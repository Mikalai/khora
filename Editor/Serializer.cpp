#pragma once

#include "Serializer.h"

void Serialize(nlohmann::json& o, const vsg::dvec3& v) {
	o["x"] = v.x;
	o["y"] = v.y;
	o["z"] = v.z;
}

void Serialize(nlohmann::json& o, const vsg::dquat& v) {
	o["x"] = v.x;
	o["y"] = v.y;
	o["z"] = v.z;
	o["w"] = v.w;
}

void Deserialize(const nlohmann::json& o, vsg::dvec3& v) {
	v.x = o["x"].get<double>();
	v.y = o["y"].get<double>();
	v.z = o["z"].get<double>();
}

void Deserialize(const nlohmann::json& o, vsg::dquat& v) {
	v.x = o["x"].get<double>();
	v.y = o["y"].get<double>();
	v.z = o["z"].get<double>();
	v.w = o["w"].get<double>();
}
