
if (${vsg_FOUND})

    set(EditorSources 
        "UI/ViewerWindow.cpp"
        "UI/ViewerWindow.h"
        "UI/EditorMainWindow.cpp"
        "UI/EditorMainWindow.h"
        "UI/vsgEditor.cpp"
        "UI/vsgEditor.h"
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
        "IDirectoryObserver.h"
        "ObjectEntry.cpp"
        "ObjectEntry.h"
        "Entry.cpp"
        "Entry.h"
        "IDataModelEditor.h"
        "EntryType.h"
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
    )

    set(Boost_USE_STATIC_LIBS ON) 
    set(Boost_USE_MULTITHREADED ON)  
    set(Boost_USE_STATIC_RUNTIME ON) 
    
    find_package(Boost COMPONENTS thread) 

    find_package(wxWidgets CONFIG REQUIRED)
    find_package(vsgXchange CONFIG REQUIRED)

    add_executable(Editor WIN32 ${EditorSources})
    
    target_include_directories(Editor PRIVATE ${vsg_INCLUDE_DIR} ${Boost_INCLUDE_DIRS})
    target_link_libraries(Editor PRIVATE wx::core wx::base vsg::vsg vsgXchange::vsgXchange ${Boost_LIBRARIES} KhoraLib)

endif()