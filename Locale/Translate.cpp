#include <cassert>
#include "Translate.h"
#include "ILocalization.h"
#include "EnglishLocalization.h"

EnglishLocalization g_englishLocalization;
ILocalization* g_currentLocale = &g_englishLocalization;

const std::string& tr(const std::string& value) {
    assert(g_currentLocale != nullptr);
    return *g_currentLocale->GetString(value);
}

void SetLocalization(ILocalization* locale) {
    g_currentLocale = locale;
}