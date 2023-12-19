#pragma once

#include <vector>
#include <map>

#include <vsg/all.h>
#ifdef vsgXchange_FOUND
#    include <vsgXchange/all.h>
#endif

class WorldCompiler : public vsg::Inherit<vsg::Visitor, WorldCompiler>
{
public:

    WorldCompiler() {

    }

    void apply(Object& o) override {
        std::string name;
        if (auto hasName = o.getValue("name", name); hasName) {
            auto ptr = vsg::ref_ptr<Object>{ &o };
            objects[name] = std::make_tuple(ptr, path);

            if (auto t = vsg::cast<vsg::MatrixTransform>(ptr); t) {
                allTransforms[name] = t;
            }           
            _name = name;
        }
        else {
            if (auto m = o.cast<vsg::StateGroup>(); m) {
                objects[_name + ".material"] = std::make_tuple(m, path);
            }
        }

        path.emplace_back(&o);
        o.traverse(*this);
        path.pop_back();
    }

    std::string _name;
    std::vector<vsg::ref_ptr<Object>> path;
    std::map<std::string, std::tuple<vsg::ref_ptr<Object>, std::vector<vsg::ref_ptr<Object>>>> objects;
    std::unordered_map<std::string, vsg::ref_ptr<vsg::MatrixTransform>> allTransforms;
};
