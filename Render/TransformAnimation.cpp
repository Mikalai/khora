#pragma once

#include "TransformAnimation.h"

TransformAnimation::TransformAnimation(float time, vsg::ref_ptr<vsg::MatrixTransform> d, vsg::dmat4 a, vsg::dmat4 b)
	: _time{ time }
	, _a{ a }
	, _b{ b }
	, _d{ d }
{}

void TransformAnimation::Update(float dt) {
	_curTime += dt;
	if (_curTime > _time)
	{
		_r = _b;
		_d->matrix = _r;
		SetComplete();
		return;
	}

	double k = 1.0 - _curTime / _time;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			_r[i][j] = _a[i][j] * k + _b[i][j] * (1.0 - k);
		}
	}

	_d->matrix = _r;
};

vsg::dmat4 TransformAnimation::Value() const {
	return _r;
}
