#pragma once
#include <fmt/format.h>
#include <string>
#include <string_view>
#include <nlohmann/json.hpp>
#include "glsl_type.hpp"

using json = nlohmann::json;
namespace jshd {
struct input_data {
  std::string inputName;
  std::string inputTypeName;
  std::vector<std::string> modifiers;
  glsl_type inputType;
  uint32_t location;
};

inline std::string make_input(input_data inputData) {
  return fmt::format(
      "layout(location = {}) in {} {};",
      inputData.location,
      inputData.inputTypeName,
      inputData.inputName);
}

inline input_data input_deserialize(json inputJson) {
  input_data result{};
  result.inputName = inputJson["input_name"];
  std::string typeName = inputJson["glsl_type"];
  result.inputType = make_glsl_type(typeName);
  result.inputTypeName = std::move(typeName);
  result.location = inputJson["location"];
  for (auto modifier : inputJson["modifiers"]) {
    result.modifiers.push_back(std::move(modifier));
  }

  return result;
}
}  // namespace jshd