#pragma once

#include <array>
#include <PlayerLogic.h>

#include <Logic/WorldGameState.h>
#include <Logic/WorldInitState.h>

class World {
public:

    World(WorldLogic& logic);
    void Update();

    WorldState* current{ nullptr };
    WorldInitState state_init;
    WorldGameState state_game;
    WorldState state_caculate_scores;
	bool _started{ false };
	WorldLogic& _logic;
};
