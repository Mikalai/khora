#pragma once

#include <array>
#include <Logic/ComplexState.h>

class WorldDraftState : public ComplexState {
public:
	WorldDraftState(WorldLogic& logic);
	void Reset() override;
	
	std::array<WorldState, 5> state_round;
};

//
//class WorldDraftState : public WorldState {
//public:
//	WorldDraftState(WorldLogic& logic);
//	WorldState* Update() override;
//	void Transition(std::function<bool(const WorldLogic&)> predicate, WorldState* next) override;
//	void Enter() override;
//
//	std::array<WorldState, 5> state_round;
//	WorldState last;
//	WorldState* current;
//};
