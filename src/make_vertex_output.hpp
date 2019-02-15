#pragma once
#include <fmt/format.h>
#include <string>
#include <string_view>
#include <vector>
#include <nlohmann/json.hpp>
#include "glsl_type.hpp"

using json = nlohmann::json;
namespace jshd {
struct vertex_output_data {
  std::string outputName;
  std::string outputTypeName;
  std::vector<std::string> modifiers;
  glsl_type outputType;
  uint32_t location;
};

inline std::string make_vertex_output(vertex_output_data outputData) {
  fmt::memory_buffer modifierBuffer;
  for (auto modifier : outputData.modifiers) {
    fmt::format_to(modifierBuffer, "{} ", modifier);
  }
  return fmt::format(
      "layout (location = {}) out {}{} {};\n",
      outputData.location,
      fmt::to_string(modifierBuffer),
      outputData.outputTypeName,
      outputData.outputName);
}

inline vertex_output_data vertex_output_deserialize(json outputJson) {
  vertex_output_data result{};
  result.outputName = outputJson["output_name"];
  std::string typeName = outputJson["glsl_type"]["type"];
  result.outputType = make_glsl_type(typeName);
  result.outputTypeName = std::move(typeName);
  result.location = outputJson["location"];
  for (auto modifier : outputJson["modifiers"]) {
    result.modifiers.push_back(std::move(modifier));
  }
  return result;
}
}  // namespace jshd