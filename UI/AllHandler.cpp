#pragma once

#include <cassert>
#include <UI/IUserInputHandler.h>
#include <UI/UserInputDispatcher.h>
#include "AllHandler.h"

void AllHandler::ForEach(std::function<void(IUserInputHandler& handler)> action) {
	for (int i = 0; i < _h._playersCount; ++i) {
		action(_h.Get(i));
	}
}

IUserInputHandler& AllHandler::Select(int playerId) {
	assert(playerId >= 0 && playerId < _h._playersCount);
	return *_h._handlers[playerId];
}
