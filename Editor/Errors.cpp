#pragma once

#include "Errors.h"

const std::string ErrorToString(const LogNotification& error) {
	switch (error.Code)
	{
	case EDITOR_NO_ERROR:
		return "";
	case EDITOR_ERROR_FILE_NOT_FOUND:
		return "File " + error.StrParamter + " not found.";
	case EDITOR_ERROR_PROJECT_FILE_IS_NOT_VALID:
		return "Project file contains invalid data. " + error.StrParamter;
	case LOG_ENTRY_ALREADY_EXISTS:
		return "Entry '" + error.StrParamter + "' already exists.";
	case LOG_ENTRY_NOT_FOUND:
		return "Entry '" + error.StrParamter + "' was not found";
	default:
		return "Error " + error.StrParamter + "; " + std::to_string(error.IntParameter) + std::to_string(error.RealParameter);
	}
}
