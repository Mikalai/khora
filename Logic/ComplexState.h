#pragma once

#include <functional>
#include <vector>
#include <Logic/WorldState.h>

class ComplexState : public WorldState {
public:
    ComplexState(WorldLogic& logic);
    WorldState* Update() override;
    void Transition(std::function<bool(const WorldLogic&)> predicate, WorldState* next) override;
    void Enter() override;
	void Reset() override;

protected:    
	WorldState first;
    WorldState last;

private:
	WorldState* current{ nullptr };
};