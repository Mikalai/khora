#pragma once

#include <vsg/all.h>
#ifdef vsgXchange_FOUND
#    include <vsgXchange/all.h>
#endif


class WorldVisual;

class WorldVisualAnimator {
public:
	WorldVisualAnimator(WorldVisual& visual);
	Animation& MoveTransform(vsg::ref_ptr<vsg::MatrixTransform> t, vsg::dmat4 a, vsg::dmat4 b);	
	Animation& MoveTransform(vsg::ref_ptr<vsg::MatrixTransform> t, vsg::dmat4 a, vsg::dmat4 b, float time);

private:
	WorldVisual& _visual;
};
