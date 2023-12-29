# CMakeList.txt : CMake project for Khora, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.14)

set(MAJOR_VERSION  0)
set(MINOR_VERSION  1)
set(BUILD_VERSION  0)
set(BUILD_REVISION 0)

project(Khora VERSION ${MAJOR_VERSION}.${MINOR_VERSION}.${BUILD_VERSION}.${BUILD_REVISION} LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)

include_directories("../")
include_directories("./")
include_directories(${CMAKE_CURRENT_BINARY_DIR})

#if(NOT CMAKE_BUILD_TYPE)
#  set(CMAKE_BUILD_TYPE RelWithDebInfo)
#endif()

message("Compiler: " ${CMAKE_CXX_COMPILER_ID})

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")  
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC") 
    set(CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE} "/O3" "/Qpar" "/Wall" "/arch:AVX512" "/GL")
endif()


# add_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)

set(CMAKE_VERBOSE_MAKEFILE ON)
option(MAD_ENGINE_USE_GLM "Enable to use GLM as underlying math engine." ON)
option(MAD_ENGINE_USE_GLFW "Enable to use GLFW as underlying window engine." ON)
option(MAD_ENGINE_USE_BOOST_PROGRAM_OPTIONS "Enable to boost program options to parse command line arguments." ON)
option(MAD_ENGINE_USE_BOOST_DLL "Enable to boost dll library." ON)
option(MAD_ENGINE_ENABLE_LOG "Enable console and file logging. Use MAD_ENGINE_LOG_LEVEL to set log level." ON)
option(MAD_ENGINE_USE_BATTLE_GRID "Enable battle grid to speed up spatial search." ON)
option(MAD_ENGINE_ENABLE_UNIT_TESTS "Enable unit tests." ON)
set(KHORA_MAJOR_VERSION "v0" CACHE STRING "Major version.")
set(KHORA_MINOR_VERSION "1" CACHE STRING "Minor version.")
set(MAD_ENGINE_COMPANY "MADS" CACHE STRING "Override company name. Influence config path.")
set(MAD_ENGINE_PRODUCT "P01" CACHE STRING "Override product name. Influence config path.")
set(MAD_ENGINE_LOG_LEVEL "2" CACHE STRING "Log level. 0 - trace, 1 - debug, 2 - info, 3 - warning, 4 - error, 5 - critical." )

set(SourceFiles
"UI/AIUserInput.cpp"
"UI/AIUserInput.h"
"UI/AllHandler.cpp"
"UI/AllHandler.h"
"UI/ConsoleUserInput.cpp"
"UI/ConsoleUserInput.h"
"UI/GeneralUserInput.cpp"
"UI/GeneralUserInput.h"
"UI/ICityStrategy.cpp"
"UI/ICityStrategy.h"
"UI/IUserInput.cpp"
"UI/IUserInput.h"
"UI/IUserInputHandler.cpp"
"UI/IUserInputHandler.h"
"UI/IUserInputIdleMarker.h"
"UI/NetworkUserInput.cpp"
"UI/NetworkUserInput.h"
"UI/SimpleCityStrategy.cpp"
"UI/SimpleCityStrategy.h"
"UI/UI.cpp"
"UI/UI.h"
"UI/UserInputDispatcher.cpp"
"UI/UserInputDispatcher.h"
"Render/Animation.cpp"
"Render/Animation.h"
"Render/CameraManipulator.cpp"
"Render/CameraManipulator.h"
"Render/GameLoop.cpp"
"Render/GameLoop.h"
"Render/IntersectionHandler.cpp"
"Render/IntersectionHandler.h"
"Render/TransformAnimation.cpp"
"Render/TransformAnimation.h"
"Render/WorldCompiler.cpp"
"Render/WorldCompiler.h"
"Render/WorldVisual.cpp"
"Render/WorldVisual.h"
"Render/WorldVisualAnimator.cpp"
"Render/WorldVisualAnimator.h"
"Render/WorldVisualIdleMarker.cpp"
"Render/WorldVisualIdleMarker.h"
"Render/WorldVisualInput.h"
"Platform/NumberConverter.h"
"Platform/Path.h"
"Platform/SpinLock.cpp"
"Platform/SpinLock.h"
"Platform/ThreadId.cpp"
"Platform/ThreadId.h"
"Platform/WellKnownPaths.cpp"
"Platform/WellKnownPaths.h"
"Messages/All.h"
"Messages/GameMessage.h"
"Messages/MessageType.cpp"
"Messages/MessageType.h"
"Messages/MoneyChangedMessage.h"
"Messages/TaxChangedMessage.h"
"Logic/ActionsState.cpp"
"Logic/ActionsState.h"
"Logic/ComplexState.cpp"
"Logic/ComplexState.h"
"Logic/RoundState.cpp"
"Logic/RoundState.h"
"Logic/ThrowDicesState.cpp"
"Logic/ThrowDicesState.h"
"Logic/WorldDraftState.cpp"
"Logic/WorldDraftState.h"
"Logic/WorldGameState.cpp"
"Logic/WorldGameState.h"
"Logic/WorldInitState.cpp"
"Logic/WorldInitState.h"
"Logic/WorldState.cpp"
"Logic/WorldState.h"
"Log/Log.cpp"
"Log/Log.h"
"Log/LogMessageFormatter.h"
"Locale/EnglishLocalization.cpp"
"Locale/EnglishLocalization.h"
"Locale/ILocalization.h"
"Locale/Translate.cpp"
"Locale/Translate.h"
"Effects/CityEffect.cpp"
"Effects/CityEffect.h"
"Effects/Effect.cpp"
"Effects/Effect.h"
"Effects/EventEffect.cpp"
"Effects/EventEffect.h"
"Effects/PlayerEffect.cpp"
"Effects/PlayerEffect.h"
"Effects/PlayerEffectRequirenment.h"
"Effects/PlayerPerk.h"
"Effects/PlayerPredicate.h"
"Effects/PolicyEffect.cpp"
"Effects/PolicyEffect.h"
"Effects/WorldEffect.cpp"
"Effects/WorldEffect.h"
"ActionType.cpp"
"ActionType.h"
"AllArmies.cpp"
"AllArmies.h"
"CityTemplate.cpp"
"CityTemplate.h"
"Deck.h"
"DiscoveryType.cpp"
"DiscoveryType.h"
"DraftManipulator.cpp"
"DraftManipulator.h"
"DraftManipulatorConst.cpp"
"DraftManipulatorConst.h"
"EventsManipulator.cpp"
"EventsManipulator.h"
"EventTemplate.cpp"
"EventTemplate.h"
"ExpeditionTemplate.cpp"
"ExpeditionTemplate.h"
"GlobalEventsDeck.cpp"
"GlobalEventsDeck.h"
"GlobalEventStage.h"
"GlobalEventType.cpp"
"GlobalEventType.h"
"Observers.h"
"OrderedByDicesPlayers.cpp"
"OrderedByDicesPlayers.h"
"PlayerLogic.cpp"
"PlayerLogic.h"
"PlayerPerkAcceptor.cpp"
"PlayerPerkAcceptor.h"
"PlayerPerks.cpp"
"PlayerPerks.h"
"Players.cpp"
"Players.h"
"PlayersConst.cpp"
"PlayersConst.h"
"Policies.cpp"
"Policies.h"
"PoliciesDeck.cpp"
"PoliciesDeck.h"
"PoliciesManipulator.cpp"
"PoliciesManipulator.h"
"PolicyTemplate.cpp"
"PolicyTemplate.h"
"Resources.h"
"Round.cpp"
"Round.h"
"World.cpp"
"World.h"
"WorldLogic.cpp"
"WorldLogic.h"
"WorldLogicPrepare.cpp"
"WorldLogicPrepare.h"
"WorldLogicRound.cpp"
"WorldLogicRound.h"
)

add_library(KhoraLib STATIC ${SourceFiles})

add_executable (Khora Main.cpp)
target_link_libraries(Khora KhoraLib)

if (MAD_ENGINE_ENABLE_LOG)
    message ("Search fmt library")
    find_package(fmt CONFIG)        
    if (${fmt_FOUND}) 
        message ("Found fmt library")
        target_link_libraries(Khora fmt::fmt)
        message("FMT DIR: " ${fmt_DIR})
        target_include_directories(Khora PRIVATE ${fmt_DIR})
        set(MAD_ENGINE_USE_FMT "1" CACHE STRING "Use fmt library in logger")
    endif()
endif()

if (MAD_ENGINE_ENABLE_UNIT_TESTS)
	message ("Search gtest")
	# enable_testing()
	find_package(GTest REQUIRED)
	if (${GTest_FOUND})
		message("Found gtest library: Dir " ${GTest_DIR})
		
		target_include_directories(Khora PRIVATE ${GTest_DIR})
		target_link_libraries(Khora GTest::GTest)
	endif()
endif()

if (MAD_ENGINE_USE_GLM)
    find_package(glm CONFIG REQUIRED)    
    target_link_libraries(KhoraLib glm::glm)
    target_include_directories(KhoraLib PRIVATE ${GLM_DIR})    
endif()

if (MAD_ENGINE_USE_GLFW)
    #find_package(glfw3 CONFIG REQUIRED)
    #target_link_libraries(Khora glfw)
    #target_include_directories(Khora PRIVATE ${GLFW_DIR})    
endif()


if (MAD_ENGINE_USE_BOOST_PROGRAM_OPTIONS)
    find_package(Boost COMPONENTS program_options filesystem REQUIRED)
    message("Boost libs: " ${Boost_LIBRARIES})
    include_directories( ${Boost_INCLUDE_DIR} )
    target_link_libraries(KhoraLib ${Boost_LIBRARIES})
    target_link_libraries(KhoraLib Boost::program_options Boost::filesystem)
endif()

message("VULKAN_SDK: " $ENV{VULKAN_SDK})

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(vsgMacros)

vsg_setup_dir_vars()
vsg_setup_build_vars()

find_package(vsg REQUIRED)

if (${vsg_FOUND})
    message("Found VSG: " ${vsg_LIBRARIES} " " ${vsg_INCLUDE_DIR})
    set(MAD_ENGINE_USE_VSG "1" CACHE STRING "Use VSG library to render 3D graphics")    

    target_include_directories(Khora PRIVATE ${vsg_INCLUDE_DIR} )
    target_include_directories(KhoraLib PRIVATE ${vsg_INCLUDE_DIR} )
    target_link_libraries(Khora vsg::vsg)
    target_link_libraries(KhoraLib vsg::vsg)
endif()

configure_file("Config.h.in" "Config.h")

add_subdirectory("Editor")
