#pragma once

struct DraftManipulatorConst {
	DraftManipulatorConst(const PlayerLogic& player)
		: _player{ player } {
	}

	void ForEach(std::function<void(Policies policy)> action);
	Policies Select(int index) const;
	int Size() const;
	Policies Random();

private:
	const PlayerLogic& _player;
};
