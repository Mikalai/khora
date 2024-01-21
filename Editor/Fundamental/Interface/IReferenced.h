#pragma once

#include <atomic>
#include <boost/uuid/uuid.hpp>
#include <cassert>
#include <concepts>
#include <cstdint>
#include <functional>
#include <type_traits>

#define DECLARE_IID(X, ...)                                                    \
  namespace Vandrouka::Fundamental {                                           \
  template <> struct GetIID<X> {                                               \
    static constexpr InterfaceId Id = {{__VA_ARGS__}};                         \
  };                                                                           \
  }

#ifdef DYNAMIC_FACTORY
#else
#define DECLARE_CID(PACKAGE, X, ...)                                           \
  namespace Vandrouka::Instances::PACKAGE {                                    \
  class X;                                                                     \
  }                                                                            \
  namespace Vandrouka::Factory {                                               \
  Vandrouka::Fundamental::IReferenced *Create##X();                            \
  }                                                                            \
  namespace Vandrouka::Fundamental {                                           \
  template <> struct GetCID<Vandrouka::Instances::PACKAGE::X> {                \
    static constexpr InterfaceId Id = {{__VA_ARGS__}};                         \
  };                                                                           \
  }
#endif

namespace Vandrouka {
namespace Fundamental {

using ClassId = boost::uuids::uuid;
using InterfaceId = boost::uuids::uuid;
class IError;

class IReferenced {
public:
  virtual void AddRef() = 0;
  virtual void Release() = 0;
  virtual bool QueryInterface(const InterfaceId &id, void **o) = 0;
};

template <typename T>
concept ReferenceCounted = requires(T a) {
  { std::derived_from<T, IReferenced> };
};

template <ReferenceCounted T> struct GetIID;
template <ReferenceCounted T> struct GetCID;

template <ReferenceCounted T> class Ref {
public:
  Ref() : _o{nullptr} {}

  Ref(T *o) : _o{o} {
    if (this->_o) {
      this->_o->AddRef();
    }
  }

  ~Ref() {
    if (this->_o) {
      this->_o->Release();
      this->_o = nullptr;
    }
  }

  template <typename U> Ref(U *o) {
    if (!o) {
      this->_o = nullptr;
      return;
    }

    o->AddRef();

    if (!o->QueryInterface(GetIID<T>::Id, (void **)&this->_o)) {
      this->_o = nullptr;
    }

    o->Release();
  }

  Ref(const Ref<T> &o) : _o{o._o} {
    if (this->_o) {
      this->_o->AddRef();
    }
  }

  template <ReferenceCounted U> Ref(const Ref<U> &o) {
    auto v = o.template Cast<T>();
    this->_o = v.Release();
  }

  template <ReferenceCounted U> Ref(Ref<U> &&o) {
    auto v = o.template Cast<U>();
    this->_o = v.Release();
    o.Release();
  }

  Ref(Ref<T> &&o) : _o{o._o} { o._o = nullptr; }

  Ref<T> &operator=(const Ref<T> &o) {
    if (this == &o)
      return *this;

    if (this->_o == o._o)
      return *this;

    if (this->_o) {
      this->_o->Release();
      this->_o = nullptr;
    }

    this->_o = o._o;
    if (this->_o) {
      this->_o->AddRef();
    }
    return *this;
  }

  template <ReferenceCounted U> Ref<T> &operator=(const Ref<U> &o) {
    if (this == &o)
      return *this;

    if (this->_o == o._o)
      return *this;

    if (this->_o) {
      this->_o->Release();
      this->_o = nullptr;
    }

    auto v = o.template Cast<U>();
    this->_o = v.Release();

    return *this;
  }

  Ref<T> &operator=(Ref<T> &&o) {
    if (this == &o)
      return *this;

    if (this->_o == o._o)
      return *this;

    if (this->_o) {
      this->_o->Release();
      this->_o = nullptr;
    }

    this->_o = o._o;
    o._o = nullptr;

    return *this;
  }

  template <ReferenceCounted U> Ref<T> &operator=(Ref<U> &&o) {
    if (this == &o)
      return *this;

    if (this->_o == o._o)
      return *this;

    if (this->_o) {
      this->_o->Release();
      this->_o = nullptr;
    }

    this->_o = o._o.template Cast<U>().Release();

    return *this;
  }

  T *operator->() {
    assert(this->_o);
    return this->_o;
  }

  const T *operator->() const {
    assert(this->_o);
    return this->_o;
  }

  operator bool() const { return this->_o != nullptr; }

  T *Get() { return this->_o; }

  T *Get() const { return this->_o; }

  T *Release() {
    auto r = this->_o;
    this->_o = nullptr;
    return r;
  }

  void Reset() {
    if (this->_o) {
      this->_o->Release();
      this->_o = nullptr;
    }
  }

  template <ReferenceCounted U> Ref<U> Cast() const {
    return const_cast<Ref<T> &>(*this).Cast<U>();
  }

  template <ReferenceCounted U> Ref<U> Cast() {
    if (!this->_o) {
      return {};
    }

    U *ptr{nullptr};
    if (this->_o->QueryInterface(GetIID<U>::Id, (void **)&ptr)) {
      Ref<U> r{ptr};
      ptr->Release();
      return r;
    }
    return {};
  }

  template <ReferenceCounted U> auto &When(std::function<void(Ref<U>)> func) {
    if (auto v = this->template Cast<U>(); v) {
      func(v);
    }
    return *this;
  }

private:
  T *_o{nullptr};
};

template <> struct GetIID<IReferenced> {
  static constexpr InterfaceId Id = {{0x8a, 0xd, 0x9, 0x12, 0xfa, 0xed, 0x4d,
                                      0x83, 0xb8, 0xf6, 0xfd, 0xac, 0xd7, 0x8a,
                                      0x28, 0x7c}};
};

bool Create(const ClassId &cid, const InterfaceId &iid, void **obj);

template <ReferenceCounted C, ReferenceCounted T> Ref<T> Create() {
  T *result;
  if (Create(GetCID<C>::Id, GetIID<T>::Id, (void **)&result)) {
    return {result};
  }
  return {};
}

template <class T> T *get_pointer(Ref<T> const &p) { return p.Get(); }
} // namespace Fundamental

using Fundamental::ClassId;
using Fundamental::Create;
using Fundamental::GetCID;
using Fundamental::GetIID;
using Fundamental::IError;
using Fundamental::InterfaceId;
using Fundamental::IReferenced;
using Fundamental::Ref;
using Fundamental::ReferenceCounted;

} // namespace Vandrouka
