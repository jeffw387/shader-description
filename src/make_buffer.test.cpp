#include <catch2/catch.hpp>
#include "make_buffer.hpp"

using json = nlohmann::json;
using namespace jshd;

TEST_CASE("Json API output matches expected output") {
  std::string expectedOutput{
      // clang-format off
R"(layout (set = 3, binding = 3) uniform CameraBlock {
  mat4 view;
  mat4 projection;
} camera;
)"
      // clang-format on
  };
  auto testJson = json::parse(
      // clang-format off
R"({
  "binding": 3,
  "set": 3,
  "block_name": "CameraBlock",
  "instance_name": "camera",
  "buffer_type": "uniform",
  "dynamic": false,
  "members": [
    {
      "member_name": "view",
      "member_type": "mat4",
      "member_count": 1
    },
    {
      "member_name": "projection",
      "member_type": "mat4",
      "member_count": 1
    }
  ]
}
)"
      // clang-format on
  );
  auto bufferData = buffer_deserialize(testJson);
  auto result = make_buffer(bufferData);
  REQUIRE(result == expectedOutput);
}

TEST_CASE("Storage buffer with runtime array member.") {
  std::string expectedOutput{
      // clang-format off
R"(layout (set = 0, binding = 1) readonly buffer InstanceBlock {
  mat4 mvp[];
} instance;
)"
      // clang-format on
  };
  auto testJson = json::parse(
      // clang-format off
R"({
  "set": 0,
  "binding": 1,
  "dynamic": false,
  "block_name": "InstanceBlock",
  "instance_name": "instance",
  "buffer_type": "storage",
  "members": [
    {
      "member_name": "mvp",
      "member_type": "mat4"
    }
  ]
}
)"
      // clang-format on
  );
  auto bufferData = buffer_deserialize(testJson);
  auto result = make_buffer(bufferData);
  REQUIRE(result == expectedOutput);
}