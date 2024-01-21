#pragma once
#include <Fundamental/Module/Referenced.h>
#include <Fundamental/Interface/Result.h>
#include <cassert>
#include <string>

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

namespace Vandrouka::Fundamental::Private {

template <typename... Args>
class GenericError
    : public Fundamental::Private::ReferenceCountedBase<GenericError<Args...>,
                                                        IError> {
public:
  using Interfaces =
      QueryInterfaces<GenericError<Args...>, IError, IReferenced>;

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
    case LOG_NOT_IMPLEMENTED:
      return "Operation is not implemented. " +
             std::get<std::string>(this->_args);
    case LOG_INDEX_OUT_OF_RANGE:
      return "Operation is out of range. " + std::get<std::string>(this->_args);
    default:
      return "Unknown error.";
    }
  }

private:
  int _severity{0};
  int _code{0};
  std::tuple<Args...> _args;
};

template <ReferenceCounted T>
inline void Map(Ref<T> o, std::function<void(Ref<T>)> onValid,
                std::function<void(Ref<IError>)> onInvalid) {
  if (o) {
    onValid(o);
  } else {
    onInvalid(new GenericError(LOG_LEVEL_ERROR, LOG_NOT_IMPLEMENTED,
                               std::string("")));
  }
}

template <ReferenceCounted T, ReferenceCounted U>
inline std::pair<Ref<T>, Ref<IError>> Cast(Ref<U> o) {
  if (auto v = o.Cast<T>(); v) {
    return {v, {}};
  } else {
    return {{},
            new GenericError(LOG_LEVEL_ERROR, LOG_NOT_IMPLEMENTED,
                             std::string(""))};
  }
}

inline Ref<IError> NotFoundError(const std::string &value) {
  return new GenericError{LOG_LEVEL_ERROR, LOG_ENTRY_NOT_FOUND, value};
}

} // namespace Vandrouka::Fundamental::Private
