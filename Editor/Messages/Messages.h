#pragma once

#include "../IDataModelEditor.h"
#include "../IDataModelObserver.h"
#include "../IReferenced.h"
#include "../Observer.h"

namespace Vandrouka {
//
//class CompileMessage : public MessageBase<CompileMessage, ICompileMessage> {
//public:
//  CompileMessage(vsg::ref_ptr<vsg::Node> _node, Ref<IAsyncTask> _completion)
//      : _node(_node), _completion(_completion) {}
//
//  vsg::ref_ptr<vsg::Node> GetResultObject() override { return _node; }
//
//  Ref<IAsyncTask> GetCompletion() override { return _completion; }
//
//private:
//  vsg::ref_ptr<vsg::Node> _node;
//  Ref<IAsyncTask> _completion;
//};
//
//
//class SceneCompeledMessage
//    : public MessageBase<SceneCompeledMessage, ISceneCompeledMessage> {
//public:
//  SceneCompeledMessage(vsg::ref_ptr<vsg::Node> root) : _root{root} {}
//  vsg::ref_ptr<vsg::Node> GetRoot() const override { return _root; }
//
//private:
//  vsg::ref_ptr<vsg::Node> _root;
//};
//
//class CompileFontMessage
//    : public MessageBase<CompileFontMessage, ICompileFontMessage> {
//public:
//  CompileFontMessage(std::string name, Ref<IReferenced> state)
//      : _name{name}, _state{state} {}
//
//  const std::string &GetDisplayName() const override { return _name; }
//  Ref<IReferenced> GetState() const override { return _state; }
//
//private:
//  std::string _name;
//  Ref<IReferenced> _state;
//};
//
//
//
//
//class ModelResetMessage
//    : public MessageBase<ModelResetMessage, IModelResetMessage> {
//  const MessageId &GetTypeID() const override {
//    static MessageId id{{0x97, 0xd4, 0x17, 0xa, 0x15, 0xf8, 0x4d, 0x5, 0xb9,
//                         0x24, 0xbe, 0x23, 0x45, 0xd7, 0xbb, 0xed}};
//    return id;
//  }
//};
//
//class ConfigChangedMessage
//    : public MessageBase<ConfigChangedMessage, IConfigChangedMessage> {
//public:
//  ConfigChangedMessage(Ref<IConfigEntry> cfg) : _config{cfg} {}
//
//  Ref<IConfigEntry> GetConfig() const override { return _config; }
//
//private:
//  Ref<IConfigEntry> _config;
//};
//

} // namespace Vandrouka