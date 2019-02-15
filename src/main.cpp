#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include <cxxopts.hpp>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <string_view>
#include "make_vertex_shader.hpp"
#include "make_fragment_shader.hpp"
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
  std::fstream o{path, std::ios_base::out | std::ios_base::trunc};
  o << fileContents;
}

std::string generate_vertex_shader_in_place(std::string_view original, json j) {
  auto [beforeStartToken, afterStartToken] =
      split_after(original, StartToken());
  auto [betweenTokens, afterEndToken] =
      split_after(afterStartToken, EndToken());
  auto result = fmt::format(
      "{}\n{}{}{}",
      beforeStartToken,
      jshd::make_vertex_shader(jshd::vertex_shader_deserialize(j)),
      EndToken(),
      afterEndToken);
  return result;
}

std::string generate_fragment_shader_in_place(std::string_view original, json j) {
  auto [beforeStartToken, afterStartToken] =
      split_after(original, StartToken());
  auto [betweenTokens, afterEndToken] =
      split_after(afterStartToken, EndToken());
  auto result = fmt::format(
      "{}\n{}{}{}",
      beforeStartToken,
      jshd::make_fragment_shader(jshd::fragment_shader_deserialize(j)),
      EndToken(),
      afterEndToken);
  return result;
}

enum class shader_stage {
  vertex,
  fragment
};

int main(int argc, char* argv[]) {
  cxxopts::Options options(
      "json-shader", "Pass in a json-encoded shader file, output glsl");
      // clang-format off
  options.add_options()
      ("j, input-json", "Input json file", cxxopts::value<std::string>())
      ("g, input-glsl", "Input glsl", cxxopts::value<std::string>())
      ("s, stage", "Shader stage", cxxopts::value<std::string>())
      ("o, output", "Output glsl file", cxxopts::value<std::string>());
      // clang-format on

  options.parse_positional({"input-json", "input-glsl", "output"});
  options.positional_help("<input-json> <input-glsl> <output-glsl>")
      .show_positional_help();
  auto parseResult = options.parse(argc, argv);
  if (parseResult.arguments().empty()) {
    fmt::print("No arguments found...");
    fmt::print(options.help());
    return 0;
  }

  std::string inputJsonPath;
  shader_stage shaderStage;
  try {
    inputJsonPath = parseResult["input-json"].as<std::string>();
  } catch (const std::exception& e) {
    fmt::print(std::cerr, "{}", e.what());
    fmt::print(options.help());
    return 0;
  }

  try {
    auto stageString = parseResult["stage"].as<std::string>();
    if (stageString == "vertex") {
      shaderStage = shader_stage::vertex;
    } else if (stageString == "fragment") {
      shaderStage = shader_stage::fragment;
    } else {
      throw "Shader stage not implemented!";
    }
  } catch (const std::exception& e) {
    fmt::print(std::cerr, "Problem with shader stage, did you use -s?\n\n");
    fmt::print(options.help());
    exit(1);
  }
  std::string inputGLSLPath = parseResult["input-glsl"].as<std::string>();
  std::string outputGLSLPath = parseResult["output"].as<std::string>();

  auto inputJson = load_json_file(inputJsonPath);
  auto inputGLSL = load_text_file(inputGLSLPath);
  std::string generatedGLSL;
  switch (shaderStage) {
    case shader_stage::vertex:
      generatedGLSL = generate_vertex_shader_in_place(inputGLSL, inputJson);
      break;
    case shader_stage::fragment:
      generatedGLSL = generate_fragment_shader_in_place(inputGLSL, inputJson);
      break;
  }
  save_text_file(outputGLSLPath, generatedGLSL);
  return 0;
}