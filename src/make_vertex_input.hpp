#pragma once
#include <fmt/format.h>
#include <string>
#include <string_view>
#include <nlohmann/json.hpp>
#include "glsl_type.hpp"

using json = nlohmann::json;
namespace jshd {
struct vertex_input_data {
  std::string inputName;
  std::string inputTypeName;
  glsl_type inputType;
  uint32_t location;
  uint32_t binding;
  uint32_t offset;
};

inline std::string make_vertex_input(vertex_input_data inputData) {
  return fmt::format(
      "layout (location = {}) in {} {};\n",
      inputData.location,
      inputData.inputTypeName,
      inputData.inputName);
}

inline vertex_input_data vertex_input_deserialize(json inputJson) {
  vertex_input_data result{};
  result.inputName = inputJson["input_name"];
  std::string typeName = inputJson["glsl_type"];
  result.inputType = make_glsl_type(typeName);
  result.inputTypeName = std::move(typeName);
  result.location = inputJson["location"];
  result.binding = inputJson["binding"];
  result.offset = inputJson["offset"];

  return result;
}
}  // namespace jshd