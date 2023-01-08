#pragma once

#include <functional>

class UserInputDispatcher;
class IUserInputHandler;

struct AllHandler {
	AllHandler(UserInputDispatcher& h)
		: _h{h}
	{}

	void ForEach(std::function<void(IUserInputHandler& handler)> action);
	IUserInputHandler& Select(int playerId);

private:
	UserInputDispatcher& _h;
};
