
if (${vsg_FOUND})

    set(EditorSources 
        "UI/ViewerWindow.cpp"
        "UI/ViewerWindow.h"
        "UI/TransformPanel.cpp"
        "UI/TransformPanel.h"
        "UI/EditorMainWindow.cpp"
        "UI/EditorMainWindow.h"
        "UI/TextEnterDialog.cpp"
        "UI/TextEnterDialog.h"
        "UI/vsgEditor.cpp"
        "UI/vsgEditor.h"
        "UI/UICommon.h"
        "Application.cpp"
        "Application.h"
        "DataModel.h"
        "DataModel.cpp"
        "GeometryEntry.cpp"
        "GeometryEntry.h"
        "TransformEntry.cpp"
        "TransformEntry.h"
        "MaterialEntry.h"
        "MaterialEntry.cpp"
        "GroupEntry.h"
        "DirectoryEntry.h"
        "DirectoryEntry.cpp"
        "IEntryObserver.h"
        "ObjectEntry.cpp"
        "ObjectEntry.h"
        "Entry.cpp"
        "Entry.h"
        "IDataModelEditor.cpp"
        "IDataModelEditor.h"
        "EntryType.h"
        "IDataModelObserver.cpp"
        "IDataModelObserver.h"
        "EntryPath.cpp"
        "EntryPath.h"
        "GroupEntry.cpp"
        "Clone.h"
        "Clone.cpp"
        "Serializer.h"
        "Serializer.cpp"
        "AsyncQueue.h"
        "AsyncQueue.cpp"
        "Errors.h"
        "Errors.cpp"
        "ConfigEntry.h"
        "ConfigEntry.cpp"
        "LocalizedEntry.h"        
        "LocalizedEntry.cpp"
        "SystemFonts.h"
        "SystemFonts.cpp"
        "Observer.h"
        "LongOperationNotification.h"
    )

    set(Boost_USE_STATIC_LIBS ON) 
    set(Boost_USE_MULTITHREADED ON)  
    set(Boost_USE_STATIC_RUNTIME ON) 
    
    find_package(Boost COMPONENTS thread) 

    find_package(wxWidgets REQUIRED gl core base OPTIONAL_COMPONENTS net)
    find_package(vsgXchange CONFIG REQUIRED)
    find_package(Freetype REQUIRED)

    add_executable(Editor WIN32 ${EditorSources})
    
    target_include_directories(Editor PRIVATE Freetype::Freetype ${vsg_INCLUDE_DIR} ${Boost_INCLUDE_DIRS})

    if (vsgXchange_FOUND)
        target_compile_definitions(Editor PRIVATE vsgXchange_FOUND)
        target_link_libraries(Editor PRIVATE vsgXchange::vsgXchange)
    endif()

    include(${wxWidgets_USE_FILE})

    find_package(PkgConfig)

    pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
        
    target_include_directories(Editor PUBLIC ${GTK3_INCLUDE_DIRS})
    target_link_libraries(Editor PRIVATE ${wxWidgets_LIBRARIES} vsg::vsg vsgXchange::vsgXchange ${Boost_LIBRARIES} KhoraLib)

    add_custom_command(
        TARGET Editor POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_CURRENT_SOURCE_DIR}/UI/Icons
                ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Icons)

endif()