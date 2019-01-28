#include "make_image.hpp"
#include <catch2/catch.hpp>

TEST_CASE("Create a glsl string for image descriptor(s) from json") {
  std::string desiredOutput =
      "layout(set = 1, binding = 1) uniform image2D myImage;";
  auto j = json::parse(
      R"({
        "binding": 1,
        "set": 1,
        "image_name": "myImage",
        "image_type": "2D",
        "image_count": 1
      })");
  auto imageData = jshd::image_deserialize(j);
  auto result = jshd::make_image(imageData);
  REQUIRE(result == desiredOutput);
}