#pragma once
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
const int LOG_OPERATION_NOT_SUPPORTED  = 13;

const int LOG_LEVEL_WARNING = 3;
const int LOG_LEVEL_ERROR = 4;

struct LogNotification {
    int Level;
    int Code;
    std::string StrParamter;
    int IntParameter;
    double RealParameter;
};

inline auto LogWarning(auto... args) {
    LogNotification r{ LOG_LEVEL_WARNING, args... };
    return r;
}

inline auto LogError(auto... args) {
    LogNotification r{ LOG_LEVEL_ERROR, args... };
    return r;
}

const std::string ErrorToString(const LogNotification& error);