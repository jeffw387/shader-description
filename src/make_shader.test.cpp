#include "make_shader.hpp"
#include <catch2/catch.hpp>
#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;
TEST_CASE("Create glsl shader from json. Check output.") {
  std::string expectedOutput{
      // clang-format off
R"(#version 450 core

const uint someConstant = 2;

layout (location = 0) out vec4 outColor;

layout (push_constant) uniform PushBlock {
  layout (offset = 0) vec3 push0;
  layout (offset = 16) float push1;
  layout (offset = 32) vec4 push2;
} push;

layout (set = 2, binding = 2) uniform UniformBlock {
  vec4 member0[4];
  vec4 member1;
} uniforms;

layout (set = 3, binding = 3) readonly buffer StorageBlock {
  mat4 matrices[];
} storageData;

layout (set = 0, binding = 0) uniform image2D myImage[3];

layout (set = 1, binding = 1) uniform sampler imgSampler;
)"
      // clang-format on
  };

  json j{json::parse(
      // clang-format off
R"({
  "shader_stage": "Fragment",
  "inputs": [],
  "outputs": [
    {
      "output_name": "outColor",
      "glsl_type": "vec4",
      "location": 0
    }
  ],

)"
      // clang-format on
      )};

  auto shaderData = jshd::shader_deserialize(j);
  auto result = jshd::make_shader(shaderData);
  REQUIRE(result == expectedOutput);
}