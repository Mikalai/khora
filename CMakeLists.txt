# CMakeList.txt : CMake project for Khora, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.14)

project(Khora VERSION 0.1.0 LANGUAGES C CXX)

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


file(GLOB_RECURSE SourceFiles
     "*.h"
     "*.cpp"
)

set(MAKELIST_SOURCE 
    "Render/WorldCompiler.h"
    "Render/WorldCompiler.cpp"
    "Log/Log.cpp"
    "Platform/SpinLock.cpp"
    "Platform/WellKnownPaths.cpp"
    "Platform/ThreadId.cpp"
    "MakeList/Main.cpp")

add_executable (MakeList ${MAKELIST_SOURCE})

add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/Assets/Names.h
    COMMAND MakeList "${CMAKE_CURRENT_SOURCE_DIR}/../data/raw/models/board.vsgb" 
        "${CMAKE_CURRENT_SOURCE_DIR}/../data/raw/models/city_card.vsgb" 
        "${CMAKE_CURRENT_SOURCE_DIR}/../data/raw/models/policies.vsgb"
        "${CMAKE_CURRENT_SOURCE_DIR}/../data/raw/models/events.vsgb" > ${CMAKE_CURRENT_SOURCE_DIR}/Assets/Names.h
    VERBATIM)

add_executable (Khora ${SourceFiles} "${CMAKE_CURRENT_SOURCE_DIR}/Assets/Names.h")
#add_executable (Khora ${MAKELIST_SOURCE} "${CMAKE_CURRENT_SOURCE_DIR}/Assets/Names.h")

if (MAD_ENGINE_ENABLE_LOG)
    message ("Search fmt library")
    find_package(fmt CONFIG)        
    if (${fmt_FOUND}) 
        message ("Found fmt library")
        target_link_libraries(Khora fmt::fmt)
        message("FMT DIR: " ${fmt_DIR})
        target_include_directories(Khora PRIVATE ${fmt_DIR})
        target_link_libraries(MakeList fmt::fmt)    
        set(MAD_ENGINE_USE_FMT "1" CACHE STRING "Use fmt library in logger")
    endif()
endif()

if (MAD_ENGINE_ENABLE_UNIT_TESTS)
	message ("Search gtest")
	enable_testing()
	find_package(GTest REQUIRED)
	if (${GTest_FOUND})
		message("Found gtest library: Dir " ${GTest_DIR})
		
		target_include_directories(Khora PRIVATE ${GTest_DIR})
		target_link_libraries(Khora GTest::GTest)
	endif()
endif()

if (MAD_ENGINE_USE_GLM)
    find_package(glm CONFIG REQUIRED)    
    target_link_libraries(Khora glm::glm)
    target_link_libraries(MakeList vsg::vsg)    
    target_include_directories(Khora PRIVATE ${GLM_DIR})    
endif()

if (MAD_ENGINE_USE_GLFW)
    find_package(glfw3 CONFIG REQUIRED)
    target_link_libraries(Khora glfw)
    target_include_directories(Khora PRIVATE ${GLFW_DIR})    
endif()


if (MAD_ENGINE_USE_BOOST_PROGRAM_OPTIONS)
    find_package(Boost COMPONENTS program_options filesystem REQUIRED)
    message("Boost libs: " ${Boost_LIBRARIES})
    include_directories( ${Boost_INCLUDE_DIR} )
    target_link_libraries(Khora ${Boost_LIBRARIES})
    target_link_libraries(Khora Boost::program_options Boost::filesystem)
endif()

message("VULKAN_SDK: " $ENV{VULKAN_SDK})

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(vsgMacros)

vsg_setup_dir_vars()
vsg_setup_build_vars()

find_package(vsg)
if (${vsg_FOUND})
    message("Found VSG: " ${vsg_LIBRARIES} " " ${vsg_INCLUDE_DIR})
    set(MAD_ENGINE_USE_VSG "1" CACHE STRING "Use VSG library to render 3D graphics")    

    target_include_directories(Khora PRIVATE ${vsg_INCLUDE_DIR} )
    target_link_libraries(Khora vsg::vsg)

    target_include_directories(MakeList PRIVATE ${vsg_INCLUDE_DIR} )
    target_link_libraries(MakeList vsg::vsg)    
endif()

configure_file("Config.h.in" "Config.h")


# TODO: Add tests and install targets if needed.
