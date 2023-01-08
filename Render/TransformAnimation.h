#pragma once

#include <Render/Animation.h>
#include <vsg/all.h>
#ifdef vsgXchange_FOUND
#    include <vsgXchange/all.h>
#endif

class WorldLogic;

class TransformAnimation : public Animation {
public:
	TransformAnimation(float time, vsg::ref_ptr<vsg::MatrixTransform> d, vsg::dmat4 a, vsg::dmat4 b);

	void Update(float dt) override;

	vsg::dmat4 Value() const;

	double _time{0.0f};
	double _curTime{ 0.0f };
	vsg::dmat4 _a;
	vsg::dmat4 _b;
	vsg::dmat4 _r;
	vsg::ref_ptr<vsg::MatrixTransform> _d;
};
