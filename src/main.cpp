#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include <cxxopts.hpp>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <string_view>
#include "make_shader.hpp"
#include "split_view.hpp"

using nlohmann::json;

constexpr std::string_view StartToken() { return "///{"; }
constexpr std::string_view EndToken() { return "///}"; }

std::string load_text_file(std::string path) {
  std::ifstream i{path};
  std::stringstream ss;
  ss << i.rdbuf();
  return ss.str();
}

void save_text_file(std::string path, std::string_view fileContents) {
  std::ofstream o{path};
  o << fileContents;
}

int main(int argc, char* argv[]) {
  cxxopts::Options options(
      "json-shader", "Pass in a json-encoded shader file, output glsl and c++");
  options.add_options()(
      "i, input", "Input json file", cxxopts::value<std::string>())(
      "g, glsl",
      "Output glsl file",
      cxxopts::value<std::string>()->default_value("output.glsl"))(
      "c, cpp",
      "Output c++ file",
      cxxopts::value<std::string>()->default_value("output.hpp"))(
      "t, template", "GLSL output file exists and is a template");

  auto parseResult = options.parse(argc, argv);
  if (parseResult.arguments().size() == 0) {
    std::cout << "No arguments, exiting";
    exit(1);
  }
  std::string inputPath;
  std::string outputGLSL;
  std::string outputCPP;
  bool glslTemplate;
  try {
    inputPath = parseResult["input"].as<std::string>();
    outputGLSL = parseResult["glsl"].as<std::string>();
    outputCPP = parseResult["cpp"].as<std::string>();
    glslTemplate = parseResult["template"].as<bool>();
  } catch (std::exception& e) {
    fmt::print(std::cerr, "Error processing command line arguments: {}\n", e.what());
    exit(1);
  }

  auto inputJson = json::parse(load_text_file(inputPath));
  auto shaderData = jshd::shader_deserialize(inputJson);
  auto outputGLSLText = load_text_file(outputGLSL);
  auto [beforeStartToken, afterStartToken] = split_after(outputGLSLText, StartToken());
  auto [betweenTokens, afterEndToken] = split_after(afterStartToken, EndToken());

  save_text_file(outputGLSL, fmt::format("{}\n{}{}{}", beforeStartToken, jshd::make_shader(shaderData), EndToken(), afterEndToken));
}