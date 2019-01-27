#pragma once
#include <string>
#include <string_view>

struct split_view {
  std::string_view before;
  std::string_view after;
};

split_view split_after(std::string_view whole, std::string_view token) {
  split_view result{};
  auto findPos = whole.find(token);
  if (findPos != std::string::npos) {
    auto afterTokenPos = findPos + token.length();
    result.before = whole.substr(0, afterTokenPos);
    result.after = whole.substr(afterTokenPos, whole.length() - afterTokenPos);
    return result;
  }
  result.before = whole;
  return result;
}