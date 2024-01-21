#include <Fundamental/Module/Errors.h>

namespace Vandrouka::Fundamental {

Ref<IError> CreateError(int code, std::string msg) {
  return new Private::GenericError{LOG_LEVEL_ERROR, code, msg};
}

Ref<IError> CreateWarning(int code, std::string msg) {
  return new Private::GenericError{LOG_LEVEL_WARNING, code, msg};
}

} // namespace Vandrouka::Fundamental::Private

const std::string ErrorToString(const LogNotification &error) {
  switch (error.Code) {
  case EDITOR_NO_ERROR:
    return "";
  case EDITOR_ERROR_FILE_NOT_FOUND:
    return "File " + error.StrParamter + " not found.";
  case EDITOR_ERROR_PROJECT_FILE_IS_NOT_VALID:
    return "Project file contains invalid data. " + error.StrParamter;
  case LOG_ENTRY_ALREADY_EXISTS:
    return "Entry '" + error.StrParamter + "' already exists.";
  case LOG_ENTRY_NOT_FOUND:
    return "Entry '" + error.StrParamter + "' was not found.";
  case LOG_ENTRY_BUSY:
    return "Requested operation can't be executed because resource is "
           "busy.";
  case LOG_ENTRY_COMPILATION_FAILED:
    return "Compilation '" + error.StrParamter + "' failed.";
  case LOG_TYPE_MISMATCH:
    return "Type mismatch";
  case LOG_IO_ERROR:
    return "IO error. " + error.StrParamter;
  case LOG_VSGXCHANGE_NOT_FOUND:
    return "Editor was build without vsgXchange support.";
  case LOG_FILE_LOAD_FAILED:
    return "Failed to load file '" + error.StrParamter + "'";
  case LOG_OPERATION_NOT_SUPPORTED:
    return "Operation is not supported. " + error.StrParamter;
  default:
    return "Error " + error.StrParamter + "; " +
           std::to_string(error.IntParameter) +
           std::to_string(error.RealParameter);
  }
}
