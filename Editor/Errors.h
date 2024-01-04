#pragma once
#include "IReferenced.h"
#include <string>

const int EDITOR_NO_ERROR = 0;
const int EDITOR_ERROR_FILE_NOT_FOUND = 1;
const int EDITOR_ERROR_INVALID_ARGUMENTS = 2;
const int EDITOR_ERROR_PROJECT_FILE_IS_NOT_VALID = 3;
const int LOG_EMPTY_PACKAGE_REFERENCE = 4;
const int LOG_ENTRY_NOT_FOUND = 5;
const int LOG_ENTRY_ALREADY_EXISTS = 6;
const int LOG_ENTRY_BUSY = 7;
const int LOG_ENTRY_COMPILATION_FAILED = 8;
const int LOG_TYPE_MISMATCH = 9;
const int LOG_IO_ERROR = 10;
const int LOG_VSGXCHANGE_NOT_FOUND = 11;
const int LOG_FILE_LOAD_FAILED = 12;
const int LOG_OPERATION_NOT_SUPPORTED = 13;

const int LOG_LEVEL_WARNING = 3;
const int LOG_LEVEL_ERROR = 4;

struct LogNotification {
  int Level{};
  int Code{};
  std::string StrParamter{};
  int IntParameter{};
  double RealParameter{};
};

inline auto LogWarning(auto... args) {
  LogNotification r{LOG_LEVEL_WARNING, args...};
  return r;
}

inline auto LogError(auto... args) {
  LogNotification r{LOG_LEVEL_ERROR, args...};
  return r;
}

const std::string ErrorToString(const LogNotification &error);

namespace Vandrouka {
class IError : public IReferenced {
public:
  virtual std::int32_t GetSeverity() = 0;
  virtual std::string ToString() const = 0;
};

template <> struct GetIID<IError> {
  static constexpr InterfaceId Id = {{0x1d, 0x2c, 0x8c, 0x73, 0x70, 0xb0, 0x49,
                                      0x96, 0x8a, 0xaf, 0x7f, 0xb1, 0x6a, 0xf1,
                                      0x72, 0x7d}};
};

template <typename Derived, typename Interface>
class ErrorBase : public ReferenceCountedBase<Derived, Interface> {
public:
  bool QueryInterface(const InterfaceId &id, void **o) override {
    if (id == GetIID<Interface>::Id) {
      *o = static_cast<Interface *>(this);
    } else if (id == GetIID<IError>::Id) {
      *o = static_cast<IError *>(this);
    } else if (id == GetIID<IReferenced>::Id) {
      *o = static_cast<IReferenced *>(this);
    } else {
      *o = nullptr;
    }

    if (*o) {
      this->AddRef();
    }

    return *o != nullptr;
  }
};

template <typename... Args>
class GenericError : public ErrorBase<GenericError<Args...>, IError> {
public:
  GenericError(int severity, int code, Args... args)
      : _severity{severity}, _code{code}, _args{std::forward<Args>(args)...} {}

  std::int32_t GetSeverity() override { return this->_severity; }

  std::string ToString() const override {
    switch (this->_code) {
    case EDITOR_NO_ERROR:
      return "";
    case EDITOR_ERROR_FILE_NOT_FOUND:
      return "File " + std::get<std::string>(this->_args) + " not found.";
    case EDITOR_ERROR_PROJECT_FILE_IS_NOT_VALID:
      return "Project file contains invalid data. " +
             std::get<std::string>(this->_args);
    case LOG_ENTRY_ALREADY_EXISTS:
      return "Entry '" + std::get<std::string>(this->_args) +
             "' already exists.";
    case LOG_ENTRY_NOT_FOUND:
      return "Entry '" + std::get<std::string>(this->_args) +
             "' was not found.";
    case LOG_ENTRY_BUSY:
      return "Requested operation can't be executed because resource is "
             "busy.";
    case LOG_ENTRY_COMPILATION_FAILED:
      return "Compilation '" + std::get<std::string>(this->_args) + "' failed.";
    case LOG_TYPE_MISMATCH:
      return "Type mismatch";
    case LOG_IO_ERROR:
      return "IO error. " + std::get<std::string>(this->_args);
    case LOG_VSGXCHANGE_NOT_FOUND:
      return "Editor was build without vsgXchange support.";
    case LOG_FILE_LOAD_FAILED:
      return "Failed to load file '" + std::get<std::string>(this->_args) + "'";
    case LOG_OPERATION_NOT_SUPPORTED:
      return "Operation is not supported. " +
             std::get<std::string>(this->_args);
    default:
      return "Unknown error.";
    }
  }

private:
  int _severity{0};
  int _code{0};
  std::tuple<Args...> _args;
};
} // namespace Vandrouka