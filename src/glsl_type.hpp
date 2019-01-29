#pragma once
#include <variant>
#include <iostream>
#include <fmt/ostream.h>
#include <glm/glm.hpp>
#include "compile_hash.hpp"

namespace glm {
inline std::ostream& operator<<(std::ostream& os, vec2 vec) {
  for (int i{}; i < 2; ++i) {
    os << vec[i];
  }
  return os;
}

inline std::ostream& operator<<(std::ostream& os, vec3 vec) {
  for (int i{}; i < 3; ++i) {
    os << vec[i];
  }
  return os;
}

inline std::ostream& operator<<(std::ostream& os, vec4 vec) {
  for (int i{}; i < 4; ++i) {
    os << vec[i];
  }
  return os;
}

inline std::ostream& operator<<(std::ostream& os, mat2 matrix) {
  for (int i{}; i < 2; ++i) {
    os << matrix[i];
  }
  return os;
}

inline std::ostream& operator<<(std::ostream& os, mat3 matrix) {
  for (int i{}; i < 3; ++i) {
    os << matrix[i];
  }
  return os;
}

inline std::ostream& operator<<(std::ostream& os, mat4 matrix) {
  for (int i{}; i < 4; ++i) {
    os << matrix[i];
  }
  return os;
}
}  // namespace glm

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

template <typename T>
inline glsl_type make_glsl_type(std::string_view typeName, T value) {
  using namespace glm;
  switch (hash(typeName)) {
    case hash("bool"):
      return {static_cast<bool>(value)};
    case hash("float"):
      return {static_cast<float>(value)};
    case hash("double"):
      return {static_cast<double>(value)};
    case hash("int"):
      return {static_cast<int32_t>(value)};
    case hash("uint"):
      return {static_cast<uint32_t>(value)};
    case hash("vec2"):
      return {static_cast<vec2>(value)};
    case hash("vec3"):
      return {static_cast<vec3>(value)};
    case hash("vec4"):
      return {static_cast<vec4>(value)};
    case hash("mat2"):
      return {static_cast<mat2>(value)};
    case hash("mat3"):
      return {static_cast<mat3>(value)};
    case hash("mat4"):
      return {static_cast<mat4>(value)};
    default:
      std::cerr << "glsl type " << typeName << " not implemented!";
      exit(1);
  }
}

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