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

json load_json_file(std::string path) {
  auto text = load_text_file(path);
  return json::parse(text);
}

void save_text_file(std::string path, std::string_view fileContents) {
  std::ofstream o{path};
  o << fileContents;
}

std::string generate_glsl_in_place(std::string_view original, json j) {
  auto [beforeStartToken, afterStartToken] =
      split_after(original, StartToken());
  auto [betweenTokens, afterEndToken] =
      split_after(afterStartToken, EndToken());
  auto result = fmt::format(
      "{}\n{}{}{}",
      beforeStartToken,
      jshd::make_shader(jshd::shader_deserialize(j)),
      EndToken(),
      afterEndToken);
  return result;
}

int main(int argc, char* argv[]) {
  cxxopts::Options options(
      "json-shader", "Pass in a json-encoded shader file, output glsl");
  options.add_options()(
      "j, input-json", "Input json file", cxxopts::value<std::string>())(
      "g, input-glsl", "Input glsl template", cxxopts::value<std::string>())(
      "o, output",
      "Output glsl file",
      cxxopts::value<std::string>()->default_value("output.glsl"));

  options.parse_positional({"input-json", "input-glsl", "output"});
  options.positional_help("<input-json> <input-glsl> <output-glsl>")
      .show_positional_help();
  auto parseResult = options.parse(argc, argv);
  if (parseResult.arguments().empty()) {
    fmt::print(options.help());
    return 0;
  }

  std::string inputPath;
  try {
    inputPath = parseResult["input"].as<std::string>();
  } catch (const std::exception&) {
    fmt::print(options.help());
    return 0;
  }
  std::string outputGLSL = parseResult["output"].as<std::string>();

  auto shaderJson = load_json_file(inputPath);
  auto glslOriginal = load_text_file(outputGLSL);

  auto generatedGLSL = generate_glsl_in_place(glslOriginal, shaderJson);

  save_text_file(outputGLSL, generatedGLSL);
}