#pragma once
#include <string_view>
#include <string>
#include <variant>
#include <glm/glm.hpp>
#include <iostream>

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

using glsl_type = std::variant<
  bool,
  float,
  double,
  int32_t,
  uint32_t,
  glm::vec2,
  glm::vec3,
  glm::vec4,
  glm::mat2,
  glm::mat3,
  glm::mat4>;

constexpr 
unsigned int hash(std::string_view str, int h = 0)
{
    return !str[h] ? 5381 : (hash(str, h+1)*33) ^ str[h];
}

inline glsl_type make_glsl_type(std::string_view typeName) {
  using namespace glm;
  switch (hash(typeName))
  {
    case hash("bool"):
      return {bool{}};
    case hash("float"):
      return {float{}};
    case hash("double"):
      return {double{}};
    case hash("int"):
      return {int32_t{}};
    case hash("uint"):
      return {uint32_t{}};
    case hash("vec2"):
      return {vec2{}};
    case hash("vec3"):
      return {vec3{}};
    case hash("vec4"):
      return {vec4{}};
    case hash("mat2"):
      return {mat2{}};
    case hash("mat3"):
      return {mat3{}};
    case hash("mat4"):
      return {mat4{}};
    default:
      std::cerr << "glsl type " << typeName << " not implemented!";
      exit(1);      
  }
}

struct data_type {
  std::string memberName;
  std::string typeName;
  glsl_type glslType;
  uint32_t memberCount;
};
}  // namespace common