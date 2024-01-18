#pragma once

#include <string>
#include <codecvt>

inline std::wstring utf8_to_wstring(const std::u8string &str) {
  std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
  return myconv.from_bytes((const char *)str.c_str());
}
