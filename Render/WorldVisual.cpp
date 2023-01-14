#include <iostream>
#include <iomanip>
#include <Locale/Translate.h>
#include <PolicyTemplate.h>
#include <Platform/NumberConverter.h>
#include "Animation.h"
#include "WorldVisual.h"
#include "PlayerLogic.h"
#include "PoliciesManipulator.h"
#include <WorldLogic.h>
#include "WorldCompiler.h"

const vsg::dvec4 darkColor{ 0.2,0.2,0.2,1.0 };
double tableCaptionScale = 0.003;

WorldVisual& loadWorld(WorldVisual& world, vsg::ref_ptr<vsg::Node> scene) {
	WorldCompiler compiler;
	scene->accept(compiler);

	if (auto it = compiler.objects.find("camera_object_Orientation"); it != compiler.objects.end()) {
		auto camera = it->second;
	}

	if (auto it = compiler.objects.find("camera_settings"); it != compiler.objects.end()) {
		auto camera = it->second;
	}

	for (auto& camera : world.camera_serialization_table) {
		if (auto it = compiler.objects.find(camera.first); it != compiler.objects.end()) {
			auto m = vsg::cast<vsg::MatrixTransform>(std::get<0>(it->second));
			*camera.second = vsg::cast<vsg::Camera>(m->children[0]);

			if (!*camera.second) {
				std::cerr << "Object " << camera.first << " was found but this is not camera." << std::endl;
			}
		}
		else {
			std::cerr << "Can't load geometry " << camera.first << std::endl;
			exit(-1);
		}
	}

	for (auto& geometry : world.geometry_serialization_table) {
		INFO("Loading geometry {}", geometry.first);		
		if (auto it = compiler.objects.find(geometry.first); it != compiler.objects.end()) {	
			auto o = std::get<0>(it->second);
			INFO("Geometry {} found. Type {}", geometry.first, o->className());

			auto m = vsg::cast<vsg::MatrixTransform>(o);
			auto state = vsg::cast<vsg::StateGroup>(m->children[0]);
			*geometry.second = vsg::cast<vsg::VertexIndexDraw>(state->children[0]);


			assert(geometry.second != nullptr && "Asset not found");
		}
		else {
			std::cerr << "Can't load geometry " << geometry.first << std::endl;
			exit(-1);
		}
	}

	for (auto& material : world.materials_serialization_table) {
		if (auto it = compiler.objects.find(material.first); it != compiler.objects.end()) {
			if (material.first == str_red_army)
			{
				std::cout << "RED";
			}
			auto o = std::get<0>(it->second);			
			INFO("Object {} has class name {}", material.first, o->className());

			vsg::ref_ptr<vsg::StateGroup> state;

			if (auto t = vsg::cast<vsg::MatrixTransform>(o); t) {
				state = vsg::cast<vsg::StateGroup>(t->children.front());	
			} else {
				state = vsg::cast<vsg::StateGroup>(o);
			}
			
			assert(state != nullptr);

			state->children.clear();
			*material.second = state;

			assert(state != nullptr);
			if (!*material.second) {
				std::cerr << "Object " << material.first << " was found but this is not material." << std::endl;
			}
		}
		else {
			std::cerr << "Can't load material " << material.first << std::endl;
			exit(-1);
		}
	}

	for (auto& transform : world.transform_serialization_table) {
		if (auto it = compiler.objects.find(transform.first); it != compiler.objects.end()) {
			auto o = std::get<0>(it->second);
			auto m = vsg::cast<vsg::MatrixTransform>(o);
			m->children.clear();
			*transform.second = m;

			if (!*transform.second) {
				std::cerr << "Object " << transform.first << " was found but this is not transform." << std::endl;
			}
		}
		else {
			std::cerr << "Can't load geometry " << transform.first << std::endl;
			exit(-1);
		}
	}

	for (auto& transform : world.matrix_serialization_table) {
		if (auto it = compiler.objects.find(transform.first); it != compiler.objects.end()) {
			auto o = std::get<0>(it->second);
			auto m = vsg::cast<vsg::MatrixTransform>(o);
			m->children.clear();
			*transform.second = m->matrix;			
		}
		else {
			std::cerr << "Can't load geometry " << transform.first << std::endl;
			exit(-1);
		}
	}

	//assert(world.army_materials[0] != nullptr);

	return world;
}


void WorldVisual::CreateFromScene(vsg::ref_ptr<vsg::Node> scene) {
	loadWorld(*this, scene);
	OnLoadComplete();
}

void WorldVisual::CompileActions() {
	for (int j = 0; j < players_count; ++j) {

		action_back_materials[j]->addChild(action_back_geometry);
		for (int i = 0; i < As<int>(ActionType::Count); ++i) {
			action_front_materials[j][i]->addChild(action_front_geometry);

			auto t = actions[j][i] = vsg::MatrixTransform::create();
			t->matrix = vsg::translate(0.0, 1.0, 0.0);

			auto front = vsg::MatrixTransform::create();
			front->matrix = action_front_offset->matrix;
			front->addChild(action_front_materials[j][i]);

			auto back = vsg::MatrixTransform::create();
			back->matrix = action_back_offset->matrix;
			back->addChild(action_back_materials[j]);

			t->addChild(front);
			t->addChild(back);
		}		
	}
}

void WorldVisual::CompilePolicies() {
	
	policy_back_material->addChild(policy_back_geometry);

	for (int i = 0; i < As<int>(Policies::policies_count); ++i) {
		policies[i] = vsg::MatrixTransform::create();
		policies[i]->matrix = vsg::translate(0.0, 1.0, 0.0);
		policy_materials[i]->addChild(policy_front_geometry);
		
		auto t1 = vsg::MatrixTransform::create();
		t1->matrix = policy_back_offset->matrix;
		t1->addChild(policy_back_material);
	
		auto t2 = vsg::MatrixTransform::create();
		t2->matrix = policy_front_offset->matrix;
		t2->addChild(policy_materials[i]);

		policies[i]->addChild(t1);
		policies[i]->addChild(t2);
	}
}

void WorldVisual::CompileEvents() {
	event_back_material->addChild(event_back_geometry);

	for (int i = 0; i < (int)GlobalEventType::Count; ++i) {
		events[i] = vsg::MatrixTransform::create();
		events[i]->matrix = vsg::translate(0.0, 1.0, 0.0);
		events_materials[i]->addChild(event_front_geometry);

		auto t1 = vsg::MatrixTransform::create();
		t1->matrix = events_back_offset->matrix;
		t1->addChild(event_back_material);

		auto t2 = vsg::MatrixTransform::create();
		t2->matrix = events_front_offset->matrix;
		t2->addChild(events_materials[i]);

		events[i]->addChild(t1);
		events[i]->addChild(t2);
	}
}

void WorldVisual::OnLoadComplete() {
	CompilePoliciesLocations();
	CompilePolicies();
	CompileEvents();	
	CompileMoney();	
	CompilePhilosophy();
	CompileDiscoveries();
	CompileActions();
	CompileTabletMaterial();
}

void WorldVisual::CompileTabletMaterial() {
	assert(tablet_materials);
	table_material->children.clear();	
}

void WorldVisual::CompilePhilosophy() {
	philosophy_material->addChild(philosophy_geometry);
}

void WorldVisual::CompileDiscoveries() {
	for (int i = 0; i < As<int>(discovery_type::discoveries_count); ++i) {
		discovery_materials[i]->addChild(discovery_geometry);
		// _viewer->compileManager->compile(discovery_materials[i]);
	}	
}

void WorldVisual::CompilePlayerMarkers() {
	for (int i = 0; i < players_count; ++i) {
	}
}

void WorldVisual::CompileMoney() {
	coin_1_material->addChild(coin_geometry);
	coin_5_material->addChild(coin_geometry);	
}

void WorldVisual::CompilePoliciesLocations() {
	CompileInHandsPoliciesLocations();
	CompileActivatedPoliciesLocations();
}

void WorldVisual::CompileInHandsPoliciesLocations() {
	for (int i = 0; i < players_count; ++i) {
		in_hand_policies_table_first_location[i] = GetRelativeToTableLocation(i, policies_in_hand_first_location_offset->matrix);
	}
}

void WorldVisual::CompileActivatedPoliciesLocations() {
	for (int i = 0; i < players_count; ++i) {
		activated_policies_table_first_location[i] = GetRelativeToTableLocation(i, policies_activated_first_location_offset->matrix);
	}	
}

//auto WorldVisual::CreateBox() {	
//	vsg::GeometryInfo geom;
//	state.wireframe = false;
//	state.blending = true;
//	state.lighting = false;
//	geom.color.set(0, 1, 0, 0.6);
//	geom.position.set(0.0f, 0.005f, 0.0f);
//	geom.dx.set(0.01f, 0.0f, 0.0f);
//	geom.dy.set(0.0f, 0.01f, 0.0f);
//	geom.dz.set(0.0f, 0.0f, 0.01f);
//
//	return builder->createBox(geom, state);
//}
//
//void WorldVisual::CreateScene() {
//	if (_worldRoot)
//		return;
//
//	_box = CreateBox();
//	_worldRoot = vsg::MatrixTransform::create();
//	_worldRoot->addChild(tablet_materials);
//
//	table_material->addChild(table_geometry);
//	_worldRoot->addChild(table_material);
//
//	// root->matrix = vsg::rotate(-vsg::PI / 2.0, 1.0, 0.0, 0.0);
//
//	_worldRoot->addChild(board_material);
//	board_material->addChild(board_geometry);
//
//	if (DEBUG_POLICIES_DECK) {
//		policies_deck_location->addChild(_box);
//	}
//
//	_worldRoot->addChild(policies_deck_location);
//
//	if (DEBUG_CLOSE_EVENTS_DECK) {
//		events_deck_close_location->addChild(_box);
//	}
//
//	_worldRoot->addChild(events_deck_close_location);
//
//	if (DEBUG_OPEN_EVENTS_DECK) {
//		events_deck_open_location->addChild(_box);
//	}
//
//	_worldRoot->addChild(events_deck_open_location);
//
//	if (DEBUG_POINTS_LOCATION) {
//		for (int i = 0; i < max_points_locations; ++i) {
//			auto point = points_location[i];
//			point->addChild(_box);
//			_worldRoot->addChild(point);
//		}
//	}
//
//	if (DEBUG_TAX_LOCATION) {
//		for (int i = 0; i < max_tax_locations; ++i) {
//			auto point = tax_location[i];
//			point->addChild(_box);
//			_worldRoot->addChild(point);
//		}
//	}
//
//	if (DEBUG_POPULATION_LOCATION) {
//		for (int i = 0; i < max_population_locations; ++i) {
//			auto point = population_location[i];
//			point->addChild(_box);
//			_worldRoot->addChild(point);
//		}
//	}
//
//	if (DEBUG_GLORY_LOCATION) {
//		for (int i = 0; i < max_glory_locations; ++i) {
//			auto point = glory_location[i];
//			point->addChild(_box);
//			_worldRoot->addChild(point);
//		}
//	}
//
//	if (DEBUG_ARMY_LOCATION) {
//		for (int i = 0; i < max_army_locations; ++i) {
//			auto point = army_location[i];
//			point->addChild(_box);
//			_worldRoot->addChild(point);
//		}
//	}
//
//	for (int i = 0; i < GetExpeditionsCount(); ++i) {
//
//		auto& e = GetExpeditionTemplate(i);
//		for (int j = 0; j < e.discoveries.size(); ++j) {
//			if (e.discoveries[j] == discovery_type::no)
//				continue;
//
//			// all expeditions has 1 except of the last
//			auto location = expedition_discoveries[i + j] = vsg::MatrixTransform::create();
//			location->matrix = vsg::translate(0, 1, 0);
//			location->addChild(discovery_materials[As<int>(e.discoveries[j])]);
//			_discoveryTokenToExpedition[location] = i;
//			_expeditionToDiscoveryTokens[i].push_back(location);
//
//			/*OnActivate(location, [id = i, this](vsg::ref_ptr<vsg::MatrixTransform> t) {
//				std::cout << "Expedition: " << id << std::endl;
//				auto expedition = GetExpeditionByDiscovery(id);
//				PostWorldUpdateAction([player = PlayerId(), expedition](WorldLogic& logic) {
//					if (logic.IsExpeditionAvailable(expedition)) {
//						logic.ActivateExpedition(player, expedition);
//					}
//					});
//				});*/
//
//			_worldRoot->addChild(location);
//		}
//	}
//
//	for (int i = 0; i < achieves_count; ++i) {
//		auto point = achieve_location[i];
//		point->addChild(_box);
//		_worldRoot->addChild(point);
//	}
//
//	for (int i = 0; i < As<int>(Policies::policies_count); ++i) {
//		_worldRoot->addChild(policies[i]);
//	}
//
//	for (int i = 0; i < (int)GlobalEventType::Count; ++i) {
//		_worldRoot->addChild(events[i]);
//	}
//	
//	double darkScale = 0.005;
//	persepolis_text_location->addChild(CreateText(tr("PERSEPOLIS"), { 0.0, 0.0, 0.0 }, { 0.6, 0.6, 0.6, 1.0 }, 0.008));
//	troops_text_location->addChild(CreateText(tr("TROOPS"), { 0.0, 0.0, 0.0 }, darkColor, darkScale));
//	glory_text_location->addChild(CreateText(tr("GLORY"), { 0.0, 0.0, 0.0 }, darkColor, darkScale));
//	tax_text_location->addChild(CreateText(tr("TAX"), { 0.0, 0.0, 0.0 }, darkColor, darkScale));
//	population_text_location->addChild(CreateText(tr("POPULATION"), { 0.0, 0.0, 0.0 }, darkColor, darkScale));
//
//	_worldRoot->addChild(persepolis_text_location);
//	_worldRoot->addChild(troops_text_location);
//	_worldRoot->addChild(glory_text_location);
//	_worldRoot->addChild(tax_text_location);
//	_worldRoot->addChild(population_text_location);
//
//	_root = vsg::MatrixTransform::create();
//	_root->addChild(_worldRoot);
//
//	_cameraAligned = vsg::MatrixTransform::create();
//	CreateSelectPlayersCountMessageBox();
//	CreateSelectColorMessageBox();
//	CreateSelectCityMessageBox();
//	_root->addChild(_cameraAligned);
//
//}

vsg::ref_ptr<vsg::Node> WorldVisual::GetWorldRoot() {
	CreateScene();
	return _worldRoot;
}

vsg::ref_ptr<vsg::Node> WorldVisual::GetRoot() {
	CreateScene();
	return _root;
}

//vsg::ref_ptr<vsg::Camera> WorldVisual::GetCamera() {
//	return _camera;
//}

WorldVisual::WorldVisual(WorldVisualInput vi)
	: GeneralUserInput{ vi.playerId, *vi.logic }
	, builder{ vi.builder }
	, _viewer{ vi.viewer }
	, _world{ *vi.logic }
	, _font{ vi.font }
	, _options{ vi.options }
	, _camera{ vi.camera } {
	transform_serialization_table[str_cur_board] = &root;
	transform_serialization_table[str_coin_first_location] = &coin_first_location_offset;
	transform_serialization_table[str_loc_dice_3] = &loc_dice_3_offset;
	transform_serialization_table[str_first_dice_location] = &first_dice_location;
	transform_serialization_table[str_first_action_card] = &first_action_card;
	transform_serialization_table[str_first_philosophy_offset] = &first_philosophy_offset;
	transform_serialization_table[str_first_discovery_offset] = &first_discovery_offset;
	transform_serialization_table[str_persepolis_location] = &persepolis_text_location;
	transform_serialization_table[str_glory_location] = &glory_text_location;
	transform_serialization_table[str_tax_location] = &tax_text_location;
	transform_serialization_table[str_troops_location] = &troops_text_location;
	transform_serialization_table[str_population_location] = &population_text_location;
	transform_serialization_table[str_dice_icon_culture_location] = &dice_icon_culture_location;	

	transform_serialization_table[str_economy_text_location] = &economy_text_location;
	transform_serialization_table[str_culture_text_location] = &culture_text_location;
	transform_serialization_table[str_military_text_location] = &military_text_location;

	transform_serialization_table[str_economy_icon_location] = &economy_icon_location;
	transform_serialization_table[str_culture_icon_location] = &culture_icon_location;
	transform_serialization_table[str_military_power_icon_location] = &military_power_icon_location;
	
	geometry_serialization_table[str_board] = &board_geometry;
	geometry_serialization_table[str_coin_5] = &coin_geometry;
	geometry_serialization_table[str_philosophy] = &philosophy_geometry;
	geometry_serialization_table[str_economy_icon] = &economy_icon_geometry;
	geometry_serialization_table[str_culture_icon] = &culture_icon_geometry;
	geometry_serialization_table[str_military_icon] = &military_icon_geometry;
	geometry_serialization_table[str_dice_icon] = &dice_icon_geometry;

	materials_serialization_table[str_board_material] = &board_material;
	materials_serialization_table[str_table_material] = &table_material;
	materials_serialization_table[str_event_back_material] = &event_back_material;

	for (int i = 0; i < players_count; ++i) {
		materials_serialization_table[str_action_back_material[i]] = &action_back_materials[i];

		for (int j = 0; j < As<int>(ActionType::Count); ++j) {
			materials_serialization_table[str_action_front_material[j][i]] = &action_front_materials[i][j];
		}
	}		

	for (int i = 0; i < max_city_track_level; ++i) {
		transform_serialization_table[str_loc_economy[i]] = &ecomony_track_offset[i];
		transform_serialization_table[str_loc_culture[i]] = &culture_track_offset[i];
		transform_serialization_table[str_loc_army[i]] = &military_track_offset[i];
	}

	for (int i = 0; i < max_city_levels; ++i) {
		transform_serialization_table[str_loc_city[i]] = &city_track_offset[i];
	}

	for (int i = 0; i < (int)GlobalEventType::Count; ++i) {
		materials_serialization_table[str_event_material[i]] = &events_materials[i];
	}

	//for (int i = 0; i < players_count; ++i) {
		materials_serialization_table[str_tablet_material] = &tablet_materials;
	//}

	for (int i = 0; i < players_count; ++i) {
		matrix_serialization_table[str_player_location[i]] = &players_tablet_matrix[i];
	}

	transform_serialization_table[str_city_location] = &city_location;

	transform_serialization_table[str_policies_deck] = &policies_deck_location;
	transform_serialization_table[str_events_deck_close] = &events_deck_close_location;
	transform_serialization_table[str_events_deck_open] = &events_deck_open_location;
	transform_serialization_table[str_policy_front] = &policy_front_offset;
	transform_serialization_table[str_policy_back] = &policy_back_offset;
	transform_serialization_table[str_event_front] = &events_front_offset;
	transform_serialization_table[str_event_back] = &events_back_offset;
	transform_serialization_table[str_policies_activated_first_location] = &policies_activated_first_location_offset;
	transform_serialization_table[str_policies_in_hand_first_location] = &policies_in_hand_first_location_offset;
	transform_serialization_table[str_action_front] = &action_front_offset;
	transform_serialization_table[str_action_back] = &action_back_offset;

	materials_serialization_table[str_coin_5_material] = &coin_5_material;
	materials_serialization_table[str_coin_1_material] = &coin_1_material;
	materials_serialization_table[str_philosophy_material] = &philosophy_material;

	geometry_serialization_table[str_policy_front] = &policy_front_geometry;
	geometry_serialization_table[str_policy_back] = &policy_back_geometry;

	materials_serialization_table[str_policy_back_material] = &policy_back_material;
	for (int i = 0; i < As<int>(Policies::policies_count); ++i) {
		materials_serialization_table[str_policy[i]] = &policy_materials[i];
	}

	geometry_serialization_table[str_city_card] = &city_geometry;

	for (int i = 0; i < cities_count; ++i) {
		materials_serialization_table[str_city_material[i]] = &cities_materials[i];
	}

	geometry_serialization_table[str_city_level] = &city_level_geometry;
	geometry_serialization_table[str_economy] = &economy_level_geometry;
	geometry_serialization_table[str_culture] = &culture_level_geometry;
	geometry_serialization_table[str_military] = &military_level_geometry;
	geometry_serialization_table[str_points] = &board_cursor_geometry;
	geometry_serialization_table[str_achieve] = &achieve_geometry;
	geometry_serialization_table[str_mark_90] = &mark_90_geometry;
	geometry_serialization_table[str_dice] = &dice_geometry;
	geometry_serialization_table[str_action_front] = &action_front_geometry;
	geometry_serialization_table[str_action_back] = &action_back_geometry;
	geometry_serialization_table[str_tablet] = &tablet_geometry;
	geometry_serialization_table[str_table] = &table_geometry;
	geometry_serialization_table[str_policy_front] = &policy_front_geometry;
	geometry_serialization_table[str_policy_back] = &policy_back_geometry;

	geometry_serialization_table[str_event_front] = &event_front_geometry;
	geometry_serialization_table[str_event_back] = &event_back_geometry;

	for (int i = 0; i < players_count; ++i) {
		materials_serialization_table[str_city_level_material[i]] = &city_level_materials[i];
	}

	for (int i = 0; i < players_count; ++i) {
		materials_serialization_table[str_economy_material[i]] = &economy_materials[i];
	}

	for (int i = 0; i < players_count; ++i) {
		materials_serialization_table[str_culture_material[i]] = &culture_materials[i];
	}

	for (int i = 0; i < players_count; ++i) {
		materials_serialization_table[str_military_material[i]] = &military_materials[i];
	}

	for (int i = 0; i < players_count; ++i) {
		materials_serialization_table[str_population_material[i]] = &population_materials[i];
	}

	for (int i = 0; i < players_count; ++i) {
		materials_serialization_table[str_army_material[i]] = &army_materials[i];
	}

	for (int i = 0; i < players_count; ++i) {
		materials_serialization_table[str_glory_material[i]] = &glory_materials[i];
	}

	for (int i = 0; i < players_count; ++i) {
		materials_serialization_table[str_points_material[i]] = &points_materials[i];
	}

	for (int i = 0; i < players_count; ++i) {
		materials_serialization_table[str_tax_material[i]] = &tax_materials[i];
	}

	for (int i = 0; i < players_count; ++i) {
		materials_serialization_table[str_achieve_points_material[i]] = &achieve_points_materials[i];
	}

	for (int i = 0; i < players_count; ++i) {
		materials_serialization_table[str_achieve_population_material[i]] = &achieve_population_materials[i];
	}

	for (int i = 0; i < players_count; ++i) {
		materials_serialization_table[str_achieve_army_material[i]] = &achieve_army_materials[i];
	}

	for (int i = 0; i < players_count; ++i) {
		materials_serialization_table[str_achieve_economy_material[i]] = &achieve_economy_materials[i];
	}

	for (int i = 0; i < players_count; ++i) {
		materials_serialization_table[str_achieve_policy_material[i]] = &achieve_policy_materials[i];
	}

	for (int i = 0; i < players_count; ++i) {
		materials_serialization_table[str_mark_90_material[i]] = &achieve_mark_90_materials[i];
	}

	for (int i = 0; i < players_count; ++i) {
		materials_serialization_table[str_dice_material[i]] = &dice_materials[i];
	}

	geometry_serialization_table[str_discovery] = &discovery_geometry;

	for (int i = 0; i < As<int>(discovery_type::discoveries_count); ++i)
	{
		materials_serialization_table[str_discovery_type[i]] = &discovery_materials[i];
	}

	// camera_serialization_table[str_camera] = &camera;

	for (int i = 0; i < max_points_locations; ++i) {
		std::stringstream stream;
		stream << str_cur_point_prefix << std::setfill('0') << std::setw(3) << i;
		auto name = stream.str();

		transform_serialization_table[name] = &points_location[i];
	}

	for (int i = 0; i < max_tax_locations; ++i) {
		std::stringstream stream;
		stream << str_cur_tax_prefix << i;
		auto name = stream.str();

		transform_serialization_table[name] = &tax_location[i];
	}

	for (int i = 0; i < max_population_locations; ++i) {
		std::stringstream stream;
		stream << str_cur_population_prefix << i;
		auto name = stream.str();

		transform_serialization_table[name] = &population_location[i];
	}

	for (int i = 0; i < max_glory_locations; ++i) {
		std::stringstream stream;
		stream << str_cur_glory_prefix << i;
		auto name = stream.str();

		transform_serialization_table[name] = &glory_location[i];
	}

	for (int i = 0; i < max_army_locations; ++i) {
		std::stringstream stream;
		stream << str_cur_army_prefix << i;
		auto name = stream.str();

		transform_serialization_table[name] = &army_location[i];
	}

	for (int i = 0; i < max_expedition_discoveries; ++i) {
		transform_serialization_table[std::get<1>(str_cur_discovery[i])] = &expedition_discoveries_offsets[i];
	}

	for (int i = 0; i < achieves_count; ++i) {
		transform_serialization_table[str_cur_achieve[i]] = &achieve_location[i];
	}

	CONNECT(DiscoveryAddedMessage);
	CONNECT(OpenSelectedActionsMessage);
	CONNECT(PolicyAddedToPlayedMessage);
	CONNECT(PolicyDroppedMessage);
	CONNECT(PlayerCountSelectedMessage);
	CONNECT(CitySelectedMessage);
	CONNECT(PlayerColorSelectedMessage);
	CONNECT(PoliciesShuffledMessage);
	CONNECT(PolicyAddedToDeckMessage);
	CONNECT(EventAddedToDeckMessage);
	CONNECT(PolicyTakenFromDeckMessage);
	CONNECT(PolicyAddedInHandsMessage);
	CONNECT(PolicyActivatedMessage);
	CONNECT(PolicyAddedToDraftMessage);
	CONNECT(PolicyRemovedFromDraftMessage);
	CONNECT(PolicyRemovedFromHandsMessage);
	CONNECT(AddMoneyMessage);
	CONNECT(RemoveMoneyMessage);
	CONNECT(ScorePointsChangedMessage);
	CONNECT(PopulationChangedMessage);
	CONNECT(TaxChangedMessage);
	CONNECT(GloryChangedMessage);
	CONNECT(ArmyChangedMessage);
	CONNECT(CityLevelChangedMessage);
	CONNECT(EconomyChangedMessage);
	CONNECT(CultureChangedMessage);
	CONNECT(MilitaryChangedMessage);
	CONNECT(ExpeditionAddedMessage);
	CONNECT(EventTakenFromDeckMessage);
	CONNECT(EventAddedToOpenDeckMessage);
	CONNECT(DiceValueChangedMessage);
	CONNECT(ActionSelectedMessage);
	CONNECT(ActionUnselectedMessage);
	CONNECT(PhilosophyAddedMessage);
	CONNECT(PhilosophyRemovedMessage);
}

void WorldVisual::Handle(ExpeditionAddedMessage& msg) {
	auto& e = GetExpeditionTemplate(msg.id);

	for (int i = 0; i < 3; ++i) {

		if (e.discoveries[i] == discovery_type::no)
			continue;		
		auto location = expedition_discoveries[msg.id + i];
		Animator().MoveTransform(location, location->matrix, expedition_discoveries_offsets[msg.id + i]->matrix);
	}
}

void WorldVisual::Handle(PlayerCountSelectedMessage& msg) {
	for (int i = 0; i < msg.playersCount; ++i) {
		auto point = players_tablet_locations[i] = vsg::MatrixTransform::create();
		point->matrix = players_tablet_matrix[i];

		if (DEBUG_PLAYER_LOCATION) {
			point->addChild(_box);
		}
		// _worldRoot->addChild(point);
	}

	for (int i = 0; i < msg.playersCount; ++i) {
		auto root = players_tablet_locations[i];
		auto point = players_city_locations[i] = vsg::MatrixTransform::create();
		point->matrix = city_location->matrix;		
		
		if (DEBUG_CITY_LOCATION) {
			point->addChild(_box);
		}

		root->addChild(point);
	}
}

void WorldVisual::Handle(CitySelectedMessage& msg) {
	auto tableRoot = players_city_locations[msg.player];
	auto material = cities_materials[msg.city];
	material->addChild(city_geometry);	
	_viewer->compileManager->compile(material);
	tableRoot->addChild(material);
	Animator().MoveTransform(tableRoot, vsg::translate(0.0, 1.0, 0.0), tableRoot->matrix);
}

void WorldVisual::Handle(PlayerColorSelectedMessage& msg) {
	auto tableRoot = players_tablet_locations[msg.player];	
	auto material = tablet_materials;//[msg.color];
	//material->addChild(tablet_geometry);
	_player_to_color[msg.player] = msg.color;	
	tableRoot->addChild(tablet_geometry);
	material->addChild(tableRoot);	

	_viewer->compileManager->compile(material);
	_viewer->compileManager->compile(coin_1_material);
	_viewer->compileManager->compile(coin_5_material);

	Animator().MoveTransform(tableRoot, vsg::translate(0.0, 1.0, 0.0), tableRoot->matrix);
	auto group_material = vsg::StateGroup::create();
	{
		for (auto c : city_level_materials[msg.color]->stateCommands) {
			group_material->stateCommands.push_back(c);
		}
	}
	tableRoot->addChild(group_material);
	{
		auto t = vsg::MatrixTransform::create();
		t->matrix = dice_icon_culture_location->matrix;
		t->addChild(dice_icon_geometry);
		group_material->addChild(t);
	}
	{
		auto t = vsg::MatrixTransform::create();
		t->matrix = economy_icon_location->matrix;		
		t->addChild(economy_icon_geometry);		
		group_material->addChild(t);		
	}
	{
		auto t = vsg::MatrixTransform::create();
		t->matrix = culture_icon_location->matrix;		
		t->addChild(culture_icon_geometry);
		group_material->addChild(t);
	}
	{
		auto t = vsg::MatrixTransform::create();
		t->matrix = military_power_icon_location->matrix;
		t->addChild(military_icon_geometry);
		group_material->addChild(t);
	}
	_viewer->compileManager->compile(group_material);

	{
		auto t = vsg::MatrixTransform::create();
		t->matrix = economy_text_location->matrix;
		auto text = CreateText(tr("ECONOMY"), { 0.0,0.0,0.0 }, darkColor, tableCaptionScale);
		_viewer->compileManager->compile(text);
		t->addChild(text);
		tableRoot->addChild(t);
	}	
	{
		auto t = vsg::MatrixTransform::create();
		t->matrix = culture_text_location->matrix;
		auto text = CreateText(tr("CULTURE"), { 0.0,0.0,0.0 }, darkColor, tableCaptionScale);
		_viewer->compileManager->compile(text);
		t->addChild(text);
		tableRoot->addChild(t);
	}
	{
		auto t = vsg::MatrixTransform::create();
		t->matrix = military_text_location->matrix;
		auto text = CreateText(tr("MILITARY"), { 0.0,0.0,0.0 }, darkColor, tableCaptionScale);
		_viewer->compileManager->compile(text);
		t->addChild(text);
		tableRoot->addChild(t);
	}
	/*{
		auto t = vsg::MatrixTransform::create();
		t->matrix = military_text_location_2->matrix;
		auto text = CreateText(tr("POWER"), { 0.0,0.0,0.0 }, darkColor, tableCaptionScale);
		_viewer->compileManager->compile(text);
		t->addChild(text);
		tableRoot->addChild(t);
	}*/	
	{
		auto t = cur_points[msg.player] = vsg::MatrixTransform::create();
		t->matrix = vsg::translate(0.0, 1.0, 0.0);
		auto m = points_materials[msg.color];
		t->addChild(m);
		m->addChild(board_cursor_geometry);
		_viewer->compileManager->compile(m);
		_worldRoot->addChild(t);
	}
	{
		auto t = cur_population[msg.player] = vsg::MatrixTransform::create();
		t->matrix = vsg::translate(0.0, 1.0, 0.0);
		auto m = population_materials[msg.color];
		t->addChild(m);
		m->addChild(board_cursor_geometry);
		_viewer->compileManager->compile(m);
		_worldRoot->addChild(t);
	}
	{
		auto t = cur_tax[msg.player] = vsg::MatrixTransform::create();
		t->matrix = vsg::translate(0.0, 1.0, 0.0);
		auto m = tax_materials[msg.color];
		t->addChild(m);
		m->addChild(board_cursor_geometry);
		_viewer->compileManager->compile(m);
		_worldRoot->addChild(t);
	}
	{
		auto t = cur_tax[msg.player] = vsg::MatrixTransform::create();
		t->matrix = vsg::translate(0.0, 1.0, 0.0);
		auto m = tax_materials[msg.color];
		t->addChild(m);
		m->addChild(board_cursor_geometry);
		_viewer->compileManager->compile(m);
		_worldRoot->addChild(t);
	}	
	{
		auto t = cur_glory[msg.player] = vsg::MatrixTransform::create();
		t->matrix = vsg::translate(0.0, 1.0, 0.0);
		auto m = glory_materials[msg.color];
		t->addChild(m);
		m->addChild(board_cursor_geometry);
		_viewer->compileManager->compile(m);
		_worldRoot->addChild(t);
	}
	{
		auto t = cur_army[msg.player] = vsg::MatrixTransform::create();
		t->matrix = vsg::translate(0.0, 1.0, 0.0);
		auto m = army_materials[msg.color];
		t->addChild(m);
		m->addChild(board_cursor_geometry);
		_viewer->compileManager->compile(m);
		_worldRoot->addChild(t);
	}
	{
		auto t = cur_city_level[msg.player] = vsg::MatrixTransform::create();
		t->matrix = vsg::translate(0.0, 1.0, 0.0);
		auto m = city_level_materials[msg.color];
		t->addChild(m);
		m->addChild(city_level_geometry);
		_viewer->compileManager->compile(m);
		_worldRoot->addChild(t);
	}
	{
		auto t = cur_economy[msg.player] = vsg::MatrixTransform::create();

		if (msg.player == PlayerId()) {
			OnActivate(t, [this](auto t) {
				if (_curEconomyActivated) {
					_curEconomyActivated();
				}
				});
		}

		t->matrix = vsg::translate(0.0, 1.0, 0.0);
		auto m = economy_materials[msg.color];
		t->addChild(m);
		m->addChild(economy_level_geometry);
		_viewer->compileManager->compile(m);
		_worldRoot->addChild(t);
	}	
	{
		auto t = cur_culture[msg.player] = vsg::MatrixTransform::create();

		if (msg.player == PlayerId()) {
			OnActivate(t, [this](auto t) {
				if (_curCultureActivated) {
					_curCultureActivated();
				}
				});
		}

		t->matrix = vsg::translate(0.0, 1.0, 0.0);
		auto m = culture_materials[msg.color];
		t->addChild(m);
		m->addChild(culture_level_geometry);
		_viewer->compileManager->compile(m);
		_worldRoot->addChild(t);
	}
	{
		auto t = cur_military[msg.player] = vsg::MatrixTransform::create();

		if (msg.player == PlayerId()) {
			OnActivate(t, [this](auto t) {
				if (_curMilitaryActivated) {
					_curMilitaryActivated();
				}
				});
		}

		t->matrix = vsg::translate(0.0, 1.0, 0.0);
		auto m = military_materials[msg.color];
		t->addChild(m);
		m->addChild(military_level_geometry);
		_viewer->compileManager->compile(m);
		_worldRoot->addChild(t);
	}
	{
		auto m = dice_materials[msg.color];
		m->addChild(dice_geometry);
		_viewer->compileManager->compile(m);

		for (int i = 0; i < 3; ++i) {
			auto t = cur_dices[msg.player][i] = vsg::MatrixTransform::create();
			t->matrix = vsg::translate(0.0, 1.0, 0.0);			
			t->addChild(m);						
			_worldRoot->addChild(t);
		}

		for (int i = 0; i < As<int>(ActionType::Count); ++i) {
			auto t = actions[_player_to_color[msg.player]][i];
			cur_action_cards[msg.player][i] = t;
			_viewer->compileManager->compile(t);
			_worldRoot->addChild(t);
		}

		auto dice3_location = GetRelativeToTableLocation(msg.player, loc_dice_3_offset->matrix);
		Animator().MoveTransform(cur_dices[msg.player][2], cur_dices[msg.player][2]->matrix, dice3_location);
	}
}

void WorldVisual::Handle(PoliciesShuffledMessage& msg) {	
}

void WorldVisual::Handle(PolicyAddedToDeckMessage& msg) {
	assert(msg.index <= _policies_deck.size());
	if (msg.index == _policies_deck.size()) {
		_policies_deck.push_back(policies[As<int>(msg.policy)]);
		auto it = _policies_deck.rbegin();
		Animator().MoveTransform(*it, (*it)->matrix, policies_deck_location->matrix * vsg::translate(0.0,  - card_depth * (double)msg.index, 0.0));
	}
	else {
		auto it = _policies_deck.begin();
		std::advance(it, msg.index);
		it = _policies_deck.insert(it, policies[As<int>(msg.policy)]);
		auto index = msg.index;		

		for (; it != _policies_deck.end(); ++it) {
			Animator().MoveTransform(*it, (*it)->matrix, policies_deck_location->matrix * vsg::translate(0.0, - card_depth * (double)index, 0.0));
			++index;
		}
	}
}

void WorldVisual::Handle(PolicyTakenFromDeckMessage& msg) {
	assert(policies[As<int>(msg.policy)] == _policies_deck.back());
	_policies_deck.erase(std::next(_policies_deck.rbegin()).base());
}

void WorldVisual::Handle(EventAddedToDeckMessage& msg) {
	assert(msg.index == _events_closed_deck.size());

	_events_closed_deck.push_back(events[(int)msg.event]);
	auto it = _events_closed_deck.rbegin();
	Animator().MoveTransform(*it, (*it)->matrix, events_deck_close_location->matrix * vsg::translate(0.0, - card_depth * (double)msg.index, 0.0));
}

void WorldVisual::Handle(PolicyRemovedFromHandsMessage& msg) {
	auto policy = policies[As<int>(msg.policy)];
	auto& in_hand = in_hand_policies[msg.player];

	assert(msg.index >= 0 && msg.index < in_hand.size());
	{
		auto it = in_hand.begin();
		std::advance(it, msg.index);

		assert(policy == *it);

		in_hand.erase(it);
	}

	//auto tablet = players_tablet_locations[msg.player]->matrix;
	auto invert = vsg::dmat4();
	if (msg.player != 0) {
		invert = vsg::rotate(vsg::PI, 0.0, 0.0, 1.0);
	}	

	MoveToLinearView(in_hand.begin(), in_hand.end(), GetRelativeToTableLocation(msg.player, policies_in_hand_first_location_offset->matrix), vsg::dvec3(POLICY_CARD_OFFSET, 0.0, 0.0), invert);
	//for (int i = 0; i < As<int>(in_hand.size()); ++i) {
	//	auto location = tablet * policies_in_hand_first_location_offset->matrix * vsg::translate((double)in_hand.size() * 0.1, 0.0, 0.0) * invert;
	//	Animator().MoveTransform(policy, policy->matrix, location);
	//}
}

void WorldVisual::Handle(PolicyAddedInHandsMessage& msg) {	
	auto policy = policies[As<int>(msg.policy)];
	in_hand_policies[msg.player].push_back(policy);	
	auto invert = vsg::dmat4();
	if (msg.player != 0) {
		invert = vsg::rotate(vsg::PI, 0.0, 0.0, 1.0);
	}

	OnActivateClear(policy);

	MoveToLinearView(in_hand_policies[msg.player].begin(), in_hand_policies[msg.player].end(), GetRelativeToTableLocation(msg.player, policies_in_hand_first_location_offset->matrix), vsg::dvec3(POLICY_CARD_OFFSET, 0.0, 0.0), invert);	
}

void WorldVisual::Handle(PolicyActivatedMessage& msg) {

}

void WorldVisual::Handle(PolicyAddedToDraftMessage& msg) {
	auto policy = policies[As<int>(msg.policy)];
	auto& in_draft = in_draft_policies[msg.player];

	assert(msg.index >= 0 && msg.index <= in_draft.size());

	auto it = in_draft.begin();
	std::advance(it, msg.index);
	in_draft.insert(it, policy);

	
	auto tablet = players_tablet_locations[msg.player]->matrix;
	auto invert = vsg::dmat4();
	if (msg.player != 0) {
		invert = vsg::rotate(vsg::PI, 0.0, 0.0, 1.0);
	}
	/*auto pa = policies[As<int>(a)];
	auto pb = policies[As<int>(b)];

	MoveToView(pa);
	MoveToView(pb);

	OnActivate(pa, [this, pa, pb, a, b, cb](auto t) {
		MoveToWorld(pa);
		MoveToWorld(pb);
		cb(a, b);
		});

	OnActivate(pb, [this, pa, pb, a, b, cb](auto t) {
		MoveToWorld(pa);
		MoveToWorld(pb);
		cb(b, a);
		});

	Animator().MoveTransform(pa, pa->matrix, vsg::translate(-0.04, 0.0, -0.25) * vsg::rotate(vsg::PI / 2, 1.0, 0.0, 0.0));
	Animator().MoveTransform(pb, pb->matrix, vsg::translate(0.04, 0.0, -0.25) * vsg::rotate(vsg::PI / 2, 1.0, 0.0, 0.0));*/
	
	if (PlayerId() == msg.player) {		
	}

	if (msg.player == PlayerId()) {
		OnActivate(policy, [policy, playerId = msg.player, policyId = msg.policy, this](auto t) {
			if (PlayerId() == playerId) {
				MoveToWorld(policy);
			}
			_selectPolicyFromDraftCallback(policyId);
			});
	}

	if (msg.player == PlayerId()) {
		MoveToGridView(in_draft.begin(), in_draft.begin() + msg.index + 1, 0.04, 0.07, 0.09, -0.25);
		/*auto total = in_draft.size();
		auto index = msg.index;
		int row[2] = { index / 2, total - index / 2 };
		index = 0;
		for (int i = 0; i < 2; ++i) {
			auto x_start = -(row[i] - 1) / 2.0 * 0.07;
			auto y = 0.04 - 0.09 * As<double>(i);
			for (int j = 0; j < row[i]; ++j) {
				auto action = in_draft[index];
				++index;
				Animator().MoveTransform(action, action->matrix, vsg::translate(x_start + 0.07 * As<double>(j), y, -0.25) * vsg::rotate(vsg::PI / 2.0, 1.0, 0.0, 0.0));
			}
		}*/
		// location = vsg::translate(-0.04 * msg.index, 0.0, -0.25) * vsg::rotate(vsg::PI / 2, 1.0, 0.0, 0.0); 
	}
	else {
		auto location = tablet * policies_in_hand_first_location_offset->matrix * vsg::translate((double)in_draft.size() * 0.1, 0.01, 0.0) * invert;
		Animator().MoveTransform(policy, policy->matrix, location);
	}	
}

void WorldVisual::MoveToGridView(TransformIterator begin, TransformIterator end, double topY, double dx, double dy, double z) {
	auto total = std::distance(begin, end);
	decltype(total) row[2] = { total / 2, total - total / 2 };
	auto cur = begin;
	for (int i = 0; i < 2; ++i) {
		auto x_start = -(row[i] - 1) / 2.0 * dx;
		auto y = topY - dy * As<double>(i);
		for (int j = 0; j < row[i]; ++j) {
			auto action = *cur;
			MoveToView(action);
			++cur;
			Animator().MoveTransform(action, action->matrix, vsg::translate(x_start + dx * As<double>(j), y, z) * vsg::rotate(vsg::PI / 2.0, 1.0, 0.0, 0.0));
		}
	}
}

void WorldVisual::MoveToLinearView(TransformIterator begin, TransformIterator end, vsg::dmat4 start, vsg::dvec3 offset, vsg::dmat4 invert) {

	vsg::dvec3 curOffset;
	while (begin != end) {

		auto location = start * vsg::translate(curOffset) * invert;
		MoveToWorld(*begin);
		Animator().MoveTransform(*begin, (*begin)->matrix, location);
		curOffset += offset;
		++begin;
	}
}

void WorldVisual::Handle(PolicyRemovedFromDraftMessage& msg) {
	auto policy = policies[As<int>(msg.policy)];
	auto& in_draft = in_draft_policies[msg.player];

	assert(msg.index >= 0 && msg.index < in_draft.size());

	auto it = in_draft.begin();
	std::advance(it, msg.index);
	assert(*it == policy);

	in_draft.erase(it);

	auto start_location = GetRelativeToTableLocation(msg.player, policies_in_hand_first_location_offset->matrix);
	auto invert = vsg::dmat4();
	if (msg.player != PlayerId()) {
		invert = vsg::rotate(vsg::PI, 0.0, 0.0, 1.0);
	}

	if (msg.player == PlayerId()) {
		OnActivateClear(policy);
		MoveToWorld(policy);
	}

	for (int i = 0; i < As<int>(in_draft.size()); ++i) {
		auto location = start_location * vsg::translate(As<double>(i) * 0.1, 0.01, 0.0) * invert;
		Animator().MoveTransform(policy, policy->matrix, location);
	}
}

vsg::dmat4 WorldVisual::GetRelativeToTableLocation(int playerId, vsg::dmat4 offset) {
	return players_tablet_matrix[playerId] * offset;
}

vsg::dmat4 WorldVisual::GetCityTrackLocation(int playerId, int level) {
	return players_tablet_matrix[playerId] * city_location->matrix * city_track_offset[level]->matrix;
}

vsg::dmat4 WorldVisual::GetEconomyTrackLocation(int playerId, int level) {
	return players_tablet_matrix[playerId] * ecomony_track_offset[level]->matrix;
}

vsg::dmat4 WorldVisual::GetCultureTrackLocation(int playerId, int level) {
	return players_tablet_matrix[playerId] * culture_track_offset[level]->matrix;
}

vsg::dmat4 WorldVisual::GetMilitaryTrackLocation(int playerId, int level) {
	return players_tablet_matrix[playerId] * military_track_offset[level]->matrix;
}

std::tuple<int, vsg::ref_ptr<vsg::MatrixTransform>> WorldVisual::CreateCoin(int playerId, int value) {
	auto& coins = player_coins[playerId];
	auto newCoin = vsg::MatrixTransform::create();
	newCoin->matrix = vsg::translate(0.0, 1.0, 0.0);

	OnActivate(newCoin, [playerId, this](vsg::ref_ptr<vsg::MatrixTransform> coin) {
		assert(!coin->children.empty());
		if (coin->children.front() == coin_1_material) {
			std::cout << playerId << ": COIN 1" << std::endl;
		}
		else if (coin->children.front() == coin_5_material) {
			std::cout << playerId << ": COIN 5" << std::endl;
		}
		else {
			assert(false);
		}
	});

	if (value == 5) {
		newCoin->addChild(coin_5_material);
		coins.push_back({ 5, newCoin });
	}
	else if (value == 1) {		
		newCoin->addChild(coin_1_material);
		coins.push_back({ 1, newCoin });
	}
	else {
		assert(false && "Only 5 and 1 value coins supported.");
	}

	_worldRoot->addChild(newCoin);

	return { value, newCoin };
}

void WorldVisual::Handle(AddMoneyMessage& msg) {	
	auto& coins = player_coins[msg.player];
	int count = msg.count;
	while (count != 0) {
		
		assert(count > 0);

		auto newCoin = CreateCoin(msg.player, count >= 5 ? 5 : 1);
		count -= std::get<0>(newCoin);		
	}

	auto oneCoinCount = std::count_if(coins.begin(), coins.end(), [](auto& l) {
		return std::get<0>(l) == 1;
		});

	auto toRemove = oneCoinCount / 5;

	while (toRemove != 0) {
		for (int i = 0; i < 5; ++i) {
			auto it = std::find_if(coins.begin(), coins.end(), [](auto& v) {
				return std::get<0>(v) == 1;
				});

			assert(it != coins.end());

			auto o = std::get<1>(*it);
			coins.erase(it);

			auto it2 = std::find(_worldRoot->children.begin(), _worldRoot->children.end(), o);
			assert(it2 != _worldRoot->children.end());
			_worldRoot->children.erase(it2);
		}

		auto newCoin = CreateCoin(msg.player, 5);		
		toRemove--;
	}

	AlignCoins(msg.player);
}

void WorldVisual::AlignCoins(int playerId) {
	auto start = GetRelativeToTableLocation(playerId, coin_first_location_offset->matrix);

	auto& coins = player_coins[playerId];

	std::sort(coins.begin(), coins.end(), [](auto& l, auto& r) {
		return std::get<0>(r) < std::get<0>(l);
		});

	for (int i = 0; i < As<int>(coins.size()); ++i) {
		auto coin = std::get<1>(coins[i]);
		auto newLocation = start * vsg::translate(As<double>(i) * 0.025, 0.0, 0.0);
		Animator().MoveTransform(coin, coin->matrix, newLocation);
	}
}

void WorldVisual::RemoveCoin(int playerId, int index) {
	auto& coins = player_coins[playerId];
	auto it = coins.begin();
	std::advance(it, index);
	auto tr = std::get<1>(coins[index]);
	coins.erase(it);

	Animator().MoveTransform(tr, tr->matrix, vsg::translate(0.0, 1.0, 0.0))
		.OnComplete([this, tr]() {
		RemoveFromWorld(tr);
			});
}

void WorldVisual::Handle(RemoveMoneyMessage& msg) {
	auto start = GetRelativeToTableLocation(msg.player, coin_first_location_offset->matrix);
	auto& coins = player_coins[msg.player];
	int count = msg.count;

	while (count >= 5) {
		for (int i = 0; i < coins.size(); ++i) {
			auto value = std::get<0>(coins[i]);
			if (value == 5) {
				count -= value;
				RemoveCoin(msg.player, i);
				break;
			}
		}
	}

	while (count != 0) {
		for (int i = coins.size() - 1; i >= 0; --i) {
			auto value = std::get<0>(coins[i]);
			if (value == 1) {
				count--;
				RemoveCoin(msg.player, i);
				break;
			}
			else if (value == 5) {
				RemoveCoin(msg.player, i);
				for (int i = 0; i < 5; ++i) {
					CreateCoin(msg.player, 1);
				}
				break;
			}
		}
	}

	AlignCoins(msg.player);
}

void WorldVisual::Handle(ScorePointsChangedMessage& msg) {
	auto cur = cur_points[msg.player];
	auto target = points_location[msg.points % max_points_locations];
	Animator().MoveTransform(cur, cur->matrix, target->matrix);
}

void WorldVisual::Handle(PopulationChangedMessage& msg) {
	auto cur = cur_population[msg.player];
	assert(msg.population >= 0 && msg.population < max_population_locations);
	auto target = population_location[msg.population]->matrix * vsg::translate(As<double>(msg.player) * TRACK_PLAYER_OFFSET, 0.0, 0.0);
	Animator().MoveTransform(cur, cur->matrix, target);
}

void WorldVisual::Handle(TaxChangedMessage& msg) {
	auto cur = cur_tax[msg.player];
	assert(msg.tax >= 0 && msg.tax < max_tax_locations);
	auto target = tax_location[msg.tax]->matrix * vsg::translate(As<double>(msg.player) * TRACK_PLAYER_OFFSET, 0.0, 0.0);
	Animator().MoveTransform(cur, cur->matrix, target);
}

void WorldVisual::Handle(GloryChangedMessage& msg) {
	auto cur = cur_glory[msg.player];
	assert(msg.glory >= 0 && msg.glory < max_glory_locations);
	auto target = glory_location[msg.glory]->matrix * vsg::translate(As<double>(msg.player) * TRACK_PLAYER_OFFSET, 0.0, 0.0);
	Animator().MoveTransform(cur, cur->matrix, target);
}

void WorldVisual::Handle(ArmyChangedMessage& msg) {
	auto cur = cur_army[msg.player];
	assert(msg.army >= 0);
	auto army = std::min(max_army_locations - 1, msg.army);
	auto target = army_location[army]->matrix * vsg::translate(As<double>(msg.player) * TRACK_PLAYER_OFFSET, 0.0, 0.0);
	Animator().MoveTransform(cur, cur->matrix, target);
}

void WorldVisual::Handle(CityLevelChangedMessage& msg) {
	auto cur = cur_city_level[msg.player];
	assert(msg.cityLevel >= 0 && msg.cityLevel <= max_city_levels);
	auto newLocation = GetCityTrackLocation(msg.player, msg.cityLevel);	
	Animator().MoveTransform(cur, cur->matrix, newLocation);
}

void WorldVisual::Handle(EconomyChangedMessage& msg) {
	auto cur = cur_economy[msg.player];
	assert(msg.economy >= 0 && msg.economy <= max_city_track_level);
	auto newLocation = GetEconomyTrackLocation(msg.player, msg.economy);
	Animator().MoveTransform(cur, cur->matrix, newLocation);
}

void WorldVisual::Handle(CultureChangedMessage& msg) {
	auto cur = cur_culture[msg.player];
	assert(msg.culture >= 0 && msg.culture <= max_city_track_level);
	auto newLocation = GetCultureTrackLocation(msg.player, msg.culture);
	Animator().MoveTransform(cur, cur->matrix, newLocation);
}

void WorldVisual::Handle(EventTakenFromDeckMessage& msg) {
	assert(msg.index == _events_closed_deck.size() - 1);
	_taken_event = _events_closed_deck.back();
	_events_closed_deck.pop_back();	
}

void WorldVisual::Handle(MilitaryChangedMessage& msg) {
	auto cur = cur_military[msg.player];
	assert(msg.military >= 0 && msg.military <= max_city_track_level);
	auto newLocation = GetMilitaryTrackLocation(msg.player, msg.military);
	Animator().MoveTransform(cur, cur->matrix, newLocation);
}

vsg::dmat4 old;
float all = 0;

void WorldVisual::Update(float dt) {

	_cameraAligned->matrix = _camera->viewMatrix->inverse();
	/*auto v = _camera->projectionMatrix->transform();

	std::cout << std::endl;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			std::cout << std::setw(10) << std::setprecision(6)  << std::fixed << v[j][i];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;*/

	//if (v != old) {
	//	_cameraAligned->matrix = old = v;
	//	for (int i = 0; i < 16; ++i) {
	//		std::cout << std::setw(5) << v[i];
	//	}
	//	std::cout << std::endl;
	//}
	////_cameraAligned->matrix = vsg::translate((double)sin(all), (double)cos(all), 0.0);
	//all += dt;

	for (auto& v : _animations) {
		v->Update(dt);
	}

	_animations.erase(std::remove_if(_animations.begin(), _animations.end(), [](auto& v) {
		return v->IsComplete();
		}), _animations.end());
}

WorldVisualAnimator WorldVisual::Animator() {
	return { *this };
}

void WorldVisual::Next(IntersectionMessage& msg) {
	if (msg.Type == IntersectionMessageType::Activate) {
		auto& v = static_cast<ObjectActivatedMessage&>(msg);
		std::cout << v.object->className() << std::endl;
		auto it = _onActivate.find(vsg::ref_ptr<vsg::MatrixTransform>(const_cast<vsg::MatrixTransform*>(v.object)));
		if (it != _onActivate.end()) {
			it->second(it->first);
		}
	}	
	else if (msg.Type == IntersectionMessageType::NextAction) {
		for (int i = 0; i < GetPlayer().GetDiceCount(); ++i) {
			if (_diceCallbacks[i]) {
				_diceCallbacks[i](NextRandomDiceValue());
				_diceCallbacks[i] = nullptr;
			}
		}
		if (_nextActionCallback) {
			_nextActionCallback();
			_nextActionCallback = nullptr;
		}
	}
}

void WorldVisual::OnActivate(vsg::ref_ptr<vsg::MatrixTransform> sender, std::function<void(vsg::ref_ptr<vsg::MatrixTransform>)> action) {
	_onActivate[sender] = action;
}

void WorldVisual::OnActivateClear(vsg::ref_ptr<vsg::MatrixTransform> sender) {
	_onActivate.erase(sender);
}

void WorldVisual::SelectPolicyFromActiveDeckAsync(SelectPolicyCallback cb) {
	auto& player = GetPlayer();

	std::vector<vsg::ref_ptr<vsg::MatrixTransform>> transforms;
	player.Policies()
		.InActiveDeck()
		.ForEach([this, cb, &transforms](int index, const PolicyTemplate& policy) {
			auto p = policies[As<int>(policy.GetType())];
			transforms.push_back(p);

			OnActivate(p, [this, policyId = policy.GetType(), cb](auto t) {

				// Deactivate all action for current player policies
				PostWorldUpdateAction([this, policyId](WorldLogic& world) {
					OnActivateClear(policies[As<int>(policyId)]);
					GetPlayer()
						.Policies()
						.InActiveDeck()
						.ForEach([this](int index, const PolicyTemplate& policy) {
							OnActivateClear(policies[As<int>(policy.GetType())]);
						});

				auto tablet = players_tablet_locations[PlayerId()]->matrix;
				auto invert = vsg::dmat4();
				if (PlayerId() != 0) {
					invert = vsg::rotate(vsg::PI, 0.0, 0.0, 1.0);
				}

				const auto& in_hands = activated_policies[PlayerId()];
				for (int i = 0; i < As<int>(in_hands.size()); ++i) {
					auto location = tablet * policies_activated_first_location_offset->matrix * vsg::translate((double)i * 0.1, 0.0, 0.0) * invert;
					MoveToWorld(in_hands[i]);
					Animator().MoveTransform(in_hands[i], in_hands[i]->matrix, location);
				}
			});

			cb(policyId);
		});
	});

	_nextActionCallback = [this, cb]() {

		PostWorldUpdateAction([this](WorldLogic&) {
			_curEconomyActivated = []() {};
			_curCultureActivated = []() {};
			_curMilitaryActivated = []() {};
			_nextActionCallback = []() {};

			GetPlayer()
				.Policies()
				.InActiveDeck()
				.ForEach([this](int index, const PolicyTemplate& policy) {
					OnActivateClear(policies[As<int>(policy.GetType())]);
				});
		});

		cb(Policies::policy_unknown);
	};

	MoveToGridView(transforms.begin(), transforms.end(), 0.04, 0.07, 0.09, -0.25);
}

void WorldVisual::SelectDiscoveryFromPoolAsync(SelectDiscoveryCallback cb) {
	std::vector<vsg::ref_ptr<vsg::MatrixTransform>> v;
	v.reserve(3);

	for (int i = 0; i < 3; ++i) {
		if (!std::get<1>(select_discoveries[i])) {
			std::get<0>(select_discoveries[i]) = As<discovery_type>(i);
			auto tr = std::get<1>(select_discoveries[i]) = vsg::MatrixTransform::create();
			tr->matrix = vsg::translate(0.0, 1.0, 0.0);
			tr->addChild(discovery_materials[i]);
		}

		v.push_back(std::get<1>(select_discoveries[i]));

		OnActivate(std::get<1>(select_discoveries[i]), [this, cb, index = i](vsg::ref_ptr<vsg::MatrixTransform> t) {

			PostWorldUpdateAction([this, t, index](WorldLogic& world) {
				for (int i = 0; i < 3; ++i) {
					assert(std::get<1>(select_discoveries[i]));
					auto tr = std::get<1>(select_discoveries[i]);
					OnActivateClear(tr);
					if (index == i) {
						MoveToWorld(tr);
						Animator().MoveTransform(tr, tr->matrix, vsg::translate(0.0, 2.0, 0.0));
					}
				}
			});

			cb(As<discovery_type>(index));
		});			
	}
	
	MoveToGridView(v.begin(), v.end(), 0.04, 0.07, 0.07, -0.25);
}

void WorldVisual::SelectDiscoveryFromHandsAsync(SelectDiscoveryCallback cb) {
	auto& in_hand = in_hand_discoveries[PlayerId()];

	std::vector<vsg::ref_ptr<vsg::MatrixTransform>> transform;

	for (int i = 0; i < in_hand.size(); ++i) {
		transform.push_back(std::get<1>(in_hand[i]));
		OnActivate(std::get<1>(in_hand[i]), [this, cb, o = in_hand[i]](auto t) {
			PostWorldUpdateAction([this, o](auto& t) {
				auto& in_hand = in_hand_discoveries[PlayerId()];
				auto start = GetRelativeToTableLocation(PlayerId(), first_discovery_offset->matrix);
				auto index = 0;
				std::for_each(in_hand.begin(), in_hand.end(), [this, &index, start](auto t) {
					auto trans = std::get<1>(t);
					OnActivateClear(trans); 
					MoveToWorld(trans);
					Animator().MoveTransform(trans, trans->matrix, start * vsg::translate(0.01 * (double)index, 0.0, 0.0));
				});
				OnActivateClear(std::get<1>(o));

				_curEconomyActivated = []() {};
				_curCultureActivated = []() {};
				_curMilitaryActivated = []() {};
				_nextActionCallback = []() {};

			});
			cb(std::get<0>(o));
		});
	}

	_nextActionCallback = [this, cb]() {

			PostWorldUpdateAction([this](WorldLogic&) {
				auto& in_hand = in_hand_discoveries[PlayerId()];
				auto index = 0;
				auto start = GetRelativeToTableLocation(PlayerId(), first_discovery_offset->matrix);

				_curEconomyActivated = []() {};
				_curCultureActivated = []() {};
				_curMilitaryActivated = []() {};
				_nextActionCallback = []() {};

				std::for_each(in_hand.begin(), in_hand.end(), [this, &in_hand, &index, start](auto t) {
					auto trans = std::get<1>(t);
					OnActivateClear(trans);
					MoveToWorld(trans);
					Animator().MoveTransform(trans, trans->matrix, start * vsg::translate(0.01 * (double)index, 0.0, 0.0));
					OnActivateClear(std::get<1>(in_hand[index]));
					++index;
				});			

			});

		cb(discovery_type::no);
	};

	MoveToGridView(transform.begin(), transform.end(), 0.04, 0.07, 0.07, -0.25);
}

vsg::dmat4 WorldVisual::GetInvert(int playerId) const {
	if (playerId != PlayerId()) {
		return vsg::rotate(vsg::PI, 0.0, 0.0, 1.0);
	}
	else {
		return vsg::dmat4{};
	}
}

void WorldVisual::SelectPolicyFromHandsAsync(PolicySelectionReasonType reason, SelectPolicyCallback cb) {
	auto& player = GetPlayer();	

	std::vector<vsg::ref_ptr<vsg::MatrixTransform>> transforms;
	player.Policies()
		.InHands()
		.ForEach([this, cb, &transforms](int index, const PolicyTemplate& policy) {
			auto p = policies[As<int>(policy.GetType())];
			transforms.push_back(p);

			OnActivate(p, [this, policyId = policy.GetType(), cb](auto t) {

			// Deactivate all action for current player policies
			PostWorldUpdateAction([this, policyId](WorldLogic& world) {
				OnActivateClear(policies[As<int>(policyId)]);
				GetPlayer()
					.Policies()
					.InHands()
					.ForEach([this](int index, const PolicyTemplate& policy) {
					OnActivateClear(policies[As<int>(policy.GetType())]);
					});
				
				/*auto tablet = players_tablet_locations[PlayerId()]->matrix;
				auto invert = vsg::dmat4();
				
				if (PlayerId() != 0) {
					invert = vsg::rotate(vsg::PI, 0.0, 0.0, 1.0);
				}

				auto& in_hands = in_hand_policies[PlayerId()];*/
				MoveToLinearView(
					in_hand_policies[PlayerId()].begin(), 
					in_hand_policies[PlayerId()].end(),
					GetRelativeToTableLocation(PlayerId(), policies_in_hand_first_location_offset->matrix), 
					vsg::dvec3(POLICY_CARD_OFFSET, 0.0, 0.0), 
					GetInvert(PlayerId()));

				/*for (int i = 0; i < As<int>(in_hands.size()); ++i) {
					auto location = tablet * policies_in_hand_first_location_offset->matrix * vsg::translate((double)i * 0.1, 0.0, 0.0) * invert;
					MoveToWorld(in_hands[i]);
					Animator().MoveTransform(in_hands[i], in_hands[i]->matrix, location);
				}				*/

				_curEconomyActivated = []() {};
				_curCultureActivated = []() {};
				_curMilitaryActivated = []() {};
				_nextActionCallback = []() {};
			});

			cb(policyId);			

			});

		});

	_nextActionCallback = [this, cb]() {
		
		PostWorldUpdateAction([this](WorldLogic&) {
			_curEconomyActivated = []() {};
			_curCultureActivated = []() {};
			_curMilitaryActivated = []() {};
			_nextActionCallback = []() {};

			GetPlayer()
				.Policies()
				.InHands()
				.ForEach([this](int index, const PolicyTemplate& policy) {
				OnActivateClear(policies[As<int>(policy.GetType())]);
				});

			MoveToLinearView(
				in_hand_policies[PlayerId()].begin(),
				in_hand_policies[PlayerId()].end(),
				GetRelativeToTableLocation(PlayerId(), policies_in_hand_first_location_offset->matrix),
				vsg::dvec3(POLICY_CARD_OFFSET, 0.0, 0.0),
				GetInvert(PlayerId()));

			});

		cb(Policies::policy_unknown);
	};

	MoveToGridView(transforms.begin(), transforms.end(), 0.04, 0.07, 0.09, -0.25);
}

void WorldVisual::MakeProgressAsync(MakeProgressCallback cb) {
	_curEconomyActivated = [this, cb]() {
		PostWorldUpdateAction([this](WorldLogic&) {
			_curEconomyActivated = []() {};
			_curCultureActivated = []() {};
			_curMilitaryActivated = []() {};
			_nextActionCallback = []() {};
		});
		cb(ProgressTrackType::Economy);		
	};

	_curCultureActivated = [this, cb]() {
		PostWorldUpdateAction([this](WorldLogic&) {
			_curEconomyActivated = []() {};
			_curCultureActivated = []() {};
			_curMilitaryActivated = []() {};
			_nextActionCallback = []() {};
			});
		cb(ProgressTrackType::Culture);		
	};

	_curMilitaryActivated = [this, cb]() {
		PostWorldUpdateAction([this](WorldLogic&) {
			_curEconomyActivated = []() {};
			_curCultureActivated = []() {};
			_curMilitaryActivated = []() {};
			_nextActionCallback = []() {};
			});
		cb(ProgressTrackType::Military);		
	};	

	_nextActionCallback = [this, cb]() {
		PostWorldUpdateAction([this](WorldLogic&) {
			_curEconomyActivated = []() {};
			_curCultureActivated = []() {};
			_curMilitaryActivated = []() {};
			_nextActionCallback = []() {};
			});
		cb(ProgressTrackType::Unknown);
	};
}

void WorldVisual::SelectExpeditionAsync(std::function<void(int expedition)> cb) {
	for (int i = 0; i < As<int>(expedition_discoveries.size()); ++i) {
		OnActivate(expedition_discoveries[i], [this, cb](auto t) {
			auto it = _discoveryTokenToExpedition.find(t);
			assert(it != _discoveryTokenToExpedition.end());

			auto exp = _discoveryTokenToExpedition[t];
			cb(exp);

			PostWorldUpdateAction([this](WorldLogic&) {
				_nextActionCallback = []() {};
				});

			});
	}

	_nextActionCallback = [this, cb]() {
		
		PostWorldUpdateAction([this](WorldLogic&) {			
			_nextActionCallback = []() {};
			});

		cb(-1);
	};
}

void WorldVisual::SelectLawPolicyAsync(Policies a, Policies b, std::function<void(Policies selected, Policies dropped)> cb) {

	if (a == Policies::policy_unknown || b == Policies::policy_unknown) {
		if (a != Policies::policy_unknown) {
			cb(a, b);
		}
		else {
			cb(b, a);
		}
		return;
	}

	auto pa = policies[As<int>(a)];
	auto pb = policies[As<int>(b)];

	MoveToView(pa);
	MoveToView(pb);

	OnActivate(pa, [this, pa, pb, a, b, cb](auto t) {
		MoveToWorld(pa);
		MoveToWorld(pb);		
		cb(a, b);		
		});

	OnActivate(pb, [this, pa, pb, a, b, cb](auto t) {
		MoveToWorld(pa);
		MoveToWorld(pb);		
		cb(b, a);		
		});

	Animator().MoveTransform(pa, pa->matrix, vsg::translate(-0.04, 0.0, -0.25) * vsg::rotate(vsg::PI / 2, 1.0, 0.0, 0.0));
	Animator().MoveTransform(pb, pb->matrix, vsg::translate(0.04, 0.0, -0.25) * vsg::rotate(vsg::PI / 2, 1.0, 0.0, 0.0));
}

void WorldVisual::SelectActionAsync(int diceValue, bool allowMilitary, SelectActionsCallback cb) {
	auto& player = GetPlayer();		

	for (int i = 0; i < player.GetDiceCount(); ++i) {
		auto action = player.GetAction(i);
		if (action != ActionType::Unknown)
			continue;

		auto& playerDices = cur_dices[PlayerId()];
		auto x = -(player.GetDiceCount() - 1) / 2.0 * 0.03;
		auto y = 0.08;

		for (int k = 0; k < player.GetDiceCount(); ++k) {
			auto dice = playerDices[k];
			auto scale = k == i ? vsg::scale(1.3, 1.3, 1.3) : vsg::dmat4{};

			MoveToView(dice);

			Animator().MoveTransform(dice, dice->matrix,
				vsg::translate(x + 0.03 * As<double>(k), y, -0.25) * vsg::rotate(vsg::PI / 2.0, 1.0, 0.0, 0.0) * GetDiceTransform(GetPlayer().GetDice(k)) * scale);
		}
		
		int index = 0;
		std::array<vsg::ref_ptr<vsg::MatrixTransform>, As<int>(ActionType::Count)> visible;
		auto& playerActions = cur_action_cards[PlayerId()];		

		for (int j = 0; j < As<int>(ActionType::Count); ++j) {
			auto curAction = As<ActionType>(j);
			if (curAction == ActionType::Military && !allowMilitary)
				continue;

			if (player.IsActionSelected(curAction))
				continue;			
			
			auto action = playerActions[j];			
			
			if (MoveToView(action)) {
				
				OnActivate(action, [this, action, curAction, cb](auto t) {
					cb(curAction);
					/*if (index < GetPlayer().GetDiceCount() - 1)
						PostWorldUpdateAction([this, cb](WorldLogic& world) {
						this->SelectActionAsync(cb);
							});					*/		
					});		
			}
			else {
				OnActivate(action, [this, action, curAction, cb](auto t) {
					cb(curAction);
					/*if (index < GetPlayer().GetDiceCount() - 1)
						PostWorldUpdateAction([this, cb](WorldLogic& world) {
						this->SelectActionAsync(cb);
							});*/
					});
			}
			
			visible[index] = action;
			++index;
		}

		auto total = index;
		int row[2] = { index / 2, total - index / 2 };
		index = 0;
		for (int i = 0; i < 2; ++i) {
			auto x_start = -(row[i] - 1) / 2.0 * 0.06;
			auto y = 0.03 - 0.08 * As<double>(i);
			for (int j = 0; j < row[i]; ++j) {
				auto action = visible[index];
				++index;
				Animator().MoveTransform(action, action->matrix, vsg::translate(x_start + 0.06 * As<double>(j), y, -0.25) * vsg::rotate(vsg::PI / 2.0, 1.0, 0.0, 0.0));
			}
		}		

		break;
	}
}

void WorldVisual::SelectPlayersCountAsync(std::function<void(int count)> cb) {
	if (DefaultSelect) {
		cb(4);
	}
	else {
		_selectPlayersCountMessageBoxCallback = cb;
		_selectPlayersCountMessageBox->setAllChildren(true);
	}
}

void WorldVisual::SelectCityColorAsync(std::function<void(player_color color)> cb) {
	if (DefaultSelect) {
		cb(red);
	}
	else {
		_selectColorMessageBoxCallback = cb;
		_selectColorMessageBox->setAllChildren(true);
	}
}

void WorldVisual::SelectCityAsync(std::function<void(Cities city)> cb) {
	if (DefaultSelect) {
		cb(city_milet);
	}
	else {
		_selectCityMessageBoxCallback = cb;
		_selectCityMessageBox->setAllChildren(true);
	}
}

void WorldVisual::SelectPolicyFromDraftAsync(std::function<void(Policies policy)> cb) {
	_selectPolicyFromDraftCallback = cb;
}

void WorldVisual::ThrowDiceAsync(int diceIndex, std::function<void(int diceIndex, int diceValue)> cb) {
	_diceCallbacks[diceIndex] = [diceIndex, cb](int value) {
		cb(diceIndex, value);
	};
}


void WorldVisual::Handle(EventAddedToOpenDeckMessage& msg) {
	assert(_taken_event != nullptr);
	assert(_events_opened_deck.size() == msg.index);
	_events_opened_deck.push_back(_taken_event);
	_taken_event = nullptr;

	for (int i = 0; i < As<int>(_events_opened_deck.size()); ++i) {
		auto t = _events_opened_deck[i];
		Animator().MoveTransform(t, t->matrix, events_deck_open_location->matrix * vsg::translate(0.0, card_depth * (double)i, 0.0));
	}
}


void WorldVisual::Handle(DiceValueChangedMessage& msg) {
	auto player = msg.playerId;
	auto start = GetRelativeToTableLocation(player, first_dice_location->matrix);

	auto dice = cur_dices[player][msg.diceIndex];
	auto diceTransform = GetDiceTransform(msg.diceValue);

	INFO("Player {}, Dice {}, Value {}", msg.playerId, msg.diceIndex, msg.diceValue);

	Animator().MoveTransform(dice, dice->matrix, start * vsg::translate(DICE_OFFSET * As<double>(msg.diceIndex), 0.0, 0.0) * diceTransform);
}

vsg::dmat4 WorldVisual::GetDiceTransform(int diceValue) {
	switch (diceValue)
	{
	case 1:
		return vsg::dmat4{};
	case 2:
		return vsg::rotate(vsg::PI / 2.0, { 1.0, 0.0, 0.0 });
	case 3:
		return vsg::rotate(vsg::PI / 2.0, { 0.0, 0.0, 1.0 });
	case 4:
		return vsg::rotate(vsg::PI / 2.0, { 0.0, 0.0, -1.0 });
	case 5:
		return vsg::rotate(vsg::PI / 2.0, { -1.0, 0.0, 0.0 });
	case 6:
		return vsg::rotate(vsg::PI, { 1.0, 0.0, 0.0 });
	default:
		return vsg::dmat4{};
	}
}

void WorldVisual::Handle(ActionSelectedMessage& msg) {
	auto player = msg.playerId;
	auto start = GetRelativeToTableLocation(player, first_action_card->matrix);
	auto action = cur_action_cards[player][As<int>(msg.action)];

	if (msg.playerId == PlayerId()) {
		auto flag = MoveToWorld(action);		
		assert(flag);
		
		_worldRoot->addChild(action);

		OnActivateClear(action);			
	}

	auto rotate = PlayerId() == msg.playerId ? vsg::dmat4{} : vsg::rotate(vsg::PI, 1.0, 0.0, 0.0);

	Animator().MoveTransform(action, action->matrix, start * vsg::translate(As<double>(msg.index) * 0.06, 0.0, 0.0) * rotate);

	if (msg.index == GetPlayer().GetDiceCount() - 1) {
		for (int i = 0; i < cur_action_cards[player].size(); ++i) {
			auto action = cur_action_cards[player][i];
			
			if (MoveToWorld(action)) {				

				OnActivateClear(action);							

				auto target = GetRelativeToTableLocation(player, vsg::translate(0.0, 0.0, 1.0));

				Animator().MoveTransform(action, action->matrix, target * rotate);
			}
		}
		
		if (msg.playerId == PlayerId()) {
			for (int i = 0; i < GetPlayer().GetDiceCount(); ++i) {
				auto dice = cur_dices[PlayerId()][i];
				MoveToWorld(dice);
				auto start = GetRelativeToTableLocation(player, first_dice_location->matrix);
				auto diceTransform = GetDiceTransform(GetPlayer().GetDice(i));
				Animator().MoveTransform(dice, dice->matrix, start * vsg::translate(DICE_OFFSET * As<double>(i), 0.0, 0.0) * diceTransform);
			}
		}
	}	
}

void WorldVisual::Handle(ActionUnselectedMessage& msg) {

}

void WorldVisual::Handle(PhilosophyAddedMessage& msg) {
	auto player = msg.player;
	auto start = GetRelativeToTableLocation(player, first_philosophy_offset->matrix);
	auto& col = philosophy[msg.player];

	for (int c = 0; c < msg.count; ++c) {
		auto t = vsg::MatrixTransform::create();
		t->addChild(philosophy_material);
		_viewer->compileManager->compile(t);

		if (msg.player == PlayerId()) {
			OnActivate(t, [](auto t) {
				INFO("Philosophy activated");
				});
		}

		col.push_back(t);
		_worldRoot->addChild(t);		
	}

	for (int i = 0; i < col.size(); ++i) {
		Animator().MoveTransform(col[i], col[i]->matrix, start * vsg::translate(-1.0 * PHILOSOPHY_OFFSET * As<double>(i), 0.0, 0.0));
	}
}

void WorldVisual::Handle(PhilosophyRemovedMessage& msg) {
	auto player = msg.player;
	auto& col = philosophy[msg.player];

	for (int c = 0; c < msg.count; c++) {

		assert(!col.empty());

		auto t = col.back();
		col.pop_back();

		OnActivateClear(t);

		auto it = std::find(_worldRoot->children.begin(), _worldRoot->children.end(), t);
		if (it != _worldRoot->children.end()) {
			_worldRoot->children.erase(it);
		}
	}
}

void WorldVisual::Next(GameMessage& msg) {
	Map().Process(*this, msg);
}

void WorldVisual::RemoveFromWorld(vsg::ref_ptr<vsg::MatrixTransform> t) {
	auto it = std::find(_worldRoot->children.begin(), _worldRoot->children.end(), t);
	if (it == _worldRoot->children.end())
		return;
	_worldRoot->children.erase(it);
}

bool WorldVisual::MoveToView(vsg::ref_ptr<vsg::MatrixTransform> t) {

	auto it = std::find(_worldRoot->children.begin(), _worldRoot->children.end(), t);
	if (it == _worldRoot->children.end())
		return false;

	_worldRoot->children.erase(it);
	_cameraAligned->addChild(t);

	auto aligned = _cameraAligned->matrix;
	auto world = vsg::inverse(aligned) * t->matrix;
	t->matrix = world;
	return true;
}

bool WorldVisual::MoveToWorld(vsg::ref_ptr<vsg::MatrixTransform> action) {

	auto t = _cameraAligned->matrix * action->matrix;

	auto it = std::find(_cameraAligned->children.begin(), _cameraAligned->children.end(), action);
	if (it == _cameraAligned->children.end())
		return false;

	_cameraAligned->children.erase(it);
	action->matrix = t;
	_worldRoot->addChild(action);

	return true;
}

void WorldVisual::Handle(OpenSelectedActionsMessage& msg) {
	for (int playerId = 0; playerId < _world.GetPlayersCount(); ++playerId) {
		if (playerId == PlayerId())
			continue;

		auto& player = _world.GetPlayer(playerId);
		auto start = GetRelativeToTableLocation(playerId, first_action_card->matrix);

		for (int i = 0; i < player.GetDiceCount(); ++i) {
			auto actionType = player.GetAction(i);
			assert(actionType != ActionType::Unknown);

			auto action = cur_action_cards[playerId][As<int>(actionType)];

			auto rotate = vsg::rotate(vsg::PI / 2.0, 1.0, 0.0, 0.0);
			auto& anim = Animator().MoveTransform(action, action->matrix, start * vsg::translate(As<double>(i) * 0.06, 0.1, 0.0) * rotate);
			anim.OnComplete([i, start, action, this]() {
				Animator().MoveTransform(action, action->matrix, start * vsg::translate(As<double>(i) * 0.06, 0.0, 0.0));
				});
		}
	}
}

void WorldVisual::Handle(PolicyDroppedMessage& msg) {
	INFO("WorldVisual -> PolicyDroppedMessage: {} {}", msg.player, GetPolicyTemplate(msg.policy).GetName());
	auto policy = policies[As<int>(msg.policy)];
	_policies_deck.insert(_policies_deck.begin(), policy);
	
	OnActivateClear(policy);

	int index = 0;
	for (auto it = _policies_deck.begin(); it != _policies_deck.end(); ++it) {
		Animator().MoveTransform(*it, (*it)->matrix, policies_deck_location->matrix * vsg::translate(0.0, -card_depth * (double)index, 0.0));
		++index;
	}
}

void WorldVisual::Handle(PolicyAddedToPlayedMessage& msg) {
	auto policy = policies[As<int>(msg.policy)];
	auto& activated = activated_policies[msg.player];
	assert(activated.size() == msg.index);

	activated.push_back(policy);

	//auto start = ;

	MoveToLinearView(activated.begin(), activated.end(),
		GetRelativeToTableLocation(msg.player, policies_activated_first_location_offset->matrix),
		{ -POLICY_CARD_ACTIVE_OFFSET, -card_depth, 0.0 }, {});

	/*int index = 0;
	for (auto it = activated.begin(); it != activated.end(); ++it) {
		Animator().MoveTransform(*it, (*it)->matrix, start * vsg::translate((double)index, -card_depth, 0.0));
		++index;
	}*/
}

void WorldVisual::Handle(DiscoveryAddedMessage& msg) {
	auto& in_hand = in_hand_discoveries[msg.player];
	if (msg.expedition >= 0) {
		auto& v = _expeditionToDiscoveryTokens.at(msg.expedition);
		assert(msg.indexInExpedition >= 0 && msg.indexInExpedition < v.size());
		auto token = v[msg.indexInExpedition];

		in_hand.push_back(std::make_tuple(msg.discovery, token));
	}
	else if (msg.selectionIndex >= 0) {
		assert(msg.selectionIndex < 3);
		auto token = select_discoveries[msg.selectionIndex];		
		assert(std::get<0>(token) == msg.discovery && "Discovery type mismatch");
		in_hand.push_back(token);

		select_discoveries[msg.selectionIndex] = {};
	}
	else {
		assert(false && "Unexpected source of token");
	}

	auto start = GetRelativeToTableLocation(msg.player, first_discovery_offset->matrix);

	for (int i = 0; i < As<int>(in_hand.size()); ++i) {
		Animator().MoveTransform(std::get<1>(in_hand[i]), std::get<1>(in_hand[i])->matrix, start * vsg::translate(As<double>(i) * 0.01, 0.0, 0.0));
	}
}
