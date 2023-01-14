#pragma once

#include <vector>
#include <map>
#include <Log/Log.h>

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
            objects[name] = std::make_tuple(vsg::ref_ptr<Object>{&o}, path);
        }

        path.emplace_back(&o);
        o.traverse(*this);
        path.pop_back();
    }

    std::vector<vsg::ref_ptr<Object>> path;
    std::map<std::string, std::tuple<vsg::ref_ptr<Object>, std::vector<vsg::ref_ptr<Object>>>> objects;
};
