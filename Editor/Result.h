#pragma once

#include <string>
#include "IReferenced.h"

namespace Vandrouka {

class IError : public IReferenced {
public:
  virtual std::int32_t GetSeverity() = 0;
  virtual std::string ToString() const = 0;
};

template <typename T> struct Result {
public:
  Result() : _result{} {}
  Result(T result) : _result{result} {}

  Result(Ref<IError> error) : _error{error} {}
  Result(IError *error) : _error{error} {}

  ~Result() {
    if (_error) {
      assert(_error); // TODO: Push to unhandled procedure
    }
  }

  T operator->() const {
    assert(!_error);
    return this->_result;
  }

  T Value() const {
    assert(!_error);
    return this->_result;
  }

  T Value(T def) const {
    if (!_error) {
      return this->_result;
    }
    return def;
  }

  operator bool() const { return this->_error.Get() == nullptr; }

  Ref<IError> Error() const { return this->_error; };

  template <typename OnValid, typename OnError>
  auto Map(OnValid onValid, OnError onError) {
    if (_error) {
      return onError(_error);
    } else {
      return onValid(_result);
    }
  }

  template <typename OnValid> auto Map(OnValid onValid) {
    if (_error) {
      return decltype(onValid(this->_result))(_error);
    } else {
      return onValid(_result);
    }
  }

  template <typename OnError> auto WhenError(OnError onError) {
    if (_error) {
      return onError(_error);
    } else {
      return decltype(onError(_error)){_result};
    }
  }

  template <typename OnValid> auto WhenValid(OnValid onValid) {
    if (!_error) {
      return onValid(_result);
    } else {
      return decltype(onValid()){_error};
    }
  }

private:
  T _result;
  Ref<IError> _error;
};

template <> struct Result<void> {
public:
  Result() {}
  Result(Ref<IError> error) : _error{error} {}
  Result(IError *error) : _error{error} {}

  ~Result() {
    if (_error) {
      assert(_error); // TODO: Push to unhandled procedure
    }
  }

  operator bool() const { return _error.Get() == nullptr; }

  Ref<IError> Error() const { return this->_error; };

  template <typename OnValid, typename OnError>
  auto Map(OnValid onValid, OnError onError) {
    if (this->_error) {
      return onError(this->_error);
    } else {
      return onValid();
    }
  }

  template <typename OnValid> auto Map(OnValid onValid) {
    if (this->_error) {
      return decltype(onValid()){this->_error};
    } else {
      return onValid();
    }
  }

  template <typename OnError> auto WhenError(OnError onError) {
    if (_error) {
      return onError(_error);
    } else {
      return decltype(onError(_error)){};
    }
  }

  template <typename OnValid> auto WhenValid(OnValid onValid) {
    if (!_error) {
      return onValid();
    } else {
      return decltype(onValid()){_error};
    }
  }

private:
  Ref<IError> _error;
};

template <typename U> Result<U> CheckMe(Result<U> r, auto onError) {
  if (!r) {
    onError(r.Error());
    return {};
  }
  return r;
}

#ifdef _DEBUG
#define CHECK(X) CheckMe(X, onError)
#else
#define CHECK(X) X
#endif

#define _next_ | [&](auto &&...args)

template <typename T, typename U>
auto operator|(const Result<T> &prev, U next) {
  if (prev) {
    return next(prev.Value());
  } else {
    return decltype(next(prev.Value())){prev.Error()};
  }
}

template <typename U> auto operator|(const Result<void> &prev, U next) {
  if (prev) {
    return next();
  } else {
    return decltype(next()){prev.Error()};
  }
}

template <> struct GetIID<IError> {
  static constexpr InterfaceId Id = {{0x1d, 0x2c, 0x8c, 0x73, 0x70, 0xb0, 0x49,
                                      0x96, 0x8a, 0xaf, 0x7f, 0xb1, 0x6a, 0xf1,
                                      0x72, 0x7d}};
};

} // namespace Vandrouka
