#pragma once
#include <fmt/format.h>
#include <string>
#include <string_view>
#include <nlohmann/json.hpp>
#include "glsl_type.hpp"

using json = nlohmann::json;
namespace jshd {
struct fragment_output_data {
  std::string outputName;
  std::string outputTypeName;
  glsl_type outputType;
  uint32_t location;
};

inline std::string make_fragment_output(fragment_output_data outputData) {
  return fmt::format(
      "layout (location = {}) out {} {};\n",
      outputData.location,
      outputData.outputTypeName,
      outputData.outputName);
}

inline fragment_output_data fragment_output_deserialize(json outputJson) {
  fragment_output_data result{};
  result.outputName = outputJson["output_name"];
  std::string typeName = outputJson["glsl_type"]["type"];
  result.outputType = make_glsl_type(typeName);
  result.outputTypeName = std::move(typeName);
  result.location = outputJson["location"];
  
  return result;
}
}  // namespace jshd