#include "make_image.hpp"
#include <catch2/catch.hpp>

TEST_CASE("Create a glsl string for image descriptor(s)") {
  std::string desiredOutput = "layout(set = 1, binding = 1) uniform image2D myImage;";
  auto result = jshd::make_image(
    1,
    1,
    "image2D",
    "myImage",
    1);
  REQUIRE(result == desiredOutput);
}

TEST_CASE("Create a glsl string for image descriptor(s) from json") {
  std::string desiredOutput = "layout(set = 1, binding = 1) uniform image2D myImage;";
  auto j = json::parse(
    "{{\n"
    ""
  );
}