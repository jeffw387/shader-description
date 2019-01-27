#pragma once
#include <fmt/format.h>
#include <string>
#include <string_view>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
namespace jshd {
std::string make_image(
  uint32_t set, 
    uint32_t binding, 
    std::string_view imageType, 
    std::string_view imageName, 
    uint32_t count) {
      auto countFormatted = (count > 1 ? fmt::format("[{}]", count) : fmt::format(""));
      return fmt::format("layout(set = {}, binding = {}) uniform {} {}{};",
        set,
        binding,
        imageType,
        imageName,
        countFormatted);
    }
}