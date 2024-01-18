project(Editor VERSION ${MAJOR_VERSION}.${MINOR_VERSION}.${BUILD_VERSION}.${BUILD_REVISION} LANGUAGES C CXX)

find_package(vsg REQUIRED)
find_package(vsgXchange CONFIG REQUIRED)
find_package(Freetype REQUIRED)

if (WIN32)
    add_definitions(-D_WIN32_WINNT=0x0601)
endif()

set(EditorSources 
    "UI/ViewerWindow.cpp"
    "UI/ViewerWindow.h"
    "UI/TransformPanel.cpp"
    "UI/TransformPanel.h"
    "UI/EditorMainWindow.cpp"
    "UI/EditorMainWindow.h"
    "UI/TextEnterDialog.cpp"
    "UI/TextEnterDialog.h"
    "UI/TextPanel.cpp"
    "UI/TextPanel.h"
    "UI/vsgEditor.cpp"
    "UI/vsgEditor.h"
    "UI/UICommon.h"
    "UI/ViewerState.h"
    "UI/Processors/ActiveLanguageChangedMessageProcessor.cpp"
    "UI/Processors/ActiveLanguageChangedMessageProcessor.h"
    "UI/Processors/BulkOperationEndedMessageProcessor.cpp"
    "UI/Processors/BulkOperationEndedMessageProcessor.h"
    "UI/Processors/BulkOperationStartedMessageProcessor.cpp"
    "UI/Processors/BulkOperationStartedMessageProcessor.h"
    "UI/Processors/CompileMessageProcessor.cpp"
    "UI/Processors/CompileMessageProcessor.h"
    "UI/Processors/ConfigChangedMessageProcessor.cpp"
    "UI/Processors/ConfigChangedMessageProcessor.h"
    "UI/Processors/EntryPropertyChangedMessageProcessor.cpp"
    "UI/Processors/EntryPropertyChangedMessageProcessor.h"
    "UI/Processors/EntrySelectedMessageProcessor.cpp"
    "UI/Processors/EntrySelectedMessageProcessor.h"
    "UI/Processors/FontCompiledMessageProcessor.cpp"
    "UI/Processors/FontCompiledMessageProcessor.h"
    "UI/Processors/FontsRefreshCompletedMessageProcessor.cpp"
    "UI/Processors/FontsRefreshCompletedMessageProcessor.h"
    "UI/Processors/EntryAddedMessageProcessor.cpp"
    "UI/Processors/EntryAddedMessageProcessor.h"
    "UI/Processors/EntryRemovedMessageProcessor.cpp"
    "UI/Processors/EntryRemovedMessageProcessor.h"
    "UI/Processors/LanguageAddedMessageProcessor.cpp"
    "UI/Processors/LanguageAddedMessageProcessor.h"
    "UI/Processors/LanguageRemovedMessageProcessor.cpp"
    "UI/Processors/LanguageRemovedMessageProcessor.h"
    "UI/Processors/LongOperationEndedMessageProcessor.cpp"
    "UI/Processors/LongOperationEndedMessageProcessor.h"
    "UI/Processors/LongOperationStartedMessageProcessor.cpp"
    "UI/Processors/LongOperationStartedMessageProcessor.h"
    "UI/Processors/ModelResetMessageProcessor.cpp"
    "UI/Processors/ModelResetMessageProcessor.h"
    "UI/Processors/SceneCompeledMessageProcessor.cpp"
    "UI/Processors/SceneCompeledMessageProcessor.h"
    "UI/Processors/SuggestedChildrenMessageProcessor.cpp"
    "UI/Processors/SuggestedChildrenMessageProcessor.h"
    "UI/Processors/UnhandledMessageProcessor.cpp"
    "UI/Processors/UnhandledMessageProcessor.h"
    "Messages/CopyEntryMessage.cpp"
    "Messages/CopyEntryMessage.h"
    "Messages/CompileSceneMessage.h"
    "Messages/LanguageRemovedMessage.h"
    "Messages/ActiveLanguageChangedMessage.h"
    "Messages/MoveEntryMessage.h"
    "Messages/CopyNodeMessage.h"
    "Messages/RefreshFontsMessage.h"
    "Messages/SelectEntryMessage.h"
    "Messages/RequestSuggestedChildrenMessage.h"
    "Messages/RemoveEntryMessage.h"
    "Messages/CreateNodeMessage.h"
    "Messages/RenameEntryMessage.h"
    "Messages/ResetModelMessage.h"
    "Messages/SaveToFileMessage.h"
    "Messages/ExportToFileMessage.h"
    "Messages/AddLanguageMessage.h"
    "Messages/SetActiveLanguageMessage.h"
    "Messages/RemoveLanguageMessage.h"
    "Messages/Messages.h"
    "Messages/ImportFileMessage.h"
    "Messages/CompileFontMessage.h"
    "Messages/LanguageAddedMessage.h"
    "Messages/CompileFontMessage.h"
    "Messages/CompileMessage.h"
    "Messages/ConfigChangedMessage.h"
    "Messages/EntrySelectedMessage.h"
    "Messages/ImportFileMessage.h"
    "Messages/LanguageAddedMessage.h"
    "Messages/LanguageRemovedMessage.h"
    "Messages/Messages.h"
    "Messages/ModelResetMessage.h"
    "Messages/SceneCompeledMessage.h"
    "Messages/SuggestedChildrenMessage.h"
    "DataModel/DataModel.h"
    "DataModel/DataModel.cpp"    
    "DataModel/Processors.h"
    "DataModel/CompilationState.cpp"
    "DataModel/CompilationState.h"
    "DataModel/ICompilationState.h"
    "DataModel/IDataModelState.h"
    "DataModel/DataModelState.h"
    "DataModel/DataModelState.cpp"
    "DataModel/Processors/FontsCompilationJobsCompleteMessageProcessor.cpp"
    "DataModel/Processors/FontsCompilationJobsCompleteMessageProcessor.h"
    "DataModel/Processors/FontCompiledMessageProcessor.cpp"
    "DataModel/Processors/FontCompiledMessageProcessor.h"
    "DataModel/Processors/AddLanguageMessageProcessor.cpp"
    "DataModel/Processors/AddLanguageMessageProcessor.h"
    "DataModel/Processors/CompileSceneProcessor.cpp"
    "DataModel/Processors/CompileSceneProcessor.h"
    "DataModel/Processors/CopyEntryMessageProcessor.cpp"
    "DataModel/Processors/CopyEntryMessageProcessor.h"
    "DataModel/Processors/CopyNodeMessageProcessor.cpp"
    "DataModel/Processors/CopyNodeMessageProcessor.h"
    "DataModel/Processors/CreateNodeMessageProcessor.cpp"
    "DataModel/Processors/CreateNodeMessageProcessor.h"
    "DataModel/Processors/ExportToFileMessageProcessor.cpp"
    "DataModel/Processors/ExportToFileMessageProcessor.h"
    "DataModel/Processors/ImportFileMessageProcessor.cpp"
    "DataModel/Processors/ImportFileMessageProcessor.h"
    "DataModel/Processors/ImportFromFileMessageProcessor.cpp"
    "DataModel/Processors/ImportFromFileMessageProcessor.h"
    "DataModel/Processors/MoveEntryMessageProcessor.cpp"
    "DataModel/Processors/MoveEntryMessageProcessor.h"
    "DataModel/Processors/RemoveEntryMessageProcessor.cpp"
    "DataModel/Processors/RemoveEntryMessageProcessor.h"
    "DataModel/Processors/RemoveLanguageMessageProcessor.cpp"
    "DataModel/Processors/RemoveLanguageMessageProcessor.h"
    "DataModel/Processors/RenameEntryMessageProcessor.cpp"
    "DataModel/Processors/RenameEntryMessageProcessor.h"
    "DataModel/Processors/RenameLanguageMessageProcessor.cpp"
    "DataModel/Processors/RenameLanguageMessageProcessor.h"
    "DataModel/Processors/RequestSuggestedChildrenMessageProcessor.cpp"
    "DataModel/Processors/RequestSuggestedChildrenMessageProcessor.h"
    "DataModel/Processors/ResetModelMessageProcessor.cpp"
    "DataModel/Processors/ResetModelMessageProcessor.h"
    "DataModel/Processors/SaveToFileMessageProcessor.cpp"
    "DataModel/Processors/SaveToFileMessageProcessor.h"
    "DataModel/Processors/SelectEntryMessageProcessor.cpp"
    "DataModel/Processors/SelectEntryMessageProcessor.h"
    "DataModel/Processors/SetActiveLanguageMessageProcessor.cpp"
    "DataModel/Processors/SetActiveLanguageMessageProcessor.h"
    "DataModel/Processors/UnhandledMessageProcessor.cpp"
    "DataModel/Processors/UnhandledMessageProcessor.h"
    "Application.cpp"
    "Application.h"    
    "GeometryEntry.cpp"
    "GeometryEntry.h"
    "TransformPackageEntry.cpp"
    "TransformProxyEntry.cpp"
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
    "Observer.cpp"
    "LongOperationNotification.h"
    "TextEntry.h"
    "TextEntry.cpp"
    "IReferenced.h"
    "IEntry.h"
    "IDirectoryEntry.h"
    "IGeometryEntry.h"
    "IAsyncQueue.h"
    "IObserver.h"
    "ISystemFonts.h"
    "IGroupEntry.h"
    "IConfigEntry.h"
    "ITextEntry.h"
    "ITransformEntry.h"
    "ILocalizedEntry.h"
    "IMaterialEntry.h"
    "ISharedEntry.h"
    "ISerializable.h"
    "ICloneEntry.h"
    "ISerializable.cpp"
    "IDataModel.h"
    "ProxyEntry.h"
    "IPackageEntry.h"
    "MessageProcessor.h"
    "MessageProcessor.cpp"
    "Factory.cpp")

set(Boost_USE_STATIC_LIBS ON) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME ON) 

find_package(Boost COMPONENTS thread) 

# find_package(wxWidgets REQUIRED gl core base OPTIONAL_COMPONENTS net)
find_package(wxWidgets REQUIRED gl core base OPTIONAL_COMPONENTS net)


# vsg_setup_dir_vars()
# vsg_setup_build_vars()


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

add_executable(GuidGen "GuidGen.cpp")
if (WIN32) 
    find_package(OpenSSL REQUIRED)
    target_link_libraries(GuidGen PRIVATE ${Boost_LIBRARIES} OpenSSL::SSL OpenSSL::Crypto Bcrypt.lib)
else()
    target_link_libraries(GuidGen PRIVATE ${Boost_LIBRARIES})
endif()

add_custom_command(
    TARGET Editor POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/UI/Icons
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Icons)

find_program(CLANGFORMAT clang-format)

if (CLANGFORMAT)
    message("Clang format found " ${PROJECT_NAME})

    file(GLOB FILES_TO_FORMAT ${EditorSources}
    )
    foreach(EXCLUDE ${ARGS_EXCLUDES})
        list(REMOVE_ITEM FILES_TO_FORMAT ${EXCLUDE})
    endforeach()
    if (NOT TARGET clang-format)
        add_custom_target(clang-format)
    endif()
    add_custom_target(clang-format-${PROJECT_NAME}
        COMMAND ${CLANGFORMAT} -i ${FILES_TO_FORMAT}
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        COMMENT "Automated code format using clang-format"
    )
    set_target_properties(clang-format-${PROJECT_NAME} PROPERTIES FOLDER "${PROJECT_NAME} Folder")
    add_dependencies(clang-format clang-format-${PROJECT_NAME})
endif()
        