#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include <cxxopts.hpp>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <string_view>

using nlohmann::json;

std::string load_text_file(std::string path) {
  std::ifstream i{path};
  std::stringstream ss;
  ss << i.rdbuf();
  return ss.str();
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
    std::cerr << e.what() << "\n";
    exit(1);
  }
  // std::ifstream f{inputPath};
  // json j;
  // f >> j;
  // std::cout << j["shader_stage"] << "\n";

  auto loaded = load_text_file(inputPath);
  std::cout << loaded;
}