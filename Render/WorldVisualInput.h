#pragma once

struct WorldVisualInput {
    int playerId;
    vsg::ref_ptr<vsg::Builder> builder;
    vsg::ref_ptr<vsg::Viewer> viewer;
    WorldLogic* logic; 
    vsg::ref_ptr<vsg::Options> options;
    vsg::ref_ptr<vsg::Font> font;
    vsg::ref_ptr<vsg::Camera> camera;
};
