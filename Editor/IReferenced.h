#pragma once

#include <atomic>
#include <boost/uuid/uuid.hpp>
#include <cstdint>
#include <functional>

namespace Vandrouka {

using ClassId = boost::uuids::uuid;
using InterfaceId = boost::uuids::uuid;

class IReferenced {
public:
  virtual void AddRef() = 0;
  virtual void Release() = 0;
  virtual bool QueryInterface(const InterfaceId &id, void **o) = 0;
};

template <typename T>
concept ReferenceCounted = requires(T a) {
  { std::is_base_of_v<IReferenced, T> };
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

  Ref(const Ref<T> &o) : _o{o._o} {
    if (this->_o) {
      this->_o->AddRef();
    }
  }

  template <ReferenceCounted U> Ref(const Ref<U> &o) {
    auto v = o.template Cast<U>();
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

  T *operator->() { return this->_o; }

  const T *operator->() const { return this->_o; }

  operator bool() const { return this->_o != nullptr; }

  T *Get() { return this->_o; }

  T *Get() const { return this->_o; }

  T *Release() {
    auto r = this->_o;
    this->_o = nullptr;
    return r;
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

template <typename Derived, typename MainInterface>
struct QueryInterfacesStruct<Derived, MainInterface> {

  static bool Query(Derived *derived, const InterfaceId &iid, void **o) {
    if (iid == GetIID<IReferenced>::Id) {
      *o = static_cast<IReferenced *>(static_cast<MainInterface *>(derived));
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

template <ReferenceCounted Derived, ReferenceCounted... Interfaces>
class ReferenceCountedBase : public Interfaces... {

public:
  virtual ~ReferenceCountedBase() {}

  void AddRef() override { this->_refCount++; }

  void Release() override {
    if (--this->_refCount == 0) {
      delete (Derived *)this;
    }
  }

  bool QueryInterface(const InterfaceId &id, void **o) override {
    return Private::QueryInterfacesStruct<
        Derived, std::tuple_element_t<0, std::tuple<Interfaces...>>,
        Interfaces...>::Query((Derived *)this, id, o);
  }

  Ref<Derived> Self() { return Ref<Derived>{(Derived *)this}; }

private:
  std::atomic<std::uint64_t> _refCount{0};
};

template <class T> T *get_pointer(Ref<T> const &p) { return p.Get(); }

} // namespace Vandrouka
