#pragma once
#include <fmt/format.h>
#include <string>
#include <string_view>
#include <nlohmann/json.hpp>
#include "glsl_type.hpp"

using json = nlohmann::json;
namespace jshd {
struct output_data {
  std::string outputName;
  std::string outputTypeName;
  std::vector<std::string> modifiers;
  glsl_type outputType;
  uint32_t location;
};

inline std::string make_output(output_data outputData) {
  return fmt::format(
      "layout (location = {}) out {} {};\n",
      outputData.location,
      outputData.outputTypeName,
      outputData.outputName);
}

inline output_data output_deserialize(json outputJson) {
  output_data result{};
  result.outputName = outputJson["output_name"];
  std::string typeName = outputJson["glsl_type"];
  result.outputType = make_glsl_type(typeName);
  result.outputTypeName = std::move(typeName);
  result.location = outputJson["location"];
  for (auto modifier : outputJson["modifiers"]) {
    result.modifiers.push_back(std::move(modifier));
  }
  return result;
}
}  // namespace jshd