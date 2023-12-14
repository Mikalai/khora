#pragma once

#include <vsg/all.h>
#include <nlohmann/json.hpp>

void Serialize(nlohmann::json& o, const vsg::dvec3& v);
void Serialize(nlohmann::json& o, const vsg::dquat& v);
void Deserialize(const nlohmann::json& o, vsg::dquat& v);
void Deserialize(const nlohmann::json& o, vsg::dquat& v);