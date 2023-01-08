#pragma once

#include <Logic/WorldState.h>
#include <Logic/RoundState.h>

class WorldGameState : public ComplexState {
public:
    WorldGameState(WorldLogic& logic);
	void Reset() override;

private:
    std::array<RoundState, 9> _roundState;    
};
