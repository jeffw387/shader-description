#pragma once
#include <string>
#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <optional>
#include "glsl_type.hpp"

namespace jshd {
struct constant_data {
  std::string constantName;
  std::string typeName;
  glsl_type glslType;
  std::optional<uint32_t> specializationID;
};

inline constant_data constant_deserialize(nlohmann::json constantJson) {
  constant_data result{};
  result.constantName = constantJson["constant_name"];
  result.typeName = constantJson["glsl_type"]["type"];
  result.glslType =
      make_glsl_type(result.typeName, constantJson["glsl_type"]["value"]);
  try {
    result.specializationID = constantJson["specialization_id"];
  }
  catch (const std::exception& e) {}
  return result;
}

constexpr auto visit_glsl_type = [](auto glsl_variant) {
  return fmt::format("{}", glsl_variant);
};

inline std::string make_constant(constant_data constantData) {
  std::string specIDFormat;
  if (constantData.specializationID) {
    specIDFormat = fmt::format(
        "layout (constant_id = {}) ", *constantData.specializationID);
  }

  return fmt::format(
      "{}const {} {} = {};\n",
      specIDFormat,
      constantData.typeName,
      constantData.constantName,
      std::visit(visit_glsl_type, constantData.glslType));
}
}  // namespace jshd