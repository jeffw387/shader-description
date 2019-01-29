#include "make_push_constant.hpp"
#include <catch2/catch.hpp>
#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;
TEST_CASE("Create a push constant glsl string from json, check output") {
  std::string expectedOutput = "  layout (offset = 0) mat4 mvp;";
  auto j = json::parse(
      R"({
      "constant_name": "mvp",
      "glsl_type": "mat4",
      "offset": 0
    })");
  auto pushConstantData = jshd::push_constant_deserialize(j);
  auto result = jshd::make_push_constant(pushConstantData);
  REQUIRE(result == expectedOutput);
}