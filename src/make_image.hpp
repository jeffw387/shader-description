#pragma once
#include <fmt/format.h>
#include <string>
#include <string_view>
#include <nlohmann/json.hpp>
#include <vulkan/vulkan.h>

using json = nlohmann::json;
namespace jshd {
struct image_data {
  uint32_t set;
  uint32_t binding;
  std::string imageTypeName;
  std::string imageName;
  uint32_t count;
};

inline std::string make_image(image_data imageData) {
  auto countFormatted =
      (imageData.count > 1 ? fmt::format("[{}]", imageData.count)
                           : fmt::format(""));
  return fmt::format(
      "layout(set = {}, binding = {}) uniform {} {}{};",
      imageData.set,
      imageData.binding,
      imageData.imageTypeName,
      imageData.imageName,
      countFormatted);
}

inline image_data image_deserialize(nlohmann::json imageJson) {
  image_data result{};
  result.set = imageJson["set"];
  result.binding = imageJson["binding"];
  result.imageTypeName = imageJson["image_type"];
  result.imageName = imageJson["image_name"];
  result.count = imageJson["image_count"];
  return result;
}
}  // namespace jshd