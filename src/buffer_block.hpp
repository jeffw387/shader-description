#pragma once
#include <string_view>
#include <string>
#include <variant>
#include <glm/glm.hpp>
#include <iostream>
#include "compile_hash.hpp"
#include "glsl_type.hpp"

namespace jshd {
enum class buffer_type { uniform, storage };

inline buffer_type from_string(std::string_view value) {
  if (value == "uniform") {
    return buffer_type::uniform;
  } else if (value == "storage") {
    return buffer_type::storage;
  }
  return {};
}

struct data_type {
  std::string memberName;
  std::string typeName;
  glsl_type glslType;
  uint32_t memberCount;
};
}  // namespace common