project(Editor VERSION ${MAJOR_VERSION}.${MINOR_VERSION}.${BUILD_VERSION}.${BUILD_REVISION} LANGUAGES C CXX)

find_package(vsg REQUIRED)
find_package(vsgXchange CONFIG REQUIRED)
find_package(Freetype REQUIRED)

if (WIN32)
    add_definitions(-D_WIN32_WINNT=0x0601)
endif()

include_directories(".")

set(EditorSources 
    "Fundamental/Interface/IMessage.h"
    "Fundamental/Interface/IReferenced.h"
    "Fundamental/Interface/IToString.h"
    "Fundamental/Interface/IAsyncQueue.h"
    "Fundamental/Interface/IAsyncTask.h"
    "Fundamental/Interface/IMessageProcessor.h"
    "Fundamental/Interface/IAggregatedProcessor.h"
    "Fundamental/Interface/Result.h"
    "Fundamental/Interface/IObserver.h"
    "Fundamental/Interface/LongOperation.h"
    "Fundamental/Interface/Messages/ILongOperationEndedMessage.h"
    "Fundamental/Interface/Messages/ILongOperationStartedMessage.h"
    "Fundamental/Module/Messages/LongOperationEndedMessage.h"
    "Fundamental/Module/Messages/LongOperationStartedMessage.h"
    "Fundamental/Module/Errors.h"
    "Fundamental/Module/Errors.cpp"
    "Fundamental/Module/MessageBase.h"
    "Fundamental/Module/Factory.cpp"
    "Fundamental/Module/Referenced.h"
    "Fundamental/Module/AsyncQueue.h"
    "Fundamental/Module/AsyncQueue.cpp"
    "Fundamental/Module/MessageProcessor.cpp"
    "Fundamental/Module/MessageProcessor.h"
    "Fundamental/Module/Observer.h"
    "Fundamental/Module/Observer.cpp"    
    "Serializer/Module/Serializable.cpp"
    "Serializer/Module/Serializer.cpp"
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
    "State/Module/Messages/CopyEntryMessage.cpp"
    "State/Module/Messages/CopyEntryMessage.h"
    "State/Module/Messages/CompileSceneMessage.h"
    "State/Module/Messages/LanguageRemovedMessage.h"
    "State/Module/Messages/ActiveLanguageChangedMessage.h"
    "State/Module/Messages/MoveEntryMessage.h"
    "State/Module/Messages/CopyNodeMessage.h"    
    "State/Module/Messages/SelectEntryMessage.h"
    "State/Module/Messages/RequestSuggestedChildrenMessage.h"
    "State/Module/Messages/RemoveEntryMessage.h"
    "State/Module/Messages/CreateNodeMessage.h"
    "State/Module/Messages/RenameEntryMessage.h"
    "State/Module/Messages/ResetModelMessage.h"
    "State/Module/Messages/SaveToFileMessage.h"
    "State/Module/Messages/ExportToFileMessage.h"
    "State/Module/Messages/AddLanguageMessage.h"
    "State/Module/Messages/SetActiveLanguageMessage.h"
    "State/Module/Messages/RemoveLanguageMessage.h"
    "State/Module/Messages/Messages.h"
    "State/Module/Messages/ImportFileMessage.h"
    "State/Module/Messages/LanguageAddedMessage.h"
    "State/Module/Messages/CompileMessage.h"
    "State/Module/Messages/ConfigChangedMessage.h"
    "State/Module/Messages/EntrySelectedMessage.h"
    "State/Module/Messages/ImportFileMessage.h"
    "State/Module/Messages/LanguageAddedMessage.h"
    "State/Module/Messages/LanguageRemovedMessage.h"
    "State/Module/Messages/Messages.h"
    "State/Module/Messages/ModelResetMessage.h"
    "State/Module/Messages/FontsCompilationJobsCompleteMessage.h"
    "State/Module/Messages/SceneCompeledMessage.h"
    "State/Module/Messages/SuggestedChildrenMessage.h"
    "State/Interface/ICompilationState.h"
    "State/Interface/IDataModelState.h"
    "State/Module/DataModel.h"
    "State/Module/DataModel.cpp"    
    "State/Module/Processors.h"
    "State/Module/CompilationState.cpp"
    "State/Module/CompilationState.h"    
    "State/Module/DataModelState.h"
    "State/Module/DataModelState.cpp"
    "State/Module/Processors/FontsCompilationJobsCompleteMessageProcessor.cpp"
    "State/Module/Processors/FontsCompilationJobsCompleteMessageProcessor.h"
    "State/Module/Processors/FontCompiledMessageProcessor.cpp"
    "State/Module/Processors/FontCompiledMessageProcessor.h"
    "State/Module/Processors/AddLanguageMessageProcessor.cpp"
    "State/Module/Processors/AddLanguageMessageProcessor.h"
    "State/Module/Processors/CompileSceneProcessor.cpp"
    "State/Module/Processors/CompileSceneProcessor.h"
    "State/Module/Processors/CopyEntryMessageProcessor.cpp"
    "State/Module/Processors/CopyEntryMessageProcessor.h"
    "State/Module/Processors/CopyNodeMessageProcessor.cpp"
    "State/Module/Processors/CopyNodeMessageProcessor.h"
    "State/Module/Processors/CreateNodeMessageProcessor.cpp"
    "State/Module/Processors/CreateNodeMessageProcessor.h"
    "State/Module/Processors/ExportToFileMessageProcessor.cpp"
    "State/Module/Processors/ExportToFileMessageProcessor.h"
    "State/Module/Processors/ImportFileMessageProcessor.cpp"
    "State/Module/Processors/ImportFileMessageProcessor.h"
    "State/Module/Processors/ImportFromFileMessageProcessor.cpp"
    "State/Module/Processors/ImportFromFileMessageProcessor.h"
    "State/Module/Processors/MoveEntryMessageProcessor.cpp"
    "State/Module/Processors/MoveEntryMessageProcessor.h"
    "State/Module/Processors/RemoveEntryMessageProcessor.cpp"
    "State/Module/Processors/RemoveEntryMessageProcessor.h"
    "State/Module/Processors/RemoveLanguageMessageProcessor.cpp"
    "State/Module/Processors/RemoveLanguageMessageProcessor.h"
    "State/Module/Processors/RenameEntryMessageProcessor.cpp"
    "State/Module/Processors/RenameEntryMessageProcessor.h"
    "State/Module/Processors/RenameLanguageMessageProcessor.cpp"
    "State/Module/Processors/RenameLanguageMessageProcessor.h"
    "State/Module/Processors/RequestSuggestedChildrenMessageProcessor.cpp"
    "State/Module/Processors/RequestSuggestedChildrenMessageProcessor.h"
    "State/Module/Processors/ResetModelMessageProcessor.cpp"
    "State/Module/Processors/ResetModelMessageProcessor.h"
    "State/Module/Processors/SaveToFileMessageProcessor.cpp"
    "State/Module/Processors/SaveToFileMessageProcessor.h"
    "State/Module/Processors/SelectEntryMessageProcessor.cpp"
    "State/Module/Processors/SelectEntryMessageProcessor.h"
    "State/Module/Processors/SetActiveLanguageMessageProcessor.cpp"
    "State/Module/Processors/SetActiveLanguageMessageProcessor.h"
    "State/Module/Processors/UnhandledMessageProcessor.cpp"
    "State/Module/Processors/UnhandledMessageProcessor.h"
    "Fonts/Module/Messages/RefreshFontsMessage.h"
    "Fonts/Interface.h"
    "Fonts/Interface/Messages/ICompileFontMessage.h"
    "Fonts/Interface/Messages/IFontCompiledMessage.h"
    "Fonts/Interface/Messages/IFontsRefreshCompletedMessage.h"
    "Fonts/Interface/Messages/IRefreshFontsMessage.h"
    "Fonts/Interface/ISystemFonts.h"
    "Fonts/Module/ISystemFontsPrivate.h"
    "Fonts/Module/SystemFonts.h"
    "Fonts/Module/SystemFonts.cpp"
    "Fonts/Module/Processors/CompileFontsProcessor.h"
    "Fonts/Module/Processors/CompileFontsProcessor.cpp"
    "Fonts/Module/Processors/RefreshFontsProcessor.h"
    "Fonts/Module/Processors/RefreshFontsProcessor.cpp"
    "Fonts/Module/Messages/FontCompiledMessage.h"
    "Fonts/Module/Messages/CompileFontMessage.h"
    "Fonts/Module/Messages/FontsRefreshCompletedMessage.h"
    "Application.cpp"
    "Application.h"    
    "Catalog/Interface/EntryPath.cpp"
    "Catalog/Interface/EntryPath.h"
    "Catalog/Interface/EntryType.h"
    "Catalog/Interface/ICloneEntry.h"
    "Catalog/Interface/IConfigEntry.h"
    "Catalog/Interface/IDirectoryEntry.h"
    "Catalog/Interface/IEntry.h"    
    "Catalog/Interface/IGeometryEntry.h"
    "Catalog/Interface/IGroupEntry.h"
    "Catalog/Interface/ILocalizedEntry.h"
    "Catalog/Interface/IMaterialEntry.h"
    "Catalog/Interface/IPackageEntry.h"
    "Catalog/Interface/IProxyEntry.h"
    "Catalog/Interface/ISharedEntry.h"
    "Catalog/Interface/ITextEntry.h"
    "Catalog/Interface/ITransformEntry.h"
    "Catalog/Module/Clone.cpp"    
    "Catalog/Module/Clone.h"    
    "Catalog/Module/ConfigEntry.cpp"    
    "Catalog/Module/ConfigEntry.h"    
    "Catalog/Module/GeometryEntry.cpp"    
    "Catalog/Module/GeometryEntry.h"    
    "Catalog/Module/GroupEntry.cpp"    
    "Catalog/Module/GroupEntry.h"    
    "Catalog/Module/TransformPackageEntry.cpp"
    "Catalog/Module/TransformProxyEntry.cpp"
    "Catalog/Module/TransformEntry.h"
    "Catalog/Module/MaterialEntry.h"
    "Catalog/Module/MaterialEntry.cpp"
    "Catalog/Module/ObjectEntry.cpp"
    "Catalog/Module/ObjectEntry.h"
    "Catalog/Module/LocalizedEntry.h"        
    "Catalog/Module/LocalizedEntry.cpp"      
    "Catalog/Module/TextEntry.h"
    "Catalog/Module/ProxyEntry.h"
    "Catalog/Module/TextEntry.cpp")

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
        