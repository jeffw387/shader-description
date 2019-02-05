#pragma once
#include <nlohmann/json.hpp>
#include <fmt/format.h>
#include <vector>
#include <string>
#include <string_view>
#include <optional>
#include "buffer_block.hpp"

using namespace fmt::literals;
namespace jshd {
struct member_data {
  std::string memberName;
  std::string typeName;
  glsl_type glslType;
  std::optional<uint32_t> count;
};

struct buffer_data {
  uint32_t set;
  uint32_t binding;
  buffer_type bufferType;
  bool dynamic;
  std::string blockName;
  std::string instanceName;
  std::vector<member_data> members;
};

inline std::string make_array_string(std::optional<uint32_t> count) {
  if (count) {
    if (*count > 1) {
      return fmt::format("[{}]", *count);
    }
    return "";
  }
  return "[]";
}

inline std::string make_buffer_modifier(buffer_type bufferType) {
  switch (bufferType) {
    case buffer_type::uniform:
      return "uniform";
    case buffer_type::storage:
      return "readonly buffer";
  }
  fmt::print(std::cerr, "Error: buffer type not supported!");
  exit(1);
}

inline std::string make_buffer(buffer_data bufferData) {
  fmt::memory_buffer result{};
  auto bufferMod = make_buffer_modifier(bufferData.bufferType);
  fmt::format_to(
      result,
      "layout (set = {}, binding = {}) {} {} {{\n",
      bufferData.set,
      bufferData.binding,
      bufferMod,
      bufferData.blockName);

  for (const member_data& member : bufferData.members) {
    fmt::format_to(
        result,
        "  {} {}{};\n",
        member.typeName,
        member.memberName,
        make_array_string(member.count));
  }

  fmt::format_to(result, "}} {};\n", bufferData.instanceName);
  return fmt::to_string(result);
}

inline buffer_data buffer_deserialize(nlohmann::json bufferBlockJson) {
  buffer_data result{};
  result.set = bufferBlockJson["set"];
  result.binding = bufferBlockJson["binding"];
  result.blockName = bufferBlockJson["block_name"];
  result.instanceName = bufferBlockJson["instance_name"];
  result.bufferType = from_string(bufferBlockJson["buffer_type"]);
  result.dynamic = bufferBlockJson["dynamic"];
  for (const auto& member : bufferBlockJson["members"]) {
    auto typeName = member["member_type"];
    std::optional<uint32_t> countOptional;
    if (member.find("member_count") != member.end()) {
      countOptional = member["member_count"];
    }
    member_data memberData{member["member_name"],
                           typeName,
                           make_glsl_type(typeName),
                           countOptional};
    result.members.push_back(std::move(memberData));
  }
  return result;
}
}  // namespace jshd
