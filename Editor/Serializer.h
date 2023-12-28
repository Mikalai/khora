#pragma once

#include <vsg/all.h>
#include <nlohmann/json.hpp>
#include <string_view>

void Serialize(nlohmann::json& o, const vsg::dvec3& v);
void Serialize(nlohmann::json& o, const vsg::dquat& v);
void Serialize(nlohmann::json& o, const std::u8string& v);
void SerializeVector(nlohmann::json& o, const std::array<double, 3>& v);
void SerializeColor(nlohmann::json& o, const std::array<double, 4>& v);
void Deserialize(const nlohmann::json& o, vsg::dquat& v);
void Deserialize(const nlohmann::json& o, vsg::dquat& v);
vsg::dvec3 Deserialize(const nlohmann::json& o, std::string_view property, vsg::dvec3 def);
vsg::dquat Deserialize(const nlohmann::json & o, std::string_view property, vsg::dquat def);
std::u8string Deserialize(const nlohmann::json & o, std::string_view property, std::u8string def);
std::array<double, 3> DeserializeVector(const nlohmann::json& o, std::string_view property, std::array<double, 3> def);
std::array<double, 4> DeserializeColor(const nlohmann::json& o, std::string_view property, std::array<double, 4> def);

template<typename T>
inline auto Deserialize(const nlohmann::json& o, std::string_view property, T def) {
	if (auto it = o.find(property); it != o.end())
		return it->get<T>();
	else
		return def;
}
