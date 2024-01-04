#pragma once

#include <compare>
#include <string>

#include "IObserver.h"
#include "Observer.h"

namespace Vandrouka {

struct LongOperation {
  std::string Name{};
  std::string Description{};

  auto operator<=>(const LongOperation &) const = default;
};

class ILongOperationStartedMessage : public IMessage {
public:
  virtual const LongOperation &GetOperation() const = 0;
};

template <> struct GetIID<ILongOperationStartedMessage> {
  static constexpr InterfaceId Id = {{0x87, 0xef, 0xf8, 0xeb, 0xd3, 0x94, 0x42,
                                      0x2e, 0x8c, 0xcc, 0xdc, 0x64, 0x94, 0x63,
                                      0x50, 0x11}};
};

class ILongOperationEndedMessage : public IMessage {
public:
  virtual const LongOperation &GetOperation() const = 0;
};

template <> struct GetIID<ILongOperationEndedMessage> {
  static constexpr InterfaceId Id = {{0xc9, 0xfc, 0x4e, 0x1f, 0xe2, 0xe, 0x4d,
                                      0x74, 0xa5, 0xa4, 0x96, 0x40, 0x89, 0xa,
                                      0x4c, 0x6d}};
};

template <typename T, typename OnNextFunc> struct LongOperationScope {

  class LongOperationStartedMessage
      : public MessageBase<LongOperationStartedMessage,
                           ILongOperationStartedMessage> {
  public:
    LongOperationStartedMessage(LongOperation op) : _op{std::move(op)} {}

    const LongOperation &GetOperation() const override { return _op; }

  private:
    LongOperation _op;
  };

  class LongOperationEndedMessage
      : public MessageBase<LongOperationEndedMessage,
                           ILongOperationEndedMessage> {
  public:
    LongOperationEndedMessage(LongOperation op) : _op{std::move(op)} {}

    const LongOperation &GetOperation() const override { return _op; }

  private:
    LongOperation _op;
  };

  LongOperationScope(T &self, OnNextFunc onNext, LongOperation op)
      : _self{self}, _onNext{onNext}, _op{op} {
    (_self.*_onNext)(new LongOperationStartedMessage{_op});
  }

  ~LongOperationScope() {
    (_self.*_onNext)(new LongOperationEndedMessage{_op});
  }

private:
  T &_self;
  OnNextFunc _onNext;
  LongOperation _op;
};

} // namespace Vandrouka

struct LongOperation {
  std::string Name{};
  std::string Description{};

  auto operator<=>(const LongOperation &) const = default;
};

struct LongOperationStarted {
  LongOperation Operation;
  // TODO: Add cancel source
};

struct LongOperationEnded {
  LongOperation Operation;
  // TODO: Add cancel source
};

template <typename T, typename Start, typename End> struct LongOperationScope {
  LongOperationScope(T &self, Start start, End end, LongOperation op)
      : _self{self}, _start{start}, _end{end}, _op{op} {
    (_self.*_start)(LongOperationStarted{.Operation = _op});
  }

  ~LongOperationScope() { (_self.*_end)(LongOperationEnded{.Operation = _op}); }

private:
  T &_self;
  Start _start;
  End _end;
  LongOperation _op;
};
