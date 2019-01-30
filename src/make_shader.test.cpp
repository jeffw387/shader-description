#include "make_shader.hpp"
#include <catch2/catch.hpp>
#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;
TEST_CASE("Create glsl shader from json. Check output.") {
  std::string expectedOutput =
R"(
#version 450 core

const uint someConstant = 2;

layout (location = 0) out vec4 outColor;

layout (set = 0, binding = 0) uniform image2D myImage[3];

layout (set = 1, binding = 1) uniform sampler imgSampler;


)";
}