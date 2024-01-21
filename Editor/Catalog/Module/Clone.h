#pragma once

#include <vsg/all.h>

vsg::ref_ptr<vsg::StateGroup> Clone(vsg::ref_ptr<vsg::StateGroup> original);
vsg::ref_ptr<vsg::MatrixTransform>
Clone(vsg::ref_ptr<vsg::MatrixTransform> original);
vsg::ref_ptr<vsg::VertexIndexDraw>
Clone(vsg::ref_ptr<vsg::VertexIndexDraw> original);
vsg::ref_ptr<vsg::Node> Clone(vsg::ref_ptr<vsg::Node> original);