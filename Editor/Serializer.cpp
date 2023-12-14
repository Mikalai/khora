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

vsg::dvec3 Deserialize(const nlohmann::json& o, std::string_view property, vsg::dvec3 def) {
	vsg::dvec3 r;
	
	if (auto it = o.find(property); it != o.end()) {
		r.x = ::Deserialize(*it, "x", def.x);
		r.y = ::Deserialize(*it, "y", def.y);
		r.z = ::Deserialize(*it, "z", def.z);
	}

	return r;
}

vsg::dquat Deserialize(const nlohmann::json& o, std::string_view property, vsg::dquat def) {
	vsg::dquat r;

	if (auto it = o.find(property); it != o.end()) {
		r.x = ::Deserialize(*it, "x", def.x);
		r.y = ::Deserialize(*it, "y", def.y);
		r.z = ::Deserialize(*it, "z", def.z);
		r.w = ::Deserialize(*it, "w", def.w);
	}

	return r;
}
