#pragma once
#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <string>
#include "glsl_type.hpp"

namespace jshd {
struct push_constant_data {
  std::string constantName;
  std::string typeName;
  glsl_type glslType;
  uint32_t offset;
};

inline push_constant_data push_constant_deserialize(nlohmann::json j) {
  push_constant_data result{};
  result.constantName = j["constant_name"];
  result.typeName = j["glsl_type"]["type"];
  result.glslType = make_glsl_type(result.typeName);
  result.offset = j["offset"];
  return result;
}

inline std::string make_push_constant(push_constant_data pcData) {
  return fmt::format(
      "  layout (offset = {}) {} {};\n",
      pcData.offset,
      pcData.typeName,
      pcData.constantName);
}
}  // namespace jshd