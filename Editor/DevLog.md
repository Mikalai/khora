# __EDITOR__
## Terms
Here I might use some words that probably are widely used in other tools, so to avoid misunderstanding here are some clarifications for the terms used here
- _Assets package_ - source of elements that can be used in the final scene.
- _Final scene_ - the main output of this editor. Composed vsgb file with named nodes that can be used as ready to use data source for the program.
## Goals
This program is created with next use cases in mind:
- Blender is great tool to create 3D models and it can export scenes to variety formats. vsgXchange is a great tool to convert scenes to native vsg format. But after all conversions content of the resulted scene can be different because vsg operates with low level vulkan entities and instances that where named in the Blender most of the time are lost or represented differently. That is why I need a way to fine tune the resulted scene for further usage.
- I like the idea of assets packages. It is possible to create a scene in Blender with specific elements and later use that scene as a source of elements for the final scene. Thus this editor should help with combining different assets into final scene.

## Main windows with VSG viewport
Well, this editor mimics to any other editors. It has a main view with 3D scene that can preview assets packages and final scene. 

### _New knowledge_
By default wxWidgets generate idle event once per second. To increase amount of idle notifications (this is needed for smooth animation) ```evt.RequestMore(true)``` can be used in the idle handler to request more idle events.

## Side tree view with imported packages

## Side tree view with composed final scene
### _New knowledges_
- To perform drag and drop ```wxDropSource``` can be used with conjunction ```wxTextDataObject wxTextDropTarget```

## Toolbar on main window
### _New knowledges_
- To load icons wxArtProvider can be used. 
- By default png images can't be loaded. ```wxInitAllImageHandlers``` adds support for different image formats, thus ```wxBitmap::LoadFile``` can handle png with transparancy.
- Convinient way to get current program location/directory ```boost::dll::program_location().parent_path()```
### Navigate to selected transform node 
When clicked changes look at of the track ball and starts animated camera move to the selected node.

## Menu Bar
### File menu
Contains commands to import/export data that is required to construct final scene. 
- Load Project: Loads previously saved project.
- Save Project: Save current project to json file.
- Reset Project: Clear all internal structure and effectively reverts everythin to empty project.
- Import: Imports vsgb files as assets packages.
- Export: Exports final scene to vsgb scene.

## Data Model
Main part of the data model is root directory entry. Every entry can be reference by string in the format root/a/b/c. Entry types are **transform**, **material**, **geometry**, **config**, **group**. At the same type each of this type can be represented in different way. For example asset package has trasnform nodes. This node from assets package is represented by ```TransformPackageEntry```. When this node is dragged to the final scene it is wrapped as ```TransformProxyEntry```. ```TransformProxyEntry``` provides ability to be modified and overriden. If overriden when final scene is exported overriden values are exported to the final scene. Also when transform entry is exposed to UI modification ```TransformViewEntry``` is created that synchronizes access to the entry property over provided ```AsyncQueue```. Thus besides type, entries can represent data from packages, a reference to package entry, a view entry that can be modified from UI or any other thread.

### TransformEntry
Entry contains information about local transform. Transforms from packages are represented by ```TransformPackageEntry```. Transform that refereneces to the package entry is represented by ```TransformProxyEntry```. Transform that is exposed to arbitrary access is represented by ```TransformViewEntry```.

### MaterialEntry
Entry contains information about states.

### GeometryEntry
Entry contains draw commands and buffers.


### _Design decisions_
- This is a UI tool application that require more flexibility than high speed optimization. That is why quite heavy usage of polymorphic types is used. The whole datamodel is represented with ```DataModel``` class which is a wrapper around kind of virtual filesystem-like structure. This approach allows referencing by paths. But instead of files there are leaf nodes that represented different aspects of the project. 
- To minimize UI thread lags data model operations are supposed to be executed asynchronously utilizing thread pool. Syncrhonization is achieved using ```AsyncQueue``` type. Thus when other threads invoke commands to the model, requests are redirected firstly to the queue and and queue dispatched this requests one by one to the thread pool. 
- Data model memory management relies on std::shared_ptr. At least now it simplifies implementation, though probably it is worth to switch to intrusive reference counters for better performance if needed.

## Localization
Editor should be able to produce different export based on required final language. For locaization there is a special entry: ```LocalizedEntry```. When another entry is added to localized entry its name should represent the language. During scene compilation compiler can take into account localized entries and select only subset nodes. To add/remove/modify language a Localization can be used.  
vsg uses compiled fonts. That is why there is a separate tab to manage fonts where nots can be imported and converted is vsgXchange is available. Once at least one font is imported it is possible to add text nodes. Text nodes can't be part of packages because text is pretty compound entity with bunch of specific properties that should be tuned inside this editor. Among this properties are: font, text.