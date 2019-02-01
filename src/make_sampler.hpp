#pragma once
#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <string>
#include <string_view>

namespace jshd {
struct sampler_data {
  uint32_t set;
  uint32_t binding;
  std::string samplerName;
  uint32_t count;
};

inline std::string make_sampler(sampler_data samplerData) {
  std::string formattedCount;
  if (samplerData.count > 1) {
    formattedCount = fmt::format("[{}]", samplerData.count);
  }
  return fmt::format(
      "layout (set = {}, binding = {}) uniform sampler {}{};\n",
      samplerData.set,
      samplerData.binding,
      samplerData.samplerName,
      formattedCount);
}

inline sampler_data sampler_deserialize(nlohmann::json samplerJson) {
  sampler_data result{};
  result.set = samplerJson["set"];
  result.binding = samplerJson["binding"];
  result.samplerName = samplerJson["sampler_name"];
  result.count = samplerJson["sampler_count"];
  return result;
}
}  // namespace jshd