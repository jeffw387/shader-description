#pragma once
#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <string>
#include <string_view>
#include <optional>
#include <vector>
#include <vulkan/vulkan.h>
#include "compile_hash.hpp"

namespace jshd {
struct sampler_data {
  uint32_t set;
  uint32_t binding;
  std::string samplerName;
  std::vector<std::optional<VkSamplerCreateInfo>> immutableSamplers;
};

inline std::string make_sampler(sampler_data samplerData) {
  std::string formattedCount;
  if (samplerData.immutableSamplers.size() > 1) {
    formattedCount = fmt::format("[{}]", samplerData.immutableSamplers.size());
  }
  return fmt::format(
      "layout (set = {}, binding = {}) uniform sampler {}{};\n",
      samplerData.set,
      samplerData.binding,
      samplerData.samplerName,
      formattedCount);
}

constexpr VkFilter make_filter(std::string_view name) {
  switch(hash(name)) {
    default:
    case hash("nearest"):
      return VK_FILTER_NEAREST;
    case hash("linear"):
      return VK_FILTER_LINEAR;
    case hash("cubic_img"):
      return VK_FILTER_CUBIC_IMG;
  }
}

constexpr VkSamplerMipmapMode make_mipmap_mode(std::string_view name) {
  switch (hash(name)) {
    default:
    case hash("nearest"):
      return VK_SAMPLER_MIPMAP_MODE_NEAREST;
    case hash("linear"):
      return VK_SAMPLER_MIPMAP_MODE_LINEAR;
  }
}

constexpr VkSamplerAddressMode make_addr_mode(std::string_view name) {
  switch (hash(name))
  {
    default:
    case hash("repeat"):
      return VK_SAMPLER_ADDRESS_MODE_REPEAT;
    case hash("mirrored_repeat"):
      return VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT;
    case hash("clamp_to_edge"):
      return VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    case hash("clamp_to_border"):
      return VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER;
    case hash("mirror_clamp_to_edge"):
      return VK_SAMPLER_ADDRESS_MODE_MIRROR_CLAMP_TO_EDGE;
  }
}

constexpr VkCompareOp make_compare_op(std::string_view name) {
  switch (hash(name)) {
    default:
    case hash("never"):
      return VK_COMPARE_OP_NEVER;
    case hash("<"):
      return VK_COMPARE_OP_LESS;
    case hash("<="):
      return VK_COMPARE_OP_LESS_OR_EQUAL;
    case hash(">"):
      return VK_COMPARE_OP_GREATER;
    case hash("!="):
      return VK_COMPARE_OP_NOT_EQUAL;
    case hash(">="):
      return VK_COMPARE_OP_GREATER_OR_EQUAL;
    case hash("always"):
      return VK_COMPARE_OP_ALWAYS;
  }
}

constexpr auto make_border_color(std::string_view name) {
  switch(hash(name)) {
    default:
    case hash("float_transparent_black"):
      return VK_BORDER_COLOR_FLOAT_TRANSPARENT_BLACK;
    case hash("int_transparent_black"):
      return VK_BORDER_COLOR_INT_TRANSPARENT_BLACK;
    case hash("float_opaque_black"):
      return VK_BORDER_COLOR_FLOAT_OPAQUE_BLACK;
    case hash("int_opaque_black"):
      return VK_BORDER_COLOR_INT_OPAQUE_BLACK;
    case hash("float_opaque_white"):
      return VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE;
    case hash("int_opaque_white"):
      return VK_BORDER_COLOR_INT_OPAQUE_WHITE;
  }
}

inline sampler_data sampler_deserialize(nlohmann::json samplerJson) {
  sampler_data result{};
  result.set = samplerJson["set"];
  result.binding = samplerJson["binding"];
  result.samplerName = samplerJson["sampler_name"];
  for (auto sampler : samplerJson["sampler_infos"]) {
    if (sampler.is_null()) {
      result.immutableSamplers.push_back({});
    } else {
      VkSamplerCreateInfo info{VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO};
      info.magFilter = make_filter(sampler["filters"]["mag"]);
      info.minFilter = make_filter(sampler["filters"]["min"]);
      info.mipmapMode = make_mipmap_mode(sampler["mipmap_mode"]);
      info.addressModeU = make_addr_mode(sampler["address_mode"]["u"]);
      info.addressModeV = make_addr_mode(sampler["address_mode"]["v"]);
      info.addressModeW = make_addr_mode(sampler["address_mode"]["w"]);
      info.mipLodBias = sampler["mip_lod_bias"];
      info.anisotropyEnable = sampler["anistropy"]["enable"];
      info.maxAnisotropy = sampler["anisotropy"]["max"];
      info.compareEnable = sampler["compare"]["enable"];
      info.compareOp = make_compare_op(sampler["compare"]["op"]);
    }
  }
  return result;
}
}  // namespace jshd