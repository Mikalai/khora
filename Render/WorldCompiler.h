#pragma once

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
            objects[name] = &o;
        }
        o.traverse(*this);
    }

    std::map<std::string, vsg::ref_ptr<Object>> objects;
};
