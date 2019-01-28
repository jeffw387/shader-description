#pragma once
#include <variant>
#include <iostream>
#include <glm/glm.hpp>
#include "compile_hash.hpp"

namespace jshd {
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

inline glsl_type make_glsl_type(std::string_view typeName) {
  using namespace glm;
  switch (hash(typeName)) {
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
}  // namespace jshd