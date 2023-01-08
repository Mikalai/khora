#pragma once

#include "Animation.h"

Animation::~Animation() {
}

void Animation::OnComplete(OnCompleteCallback cb) {
	_cb.push_back(cb);
}

void Animation::SetComplete() {
	if (_isComplete)
		return;

	_isComplete = true;
	for (auto cb : _cb) {
		cb();
	}
}
