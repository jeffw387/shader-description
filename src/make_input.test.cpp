#include "make_input.hpp"
#include <catch2/catch.hpp>

TEST_CASE("Make input string from input json, match it to expected") {
  std::string expectedString = "layout (location = 0) in vec3 inPos;\n";
  auto inputJson = json::parse(
      R"({
      "input_name": "inPos",
      "glsl_type": "vec3",
      "location": 0
      })");
  auto inputData = jshd::input_deserialize(inputJson);
  auto result = jshd::make_input(inputData);
  REQUIRE(result == expectedString);
}