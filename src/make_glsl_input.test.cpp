#include "make_glsl_input.hpp"
#include <catch2/catch.hpp>

TEST_CASE("Make a test input string, ensure it matches expected") {
  std::string expectedString = "layout(location = 0) in vec3 inPos;";
  auto result = jshd::make_glsl_input("inPos", "vec3", 0);
  REQUIRE(result == expectedString);
}

TEST_CASE("Make input string from input json, match it to expected") {
  std::string expectedString = "layout(location = 0) in vec3 inPos;";
  auto inputJson = json::parse(
      "{\n"
      "\"input_name\": \"inPos\",\n"
      "\"glsl_type\": {\n"
      "\"type_name\": \"vec3\",\n"
      "\"align\": 16\n"
      "},\n"
      "\"location\": 0\n"
      "}\n");
  auto result = jshd::make_glsl_input(inputJson);
  REQUIRE(result == expectedString);
}