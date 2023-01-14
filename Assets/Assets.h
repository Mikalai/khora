#pragma once

#include <filesystem>
#include <vsg/io/Options.h>
#include <unordered_map>
#include <string>
#include <vector>
#include <memory>
#include <vsg/all.h>
#include <Resources.h>

class AssetsCompiler;

class Assets {
public:
    virtual ~Assets();
    virtual void FillSerializationTables(AssetsCompiler& compiler);        
};
