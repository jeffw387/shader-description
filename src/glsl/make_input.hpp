#pragma once
#include <fmt/format.h>
#include <string>
#include <string_view>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
namespace glsl {
inline std::string make_input(
    std::string_view inputName,
    std::string_view typeName,
    uint32_t location) {
  return fmt::format(
      "layout (location = {}) in {} {};", location, typeName, inputName);
}

inline std::string make_input(json inputJson) {
  std::string inputName = inputJson["input_name"];
  std::string typeName = inputJson["glsl_type"]["type_name"];
  uint32_t location = inputJson["location"];

  return make_input(inputName, typeName, location);
}
}  // namespace glsl