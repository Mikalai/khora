#pragma once

#include <string>

class ILocalization;

const std::string& tr(const std::string& value);
void SetLocalization(ILocalization* locale);