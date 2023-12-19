#include "EntryPath.h"

EntryPath EntryPath::GetNext() const {
    auto index = Path.find('/');
    if (index == std::string::npos)
        return {};
    return { Path.substr(index + 1) };
}

std::string EntryPath::GetName() const {
    auto index = Path.find('/');
    if (index == std::string::npos)
        return Path;
    return Path.substr(0, index);
}

std::string EntryPath::GetLeafName() const {
    auto index = Path.rfind('/');
    if (index == std::string::npos)
        return Path;

    return Path.substr(index + 1);
}

EntryPath EntryPath::GetParent() const {
    auto index = Path.rfind('/');
    if (index == std::string::npos)
        return {};
    return { Path.substr(0, index) };
}

EntryPath EntryPath::Append(const std::string name) const {
    if (Path.empty()) {
        return { name };
    }
    return { Path + "/" + name };
}

bool EntryPath::IsValid() const {
    return !Path.empty();
}
