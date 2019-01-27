#pragma once
#include <fmt/format.h>
#include <string>
#include <string_view>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
namespace jshd {
inline std::string make_glsl_image(
    uint32_t set,
    uint32_t binding,
    std::string_view imageType,
    std::string_view imageName,
    uint32_t count) {
  auto countFormatted =
      (count > 1 ? fmt::format("[{}]", count) : fmt::format(""));
  return fmt::format(
      "layout(set = {}, binding = {}) uniform {} {}{};",
      set,
      binding,
      imageType,
      imageName,
      countFormatted);
}

inline std::string make_glsl_image(json imageJson) {
  uint32_t set = imageJson["set"];
  uint32_t binding = imageJson["binding"];
  std::string imageType = "image" + std::string(imageJson["image_type"]);
  std::string_view imageName = imageJson["image_name"];
  uint32_t imageCount = imageJson["image_count"];
  return make_glsl_image(set, binding, imageType, imageName, imageCount);
}
}  // namespace jshd