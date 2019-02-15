#pragma once
#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <vulkan/vulkan.h>
#include <vector>
#include <string>
#include <string_view>
#include "compile_hash.hpp"
#include "make_fragment_input.hpp"
#include "make_fragment_output.hpp"
#include "make_buffer.hpp"
#include "make_image.hpp"
#include "make_sampler.hpp"
#include "make_constant.hpp"
#include "make_push_constant.hpp"

namespace jshd {
struct fragment_shader_data {
  VkShaderStageFlagBits stage;
  std::vector<constant_data> constants;
  std::vector<fragment_input_data> inputs;
  std::vector<fragment_output_data> outputs;
  std::vector<push_constant_data> pushConstants;
  std::vector<buffer_data> buffers;
  std::vector<image_data> images;
  std::vector<sampler_data> samplers;
};

inline fragment_shader_data fragment_shader_deserialize(nlohmann::json j) {
  fragment_shader_data result{};
  
  try {
    for (auto constant : j["constants"]) {
    auto constantData = constant_deserialize(constant);
    result.constants.push_back(std::move(constantData));
  }} catch (const std::exception& e) {}
  try {
    for (auto input : j["inputs"]) {
    auto inputData = fragment_input_deserialize(input);
    result.inputs.push_back(std::move(inputData));
  }} catch (const std::exception& e) {}
  try {
    for (auto output : j["outputs"]) {
    auto outputData = fragment_output_deserialize(output);
    result.outputs.push_back(std::move(outputData));
  }} catch (const std::exception& e) {}
  try {
    for (auto pushConstant : j["push_constants"]) {
    auto pushConstantData = push_constant_deserialize(pushConstant);
    result.pushConstants.push_back(std::move(pushConstantData));
  }} catch (const std::exception& e) {}
  try {
    for (auto buffer : j["buffers"]) {
    auto bufferData = buffer_deserialize(buffer);
    result.buffers.push_back(std::move(bufferData));
  }} catch (const std::exception& e) {}
  try {
    for (auto image : j["images"]) {
    auto imageData = image_deserialize(image);
    result.images.push_back(std::move(imageData));
  }} catch (const std::exception& e) {}
  try {
    for (auto sampler : j["samplers"]) {
    auto samplerData = sampler_deserialize(sampler);
    result.samplers.push_back(std::move(samplerData));
  }} catch (const std::exception& e) {}
  return result;
}

inline std::string make_fragment_shader(fragment_shader_data shaderData) {
  fmt::memory_buffer result;

  if (!shaderData.constants.empty()) {
    fmt::format_to(result, "\n");
    for (auto constant : shaderData.constants) {
      fmt::format_to(result, "{}", make_constant(constant));
    }
  }

  if (!shaderData.inputs.empty()) {
    fmt::format_to(result, "\n");
    for (auto input : shaderData.inputs) {
      fmt::format_to(result, "{}", make_fragment_input(input));
    }
  }

  if (!shaderData.outputs.empty()) {
    fmt::format_to(result, "\n");
    for (auto output : shaderData.outputs) {
      fmt::format_to(result, "{}", make_fragment_output(output));
    }
  }

  if (!shaderData.pushConstants.empty()) {
    fmt::format_to(result, "\n");
    fmt::format_to(result, "layout (push_constant) uniform PushBlock {{\n");
    for (auto pushConstant : shaderData.pushConstants) {
      fmt::format_to(result, "{}", make_push_constant(pushConstant));
    }
    fmt::format_to(result, "}} push;\n");
  }

  if (!shaderData.buffers.empty()) {
    for (auto buffer : shaderData.buffers) {
      fmt::format_to(result, "\n");
      fmt::format_to(result, "{}", make_buffer(buffer));
    }
  }

  if (!shaderData.images.empty()) {
    fmt::format_to(result, "\n");
    for (auto image : shaderData.images) {
      fmt::format_to(result, "{}", make_image(image));
    }
  }

  if (!shaderData.samplers.empty()) {
    fmt::format_to(result, "\n");
    for (auto sampler : shaderData.samplers) {
      fmt::format_to(result, "{}", make_sampler(sampler));
    }
  }

  return fmt::to_string(result);
}
}  // namespace jshd