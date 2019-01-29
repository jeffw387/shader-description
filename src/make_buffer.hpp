#pragma once
#include <nlohmann/json.hpp>
#include <fmt/format.h>
#include <vector>
#include <string>
#include <string_view>
#include "buffer_block.hpp"

using namespace fmt::literals;
namespace jshd {
struct member_data {
  std::string memberName;
  std::string typeName;
  glsl_type glslType;
  uint32_t count;
};

struct buffer_data {
  uint32_t set;
  uint32_t binding;
  buffer_type bufferType;
  std::string blockName;
  std::string instanceName;
  std::vector<member_data> members;
};

inline std::string make_buffer(buffer_data bufferData) {
  std::string bufferModifier;
  switch (bufferData.bufferType) {
    case buffer_type::uniform:
      bufferModifier = "uniform";
      break;
    case buffer_type::storage:
      bufferModifier = "readonly buffer";
      break;
  }
  std::string blockDeclaration = fmt::format(
      "layout(set = {}, binding = {}) {} {} {{\n",
      bufferData.set,
      bufferData.binding,
      bufferModifier,
      bufferData.blockName);

  std::vector<std::string> memberDeclarations;
  memberDeclarations.reserve(bufferData.members.size());
  for (const member_data& member : bufferData.members) {
    std::string arrayString;
    if (member.count > 1) {
      arrayString = fmt::format("[{}]", member.count);
    }
    std::string memberDeclaration = fmt::format(
        "  {}{} {};\n", member.typeName, arrayString, member.memberName);
    memberDeclarations.push_back(std::move(memberDeclaration));
  }

  std::string instanceDeclaration =
      fmt::format("}} {};\n", bufferData.instanceName);
  std::string result;
  result += blockDeclaration;
  for (auto& member : memberDeclarations) {
    result += member;
  }
  result += instanceDeclaration;
  return result;
}

inline buffer_data buffer_deserialize(nlohmann::json bufferBlockJson) {
  buffer_data result{};
  result.set = bufferBlockJson["set"];
  result.binding = bufferBlockJson["binding"];
  result.blockName = bufferBlockJson["block_name"];
  result.instanceName = bufferBlockJson["instance_name"];
  result.bufferType = from_string(bufferBlockJson["buffer_type"]);
  for (const auto& member : bufferBlockJson["members"]) {
    auto typeName = member["member_type"];
    member_data memberData{member["member_name"],
                           typeName,
                           make_glsl_type(typeName),
                           member["member_count"]};
    result.members.push_back(std::move(memberData));
  }
  return result;
}
}  // namespace jshd
