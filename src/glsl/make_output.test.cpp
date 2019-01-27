#include "make_output.hpp"
#include <catch2/catch.hpp>

TEST_CASE("Make a test output string, ensure it matches expected") {
  std::string expectedString = "layout (location = 0) out vec3 outPos;";
  auto result = glsl::make_output("outPos", "vec3", 0);
  REQUIRE(result == expectedString);
}

TEST_CASE("Make output string from output json, match it to expected") {
  std::string expectedString = "layout (location = 0) out vec3 outPos;";
  auto outputJson = json::parse(
      "{\n"
      "\"output_name\": \"outPos\",\n"
      "\"glsl_type\": {\n"
      "\"type_name\": \"vec3\",\n"
      "\"align\": 16\n"
      "},\n"
      "\"location\": 0\n"
      "}\n");
  auto result = glsl::make_output(outputJson);
  REQUIRE(result == expectedString);
}