#pragma once
#include <nlohmann/json.hpp>
#include <fmt/format.h>
#include <vector>
#include <string>
#include <string_view>
#include "buffer_block.hpp"

using namespace fmt::literals;
namespace jshd {
inline std::string make_buffer(
    uint32_t binding,
    uint32_t set,
    std::string blockName,
    std::string instanceName,
    buffer_type bufferType,
    bool dynamic,
    std::vector<data_type> members) {
  std::string bufferModifier;
  switch (bufferType) {
    case buffer_type::uniform:
      bufferModifier = "uniform";
      break;
    case buffer_type::storage:
      bufferModifier = "readonly buffer";
      break;
  }
  std::string blockDeclaration = fmt::format(
      "layout(set = {}, binding = {}) {} {} {{\n",
      set,
      binding,
      bufferModifier,
      blockName);
  std::vector<std::string> memberDeclarations;
  memberDeclarations.reserve(members.size());
  for (const data_type& member : members) {
    std::string arrayString;
    if (member.memberCount > 1) {
      arrayString = fmt::format("[{}]", member.memberCount);
    }
    std::string memberDeclaration = fmt::format(
        "  {}{} {};\n", member.typeName, arrayString, member.memberName);
    memberDeclarations.push_back(std::move(memberDeclaration));
  }
  std::string instanceDeclaration = fmt::format("}} {};\n", instanceName);
  std::string result;
  result += blockDeclaration;
  for (auto& member : memberDeclarations) {
    result += member;
  }
  result += instanceDeclaration;
  return result;
}

inline std::string make_buffer(nlohmann::json bufferBlockJson) {
  std::vector<data_type> members;
  for (const auto& member : bufferBlockJson["members"]) {
    data_type memberData;
    memberData.memberName = member["member_name"];
    memberData.memberCount = member["member_count"];
    memberData.typeName = member["member_type"]["type_name"];
    memberData.align = member["member_type"]["align"];
    members.push_back(std::move(memberData));
  }
  return make_buffer(
      bufferBlockJson["set"],
      bufferBlockJson["binding"],
      bufferBlockJson["block_name"],
      bufferBlockJson["instance_name"],
      from_string(bufferBlockJson["buffer_type"]),
      bufferBlockJson["dynamic"],
      std::move(members));
}
}  // namespace jshd
