#pragma once

#include "Observer.h"

namespace Vandrouka::Fundamental::Private {

void ObserverWrapper::OnNext(Ref<IMessage> msg) { _wnd->OnNext(msg); }

void ObserverWrapper::OnError(Ref<IError> error) { _wnd->OnError(error); }

void ObserverWrapper::OnComplete() { _wnd->OnComplete(); }

void MessageSinkWrapper::SubmitMessage(Ref<IMessage> msg) {
  _sink->SubmitMessage(msg);
}

void MessageSinkWrapper::SubmitError(Ref<IError> msg) {
  _sink->SubmitError(msg);
}

} // namespace Vandrouka
