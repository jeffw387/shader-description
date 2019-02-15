#pragma once
#include <fmt/format.h>
#include <string>
#include <string_view>
#include <vector>
#include <nlohmann/json.hpp>
#include "glsl_type.hpp"

using json = nlohmann::json;
namespace jshd {
struct fragment_input_data {
  std::string inputName;
  std::string inputTypeName;
  std::vector<std::string> modifiers;
  glsl_type inputType;
  uint32_t location;
};

inline std::string make_fragment_input(fragment_input_data inputData) {
  fmt::memory_buffer modifierBuffer;
  for (auto modifier : inputData.modifiers) {
    fmt::format_to(modifierBuffer, "{} ", modifier);
  }
  return fmt::format(
      "layout (location = {}) in {} {};\n",
      inputData.location,
      inputData.inputTypeName,
      inputData.inputName);
}

inline fragment_input_data fragment_input_deserialize(json inputJson) {
  fragment_input_data result{};
  result.inputName = inputJson["input_name"];
  std::string typeName = inputJson["glsl_type"]["type"];
  result.inputType = make_glsl_type(typeName);
  result.inputTypeName = std::move(typeName);
  result.location = inputJson["location"];
  for (auto modifier : inputJson["modifiers"]) {
    result.modifiers.push_back(std::move(modifier));
  }

  return result;
}
}  // namespace jshd