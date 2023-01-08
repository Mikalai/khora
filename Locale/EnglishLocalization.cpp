#include "EnglishLocalization.h"

std::string* EnglishLocalization::GetString(const std::string& value)
{
	auto it = table.find(value);
	if (it == table.end()) {
		it = table.insert(std::pair<std::string, std::string>(value, value)).first;
	}
	return &it->second;
}

