#include <catch2/catch.hpp>
#include "make_sampler.hpp"
#include <nlohmann/json.hpp>

using json = nlohmann::json;
TEST_CASE("Create a glsl sampler from json") {
  std::string expectedOutput{
      "layout (set = 0, binding = 1) uniform sampler mySampler[2];\n"};
  json j{json::parse(
      R"({
    "set": 0,
    "binding": 1,
    "sampler_name": "mySampler",
    "sampler_count": 2,
    "immutable": false,
    "sampler_infos": [null, null]
  })")};
  auto samplerData = jshd::sampler_deserialize(j);
  auto result = jshd::make_sampler(samplerData);
  REQUIRE(result == expectedOutput);
}