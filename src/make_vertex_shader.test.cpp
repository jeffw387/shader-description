#include "make_vertex_shader.hpp"
#include <catch2/catch.hpp>
#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;
TEST_CASE("Create vertex shader from json. Check output.") {
  std::string expectedOutput{
      // clang-format off
R"(
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

layout (set = 0, binding = 0) uniform texture2D myImage[3];

layout (set = 1, binding = 1) uniform sampler imgSampler;
)"
      // clang-format on
  };

  json j{json::parse(
      // clang-format off
R"({
  "constants": [
    {
      "constant_name": "someConstant",
      "glsl_type": {
        "type": "uint",
        "value": 2
      }
    }
  ],
  "inputs": [],
  "outputs": [
    {
      "output_name": "outColor",
      "glsl_type": { "type": "vec4" },
      "location": 0
    }
  ],
  "push_constants": [
    {
      "constant_name": "push0",
      "glsl_type": { "type": "vec3" },
      "offset": 0
    },
    {
      "constant_name": "push1",
      "glsl_type": { "type": "float" },
      "offset": 16
    },
    {
      "constant_name": "push2",
      "glsl_type": { "type": "vec4" },
      "offset": 32
    }
  ],
  "buffers": [
    {
      "block_name": "UniformBlock",
      "instance_name": "uniforms",
      "buffer_type": "uniform",
      "dynamic": false,
      "binding": 2,
      "set": 2,
      "members": [
        {
          "member_name": "member0",
          "member_type": "vec4",
          "member_count": 4
        },
        {
          "member_name": "member1",
          "member_type": "vec4",
          "member_count": 1
        }
      ]
    },
    {
      "block_name": "StorageBlock",
      "instance_name": "storageData",
      "buffer_type": "storage",
      "dynamic": false,
      "binding": 3,
      "set": 3,
      "members": [
        {
          "member_name": "matrices",
          "member_type": "mat4"
        }
      ]
    }
  ],
  "images": [
    {
      "binding": 0,
      "set": 0,
      "image_name": "myImage",
      "image_type": "texture2D",
      "image_count": 3
    }
  ],
  "samplers": [
    {
      "binding": 1,
      "set": 1,
      "sampler_name": "imgSampler",
      "immutable": false,
      "sampler_infos": [null]
    }
  ]
}
)"
      // clang-format on
      )};

  auto shaderData = jshd::vertex_shader_deserialize(j);
  auto result = jshd::make_vertex_shader(shaderData);
  REQUIRE(result == expectedOutput);
}