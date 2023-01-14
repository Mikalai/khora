#pragma once

#include <filesystem>
#include <vsg/io/Options.h>
#include <unordered_map>
#include <string>
#include <vector>
#include <memory>
#include <vsg/all.h>
#include <Resources.h>
#include <Render/Animation.h>

class AssetsCompiler;

class Scene {
public:

    bool MoveToWorld(vsg::ref_ptr<vsg::MatrixTransform> action);
    bool MoveToView(vsg::ref_ptr<vsg::MatrixTransform> t);
    void RemoveFromWorld(vsg::ref_ptr<vsg::MatrixTransform> t);

    vsg::ref_ptr<vsg::Group> GetRoot();
    void AddToWorld(vsg::ref_ptr<vsg::Node> node);

private:
    vsg::ref_ptr<vsg::MatrixTransform> _root;
    vsg::ref_ptr<vsg::MatrixTransform> _worldRoot;
    vsg::ref_ptr<vsg::MatrixTransform> _cameraAligned;

    std::vector<std::unique_ptr<Animation>> _animations;
    std::vector<std::unique_ptr<Animation>> _backgroundAnimations;

    friend class SceneBuilder;
};
