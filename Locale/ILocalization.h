#pragma once

#include <string>

class ILocalization {
public:
    virtual const std::string* GetString(const std::string& value) = 0;
};
