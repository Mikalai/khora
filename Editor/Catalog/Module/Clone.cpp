#include "Clone.h"

vsg::ref_ptr<vsg::StateGroup> Clone(vsg::ref_ptr<vsg::StateGroup> original) {
  auto clone = vsg::StateGroup::create();
  for (auto &state : original->stateCommands) {
    clone->stateCommands.push_back(state);
  }

  clone->prototypeArrayState = original->prototypeArrayState;

  return clone;
}

vsg::ref_ptr<vsg::MatrixTransform>
Clone(vsg::ref_ptr<vsg::MatrixTransform> original) {
  auto clone = vsg::MatrixTransform::create();
  clone->matrix = original->matrix;
  return clone;
}

vsg::ref_ptr<vsg::VertexIndexDraw>
Clone(vsg::ref_ptr<vsg::VertexIndexDraw> original) {
  // consider immutable
  return original;
}

vsg::ref_ptr<vsg::Node> Clone(vsg::ref_ptr<vsg::Node> original) {
  if (!original)
    return {};

  if (auto state = original.cast<vsg::StateGroup>(); state) {
    return Clone(state);
  } else if (auto tr = original.cast<vsg::MatrixTransform>(); tr) {
    return Clone(tr);
  } else if (auto vi = original.cast<vsg::VertexIndexDraw>(); vi) {
    return Clone(vi);
  }

  throw std::runtime_error("not implemented");
}