#include <catch2/catch.hpp>
#include "make_buffer.hpp"

using json = nlohmann::json;
using namespace jshd;
TEST_CASE("Make a string from a buffer description") {
  std::string desiredOutput =
      "layout(set = 3, binding = 3) uniform CameraBlock {\n"
      "  mat4 view;\n"
      "  mat4 projection;\n"
      "} camera;\n";
  std::vector<data_type> members{
      data_type{"view", "mat4", 64, 1},
      data_type{"projection", "mat4", 64, 1}};

  auto result = make_buffer(
      3,
      3,
      "CameraBlock",
      "camera",
      buffer_type::uniform,
      false,
      members);
  REQUIRE(result == desiredOutput);
}

TEST_CASE("Json API output matches expected output") {
  std::string desiredOutput =
      "layout(set = 3, binding = 3) uniform CameraBlock {\n"
      "  mat4 view;\n"
      "  mat4 projection;\n"
      "} camera;\n";
  auto testInput = json::parse(
      "{\n"
      "\"binding\" : 3,\n"
      "\"set\" : 3, \"block_name\" : \"CameraBlock\",\n"
      "\"instance_name\" : \"camera\",\n"
      "\"buffer_type\" : \"uniform\",\n"
      "\"dynamic\" : false,\n"
      "\"members\" : [\n"
      "{\n"
      "\"member_name\" : \"view\",\n"
      "\"member_type\" : {\"type_name\" : \"mat4\", \"align\" : 64},\n"
      "\"member_count\" : 1\n"
      "},\n"
      "{\n"
      "\"member_name\" : \"projection\",\n"
      "\"member_type\" : {\"type_name\" : \"mat4\", \"align\" : 64},\n"
      "\"member_count\" : 1\n"
      "  }\n"
      "]\n"
      "}\n ");
  auto result = make_buffer(testInput);
  REQUIRE(result == desiredOutput);
}