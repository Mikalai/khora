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

void SerializeVector(nlohmann::json& o, const std::array<double, 3>& v){
    o["x"] = v[0];
    o["y"] = v[1];
    o["z"] = v[2];
}

void SerializeColor(nlohmann::json& o, const std::array<double, 4>& v) {
    o["r"] = v[0];
    o["g"] = v[1];
    o["b"] = v[2];
    o["a"] = v[3];
}

void Serialize(nlohmann::json& o, const std::u8string& v) {
    o = std::string{(char*)v.data(), v.size()};
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

vsg::dvec3 Deserialize(const nlohmann::json& o, std::string_view property,
                       vsg::dvec3 def) {
    vsg::dvec3 r;

    if (auto it = o.find(property); it != o.end()) {
        r.x = ::Deserialize(*it, "x", def.x);
        r.y = ::Deserialize(*it, "y", def.y);
        r.z = ::Deserialize(*it, "z", def.z);
    }

    return r;
}

std::array<double, 3> DeserializeVector(const nlohmann::json& o, std::string_view property, std::array<double, 3> def) {
    std::array<double, 3> r;

    if (auto it = o.find(property); it != o.end()) {
        r[0] = ::Deserialize(*it, "x", def[0]);
        r[1] = ::Deserialize(*it, "y", def[1]);
        r[2] = ::Deserialize(*it, "z", def[2]);
    } else {
        return def;
    }

    return r;
}

std::array<double, 4> DeserializeColor(const nlohmann::json& o, std::string_view property, std::array<double, 4> def) {
    std::array<double, 4> r;

    if (auto it = o.find(property); it != o.end()) {
        r[0] = ::Deserialize(*it, "r", def[0]);
        r[1] = ::Deserialize(*it, "g", def[1]);
        r[2] = ::Deserialize(*it, "b", def[2]);
        r[3] = ::Deserialize(*it, "a", def[3]);
    } else {
        return def;
    }

    return r;
}

std::u8string Deserialize(const nlohmann::json& o, std::string_view property,
                          std::u8string def) {
    if (auto it = o.find(property); it != o.end()) {
        auto value = it->get<std::string>();
		return (char8_t*)value.c_str();
    } else
        return def;    
}

vsg::dquat Deserialize(const nlohmann::json& o, std::string_view property,
                       vsg::dquat def) {
    vsg::dquat r;

    if (auto it = o.find(property); it != o.end()) {
        r.x = ::Deserialize(*it, "x", def.x);
        r.y = ::Deserialize(*it, "y", def.y);
        r.z = ::Deserialize(*it, "z", def.z);
        r.w = ::Deserialize(*it, "w", def.w);
    }

    return r;
}
