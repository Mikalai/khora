#pragma once

#include <Effects/PlayerPerk.h>
#include <Effects/PlayerPredicate.h>
#include <OrderedByDicesPlayers.h>

struct Players {
    Players(WorldLogic& world);

    void ForEach(PlayerPerk action);
    OrderedByDicesPlayers OrderedByDices();	
	OrderedByPointsPlayers OrderedByPoints();
    bool All(PlayerPredicate action);

public:
    WorldLogic& _world;
};
