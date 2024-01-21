#pragma once

#include <compare>
#include <string>

#include <Fundamental/Interface/LongOperation.h>
#include <Fundamental/Module/Messages/LongOperationEndedMessage.h>
#include <Fundamental/Module/Messages/LongOperationStartedMessage.h>

namespace Vandrouka::Fundamental::Private {

template <typename T, typename OnNextFunc> struct LongOperationScope {

  LongOperationScope(T &self, OnNextFunc onNext, LongOperation op)
      : _self{self}, _onNext{onNext}, _op{op} {
    (_self.*_onNext)(new Messages::LongOperationStartedMessage{_op});
  }

  ~LongOperationScope() {
    (_self.*_onNext)(new Messages::LongOperationEndedMessage{_op});
  }

private:
  T &_self;
  OnNextFunc _onNext;
  LongOperation _op;
};

} // namespace Vandrouka::Fundamental::Private
