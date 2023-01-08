#include <Resources.h>
#include "TransformAnimation.h"
#include "WorldVisual.h"
#include "WorldVisualAnimator.h"

WorldVisualAnimator::WorldVisualAnimator(WorldVisual& visual)
	: _visual{ visual } {
}

Animation& WorldVisualAnimator::MoveTransform(vsg::ref_ptr<vsg::MatrixTransform> t, vsg::dmat4 a, vsg::dmat4 b) {
	auto anim = std::make_unique<TransformAnimation>(ANIMATION_SPEED, t, a, b);
	auto r = anim.get();
	_visual.AddAnimation(std::move(anim));
	return *r;
}

Animation& WorldVisualAnimator::MoveTransform(vsg::ref_ptr<vsg::MatrixTransform> t, vsg::dmat4 a, vsg::dmat4 b, float time) {
	auto anim = std::make_unique<TransformAnimation>(time, t, a, b);
	auto r = anim.get();
	_visual.AddAnimation(std::move(anim));
	return *r;
}
