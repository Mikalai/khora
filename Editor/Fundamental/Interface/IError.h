#pragma once

#include <Fundamental/Interface/IReferenced.h>
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
const int LOG_NOT_IMPLEMENTED = 14;
const int LOG_INDEX_OUT_OF_RANGE = 15;

namespace Vandrouka {
namespace Fundamental {

class IError : public IReferenced {
public:
  virtual std::int32_t GetSeverity() = 0;
  virtual std::string ToString() const = 0;
};

Ref<IError> CreateError(int code, std::string arg = {});
Ref<IError> CreateWarning(int code, std::string msg = {});

} // namespace Fundamental

using Fundamental::CreateError;
using Fundamental::CreateWarning;
using Fundamental::IError;

} // namespace Vandrouka

DECLARE_IID(Vandrouka::Fundamental::IError, 0x1d, 0x2c, 0x8c, 0x73, 0x70, 0xb0,
            0x49, 0x96, 0x8a, 0xaf, 0x7f, 0xb1, 0x6a, 0xf1, 0x72, 0x7d);
