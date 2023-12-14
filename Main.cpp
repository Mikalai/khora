#include <Config.h>
#include <cassert>
#include <fmt/format.h>
#include <functional>
#include <unordered_map>
#include <map>

#include <iostream>
#include <Log/Log.h>
#include <Tests/RunTests.h>
#include <Messages/All.h>
#include <Platform/WellKnownPaths.h>
#include <Locale/Translate.h>
#include <UI/UI.h>
#include <UI/UserInputDispatcher.h>
#include <UI/ConsoleUserInput.h>
#include <Render/WorldVisual.h>
#include <Render/IntersectionHandler.h>
#include <Render/GameLoop.h>
#include <World.h>
#include <WorldLogic.h>
#include "Resources.h"
#include <Render/WorldVisualInput.h>

class ConsoleObserver : public Observer<GameMessage> {
public:

    void Next(GameMessage& msg) override {
        TRACE("Message {}", ToString(msg.Type));        
    }

    void Complete() override {
        INFO("Complete");
    }
};

int GenerateStringTable(const std::string& file) {
    return 0;
}

int main(int argc, char** argv)
{
    WellKnownPaths::Init();
    INIT_LOGGER();

    /*argc = 2;
    const char* args[] { "MadEngine.exe", R"(D:\Code\khora\raw\models\board.vsgb)"};
    argv = (char**)args;*/

    // set up defaults and read command line arguments to override them
    auto options = vsg::Options::create();
    options->paths = vsg::getEnvPaths("VSG_FILE_PATH");
    options->sharedObjects = vsg::SharedObjects::create();

    auto windowTraits = vsg::WindowTraits::create();
    windowTraits->windowTitle = fmt::format("khora {}.{}", KHORA_MAJOR_VERSION, KHORA_MINOR_VERSION);

    auto builder = vsg::Builder::create();
    builder->options = options;

    // set up defaults and read command line arguments to override them
    vsg::CommandLine arguments(&argc, argv);

	/*if (arguments.read("--run-tests")) {
		return RunTests(argc, argv);
	}*/

    if (arguments.read("--generate-string-table")) {
        return GenerateStringTable(arguments.value<std::string>("", "--file"));
    }

    windowTraits->debugLayer = arguments.read({"--debug", "-d"});
    windowTraits->apiDumpLayer = arguments.read({"--api", "-a"});
    if (arguments.read({"--fullscreen", "--fs"})) windowTraits->fullscreen = true;
    if (arguments.read({"--window", "-w"}, windowTraits->width, windowTraits->height)) { windowTraits->fullscreen = false; }
    auto pointOfInterest = arguments.value(vsg::dvec3(0.0, 0.0, std::numeric_limits<double>::max()), "--poi");
    auto horizonMountainHeight = arguments.value(0.0, "--hmh");
    vsg::Path textureFile = arguments.value<std::string>("", "-t");

    if (arguments.errors()) return arguments.writeErrorMessages(std::cerr);

#ifdef vsgXchange_all
    // add vsgXchange's support for reading and writing 3rd party file formats
    options->add(vsgXchange::all::create());
#endif

    // create the viewer and assign window(s) to it
    auto viewer = vsg::Viewer::create();

    auto scene = vsg::Group::create();
    vsg::ref_ptr<vsg::EllipsoidModel> ellipsoidModel;
    WorldLogic logic;
    ConsoleObserver observer;
    logic.Subscribe(&observer);

    UserInputDispatcher dispatcher(logic);
    SetUI(&dispatcher);

	logic.Subscribe(&dispatcher);

    const std::string font_filename = arguments.value<std::string>("", "--font");;
    assert(!font_filename.empty());

    auto font = vsg::read_cast<vsg::Font>(font_filename, options);

    // assign a custom StateSet to options->shaderSets so that subsequent TextGroup::setup(0, options) call will pass in our custom ShaderSet.
    auto shaderSet = options->shaderSets["text"] = vsg::createTextShaderSet(options);

    // create a DepthStencilState, disable depth test and add this to the ShaderSet::defaultGraphicsPipelineStates container so it's used when setting up the TextGroup subgraph
    auto depthStencilState = vsg::DepthStencilState::create();
    depthStencilState->depthTestEnable = VK_FALSE;
    shaderSet->defaultGraphicsPipelineStates.push_back(depthStencilState);    

    //vsg::StateInfo stateInfo;

    auto window = vsg::Window::create(windowTraits);
    if (!window)
    {
        std::cout << "Could not create windows." << std::endl;
        return 1;
    }

    viewer->addWindow(window);

    vsg::ref_ptr<vsg::LookAt> lookAt;

    // compute the bounds of the scene graph to help position camera
    vsg::ComputeBounds computeBounds;
    scene->accept(computeBounds);
    double radius = vsg::length(computeBounds.bounds.max - computeBounds.bounds.min) * 0.6;
    
    // set up the camera
    vsg::dvec3 centre{};
    vsg::dvec3 position{ 0.009106704965233803, 0.5854775905609131, 0.6723917126655579 };

    lookAt = vsg::LookAt::create(position, centre, vsg::dvec3(0.0, 1.0, 0.0));

    double nearFarRatio = 0.001;
    vsg::ref_ptr<vsg::ProjectionMatrix> perspective = vsg::Perspective::create(45.0, static_cast<double>(window->extent2D().width) / static_cast<double>(window->extent2D().height), 0.01, 50);

    auto camera = vsg::Camera::create(perspective, lookAt, vsg::ViewportState::create(window->extent2D()));

    std::cout << std::endl;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            std::cout << std::setw(10) << std::setprecision(6) << std::fixed << perspective->transform()[j][i];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    WorldVisualInput vi;
    vi.builder = builder;
    vi.logic = &logic;
    vi.options = options;
    vi.playerId = 0;
    vi.viewer = viewer;
    vi.font = font;
    vi.camera = camera;

    TabletVisual tablet{ vi };
    WorldVisual visual(vi);
    // ConsoleUserInput consoleUI{ 0, logic };

    // consoleUI.AddIdleMarker(std::make_unique<WorldVisualIdleMarker>(visual));

    logic.Subscribe(&visual);

    dispatcher.SetPlayersCount(1);
    dispatcher.SetHandler(0, &visual);

    World world(logic);

    if (argc > 1)
    {
        auto root = vsg::Group::create();

        {
            vsg::Path filename = arguments.value<std::string>("", "--data");
            if (auto model = vsg::read_cast<vsg::Node>(filename, options); model) {
                root->addChild(model);
            }
        }

        {
            vsg::Path filename = arguments.value<std::string>("", "--policies-data");
            if (auto model = vsg::read_cast<vsg::Node>(filename, options); model) {
                root->addChild(model);
            }
        }

        {
            vsg::Path filename = arguments.value<std::string>("", "--cities-data");
            if (auto model = vsg::read_cast<vsg::Node>(filename, options); model) {
                root->addChild(model);
            }
        }

        {
            vsg::Path filename = arguments.value<std::string>("", "--events-data");
            if (auto model = vsg::read_cast<vsg::Node>(filename, options); model) {
                root->addChild(model);
            }
        }
        {
            vsg::Path filename = arguments.value<std::string>("", "--tablet-data");
            if (auto model = vsg::read_cast<vsg::Node>(filename, options); model) {
                tablet.CreateFromScene(model);
                root->addChild(model);
            }            
        }

        visual.CreateFromScene(root);

        auto model = visual.GetRoot();
        scene->addChild(model);
    }


    auto commandGraph = createCommandGraphForView(window, camera, scene);
    viewer->assignRecordAndSubmitTaskAndPresentation({commandGraph});

    // add close handler to respond the close window button and pressing escape
    viewer->addEventHandler(vsg::CloseHandler::create(viewer));

    viewer->addEventHandler(vsg::Trackball::create(camera));
    viewer->addEventHandler(GameLoop::create(world, visual));
    auto intersectionHandler = IntersectionHandler::create(builder, camera, scene, ellipsoidModel, radius * 0.1, options);
    intersectionHandler->Subscribe(&visual);
    vsg::StateInfo stateInfo;

    intersectionHandler->state = stateInfo;
    viewer->addEventHandler(intersectionHandler);

    // assign a CompileTraversal to the Builder that will compile for all the views assigned to the viewer,
    // must be done after Viewer.assignRecordAndSubmitTasksAndPresentations();
    builder->assignCompileTraversal(vsg::CompileTraversal::create(*viewer));

    viewer->compile();

    // rendering main loop
    double angle = 0;
    while (viewer->advanceToNextFrame())
    {
        // pass any events into EventHandlers assigned to the Viewer
        viewer->handleEvents();

        // world.cur_board->matrix = vsg::rotate(angle, 0.0, 1.0, 0.0);
        angle += 0.01;
        viewer->update();

        viewer->recordAndSubmit();

        viewer->present();
    }
	
    // clean up done automatically thanks to ref_ptr<>
    return 0;
}
