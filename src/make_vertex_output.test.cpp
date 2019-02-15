#include "make_vertex_output.hpp"
#include <catch2/catch.hpp>

TEST_CASE("Make vertex output string from output json, match it to expected") {
  std::string expectedString = "layout (location = 0) out vec3 outPos;\n";
  auto outputJson = json::parse(
      R"({
      "output_name": "outPos",
      "glsl_type": { "type": "vec3" },
      "location": 0
      })");
  auto outputData = jshd::vertex_output_deserialize(outputJson);
  auto result = jshd::make_vertex_output(outputData);
  REQUIRE(result == expectedString);
}