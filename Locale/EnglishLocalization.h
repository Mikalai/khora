#pragma once

#include <map>
#include <Locale/ILocalization.h>

class EnglishLocalization : public ILocalization {
public:

    virtual std::string* GetString(const std::string& value) override;

private:
    std::map<std::string, std::string> table;
};