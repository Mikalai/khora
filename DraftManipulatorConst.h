#pragma once

struct DraftManipulatorConst {
	DraftManipulatorConst(const PlayerLogic& player)
		: _player{ player } {
	}
    
    void ForEach(std::function<void(PoliciesType policy)> action);
    PoliciesType Select(int index) const;
	int Size() const;
    PoliciesType Random();

private:
	const PlayerLogic& _player;
};
