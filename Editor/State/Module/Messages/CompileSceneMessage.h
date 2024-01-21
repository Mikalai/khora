#pragma once

#include <Fundamental/Module/MessageBase.h>
#include <State/Interface/Messages/ICompileSceneMessage.h>
#include <Catalog/Interface/EntryPath.h>

namespace Vandrouka::State::Private::Messages {

class CompileSceneMessage
    : public Fundamental::Private::MessageBase<CompileSceneMessage, State::Messages::ICompileSceneMessage> {
public:
  CompileSceneMessage(Catalog::EntryPath path) : _path{path} {}
  Catalog::EntryPath GetRoot() const override { return _path; }

private:
  Catalog::EntryPath _path;
};

} // namespace Vandrouka
