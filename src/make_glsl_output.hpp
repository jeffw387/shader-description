#pragma once
#include <fmt/format.h>
#include <string>
#include <string_view>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
namespace jshd {
inline std::string make_glsl_output(
    std::string_view outputName,
    std::string_view typeName,
    uint32_t location) {
  return fmt::format(
      "layout(location = {}) out {} {};", location, typeName, outputName);
}

inline std::string make_glsl_output(json outputJson) {
  std::string outputName = outputJson["output_name"];
  std::string typeName = outputJson["glsl_type"]["type_name"];
  uint32_t location = outputJson["location"];

  return make_glsl_output(outputName, typeName, location);
}
}  // namespace jshd