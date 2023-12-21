#pragma once

struct DraftManipulator {
	DraftManipulator(PlayerLogic& player)
		: _player{ player } {
	}
    
    void ForEach(std::function<void(PoliciesType policy)> action);
    PoliciesType Select(int index) const;
	int Size() const;
    void Take(PoliciesType policy);
    PoliciesType Random();

private:
	PlayerLogic& _player;
};
