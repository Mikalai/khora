#pragma once

#include "IReferenced.h"
#include "IToString.h"

#define CREATE_STATE_WRAPPER(X, ...)                                           \
  class X;                                                                     \
  class I##X##StateWrapper;                                                    \
  class X##StateWrapper;                                                       \
  class I##X##StateWrapper : public ::Vandrouka::IReferenced {                 \
  public:                                                                      \
    virtual X *GetState() = 0;                                                 \
  };                                                                           \
                                                                               \
  template <> struct GetIID<I##X##StateWrapper> {                              \
    static constexpr InterfaceId Id = {{__VA_ARGS__}};                         \
  };                                                                           \
                                                                               \
  class X##StateWrapper                                                        \
      : public ::Vandrouka::ReferenceCountedBase<X##StateWrapper,              \
                                                 I##X##StateWrapper> {         \
  public:                                                                      \
    X##StateWrapper(X *state) : _state{state} {}                               \
    X *GetState() override { return _state; }                                  \
                                                                               \
  private:                                                                     \
    X *_state;                                                                 \
  }


namespace Vandrouka {

namespace Private {
template <typename Derived, typename MainInterface,
          ReferenceCounted... Interfaces>
struct QueryInterfacesStruct;

template <typename Derived, typename MainInterface, ReferenceCounted Interface,
          ReferenceCounted... Other>
struct QueryInterfacesStruct<Derived, MainInterface, Interface, Other...>
    : public QueryInterfacesStruct<Derived, MainInterface, Other...> {

  using Base = QueryInterfacesStruct<Derived, MainInterface, Other...>;

  static bool Query(Derived *derived, const InterfaceId &id, void **o) {

    if (Base::Query(derived, id, o)) {
      return true;
    }

    if (id == GetIID<Interface>::Id) {
      *o = static_cast<Interface *>(derived);
    } else {
      *o = nullptr;
    }

    if (*o) {
      static_cast<MainInterface *>(derived)->AddRef();
    }

    return *o != nullptr;
  }
};

template <typename Derived, typename MainInterface, typename Interface>
struct QueryInterfacesStruct<Derived, MainInterface, Interface> {

  static bool Query(Derived *derived, const InterfaceId &iid, void **o) {
    if (iid == GetIID<IReferenced>::Id) {
      *o = static_cast<Interface *>(static_cast<MainInterface *>(derived));
    } else {
      *o = nullptr;
    }

    if (*o) {
      static_cast<MainInterface *>(derived)->AddRef();
    }

    return *o != nullptr;
  }
};
} // namespace Private

template <typename Derived, typename... Interfaces>
using QueryInterfaces = Private::QueryInterfacesStruct<
    Derived, std::tuple_element_t<0, std::tuple<Interfaces...>>, Interfaces...>;

template <ReferenceCounted Derived, ReferenceCounted... I>
class ReferenceCountedBase : public I... {

public:
  using Interfaces = QueryInterfaces<Derived, I..., IReferenced>;
  virtual ~ReferenceCountedBase() {}

  void AddRef() override { this->_refCount++; }

  void Release() override {
    if (--this->_refCount == 0) {
      delete (Derived *)this;
    }
  }

  bool QueryInterface(const InterfaceId &id, void **o) override {
    return Derived::Interfaces::Query((Derived *)this, id, o);
  }

  Ref<Derived> Self() { return Ref<Derived>{(Derived *)this}; }

private:
  std::atomic<std::uint64_t> _refCount{0};
};

} // namespace Vandrouka
