#pragma once

#include <Effects/PlayerPerk.h>

class WorldLogic;

struct AllArmies {
    AllArmies(WorldLogic& world);

    AllArmies& Max(PlayerPerk action);
    AllArmies& Min(PlayerPerk action);

private:
    WorldLogic& _world;
    std::array<int, 4> armies; 
    int count;
    int min;
    int max;
};
