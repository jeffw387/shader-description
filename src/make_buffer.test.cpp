#include <catch2/catch.hpp>
#include "make_buffer.hpp"

using json = nlohmann::json;
using namespace jshd;

TEST_CASE("Json API output matches expected output") {
  std::string desiredOutput =
      "layout(set = 3, binding = 3) uniform CameraBlock {\n"
      "  mat4 view;\n"
      "  mat4 projection;\n"
      "} camera;\n";
  auto testInput = json::parse(
      R"(
      {
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
      }]
      })");
  auto bufferData = buffer_deserialize(testInput);
  auto result = make_buffer(bufferData);
  REQUIRE(result == desiredOutput);
}