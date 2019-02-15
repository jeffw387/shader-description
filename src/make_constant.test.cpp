#include "make_constant.hpp"
#include <catch2/catch.hpp>
#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;
TEST_CASE("Create a glsl string from json, check output") {
  std::string expectedOutput =
      "layout (constant_id = 1) const uint lightCount = 3;\n";
  json j{json::parse(
      R"({
  "constant_name": "lightCount",
  "specialization_id": 1,
  "glsl_type": { "type": "uint", "value": 3 }
  })")};
  auto constantData = jshd::constant_deserialize(j);
  auto result = jshd::make_constant(constantData);
  REQUIRE(result == expectedOutput);
}

TEST_CASE("Create a plain constant glsl string from json, check output") {
  std::string expectedOutput = "const uint myConst = 2;\n";
  auto j = json::parse(
      R"({
      "constant_name": "myConst",
      "glsl_type": { "type": "uint", "value": 2 }
      })");
  auto constantData = jshd::constant_deserialize(j);
  auto result = jshd::make_constant(constantData);
  REQUIRE(result == expectedOutput);
}