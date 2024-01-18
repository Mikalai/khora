#pragma once

#include "../IDataModelEditor.h"
#include "../IDataModelObserver.h"
#include "../IReferenced.h"
#include "../DataModel/ICompilationState.h"
#include "../Observer.h"

namespace Vandrouka {

class CompileSceneMessage
    : public MessageBase<CompileSceneMessage, ICompileSceneMessage> {
public:
  CompileSceneMessage(EntryPath path) : _path{path} {}
  EntryPath GetRoot() const override { return _path; }

private:
  EntryPath _path;
};

class FontsCompilationJobsCompleteMessage
    : public MessageBase<FontsCompilationJobsCompleteMessage,
                         IFontsCompilationJobsCompleteMessage> {
public:
  FontsCompilationJobsCompleteMessage(const Ref<ICompilationState> &_state)
      : _state(_state) {}

  Ref<ICompilationState> GetState() const { return _state; }

private:
  Ref<ICompilationState> _state;
};

} // namespace Vandrouka
