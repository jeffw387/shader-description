#pragma once
#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <vulkan/vulkan.h>
#include <vector>
#include <string>
#include <string_view>
#include "compile_hash.hpp"
#include "make_input.hpp"
#include "make_output.hpp"
#include "make_buffer.hpp"
#include "make_image.hpp"
#include "make_sampler.hpp"
#include "make_constant.hpp"
#include "make_push_constant.hpp"

namespace jshd {
struct shader_data {
  VkShaderStageFlagBits stage;
  std::vector<constant_data> constants;
  std::vector<input_data> inputs;
  std::vector<output_data> outputs;
  std::vector<push_constant_data> pushConstants;
  std::vector<buffer_data> buffers;
  std::vector<image_data> images;
  std::vector<sampler_data> samplers;
};

inline VkShaderStageFlagBits make_shader_stage(std::string_view stageName) {
  switch (hash(stageName)) {
    case hash("Vertex"):
      return VK_SHADER_STAGE_VERTEX_BIT;
    case hash("Fragment"):
      return VK_SHADER_STAGE_FRAGMENT_BIT;
    default:
      fmt::print("Error: shader stage {} not supported!", stageName);
      exit(1);
  }
}

inline shader_data shader_deserialize(nlohmann::json j) {
  shader_data result{};
  result.stage = make_shader_stage(j["shader_stage"]);
  for (auto input : j["inputs"]) {
    auto inputData = input_deserialize(input);
    result.inputs.push_back(std::move(inputData));
  }
  for (auto output : j["outputs"]) {
    auto outputData = output_deserialize(output);
    result.outputs.push_back(std::move(outputData));
  }
  for (auto buffer : j["buffer_blocks"]) {
    auto bufferData = buffer_deserialize(buffer);
    result.buffers.push_back(std::move(bufferData));
  }
  for (auto image : j["images"]) {
    auto imageData = image_deserialize(image);
    result.images.push_back(std::move(imageData));
  }
  for (auto sampler : j["samplers"]) {
    auto samplerData = sampler_deserialize(sampler);
    result.samplers.push_back(std::move(samplerData));
  }
  for (auto constant : j["constants"]) {
    auto constantData = constant_deserialize(constant);
    result.constants.push_back(std::move(constantData));
  }
  for (auto pushConstant : j["push_constants"]) {
    auto pushConstantData = push_constant_deserialize(pushConstant);
    result.pushConstants.push_back(std::move(pushConstantData));
  }
}

inline std::string make_shader(shader_data shaderData) {}
}  // namespace jshd