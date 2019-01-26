#include "split_view.hpp"
#include <catch2/catch.hpp>
#include <string>

TEST_CASE("Split string after token #") {
  std::string wholeString = "12345#6789";
  std::string beforeDesired = "12345#";
  std::string afterDesired = "6789";

  auto splitView = split_after(wholeString, "#");
  REQUIRE(splitView.before == beforeDesired);
  REQUIRE(splitView.after == afterDesired);
}

TEST_CASE("Split string that has no matching token") {
  std::string wholeString = "123456789";
  std::string_view beforeDesired = wholeString;
  std::string_view afterDesired = "";

  auto splitView = split_after(wholeString, "#");
  REQUIRE(splitView.before == beforeDesired);
  REQUIRE(splitView.after == afterDesired);
}

TEST_CASE("Split string after multicharacter token //#") {
  std::string wholeString = "123//#456789";
  std::string beforeDesired = "123//#";
  std::string afterDesired = "456789";

  auto splitView = split_after(wholeString, "//#");
  REQUIRE(splitView.before == beforeDesired);
  REQUIRE(splitView.after == afterDesired);
}