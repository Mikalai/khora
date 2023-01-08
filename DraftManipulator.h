#pragma once

struct DraftManipulator {
	DraftManipulator(PlayerLogic& player)
		: _player{ player } {
	}

	void ForEach(std::function<void(Policies policy)> action);
	Policies Select(int index) const;
	int Size() const;
	void Take(Policies policy);
	Policies Random();

private:
	PlayerLogic& _player;
};
