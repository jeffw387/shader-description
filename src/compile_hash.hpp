#pragma once
#include <string_view>

namespace jshd {
constexpr unsigned int hash(std::string_view str, int h = 0) {
  return !str[h] ? 5381 : (hash(str, h + 1) * 33) ^ str[h];
}
}  // namespace jshd