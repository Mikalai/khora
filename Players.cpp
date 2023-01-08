#include "WorldLogic.h"
#include "Players.h"

Players::Players(WorldLogic& world)
	: _world{ world } {
}

void Players::ForEach(PlayerPerk action) {
	for (int i = 0; i < _world.GetPlayersCount(); ++i) {
		action(_world.GetPlayer(i));
	}
}

OrderedByDicesPlayers Players::OrderedByDices() {
	return OrderedByDicesPlayers{ _world };
}

OrderedByPointsPlayers Players::OrderedByPoints() {
	return OrderedByPointsPlayers{ _world };
}

bool Players::All(PlayerPredicate action) {
	bool result = true;
	for (int i = 0; i < _world.GetPlayersCount(); ++i) {
		result &= action(_world.GetPlayer(i));
	}
	return result;
}