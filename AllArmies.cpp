#include <WorldLogic.h>
#include "AllArmies.h"


AllArmies::AllArmies(WorldLogic& world)
	: _world{ world }
	, max{ std::numeric_limits<int>::min() }
	, min{ std::numeric_limits<int>::max() }
	, count{ world.GetPlayersCount() }
	, armies{ 0 } {

	for (int i = 0; i < world.GetPlayersCount(); ++i) {
		auto v = world.GetPlayer(i).GetArmySize();
		armies[i] = v;
		if (v > max)
			max = v;
		if (v < min)
			min = v;
	}
}

AllArmies& AllArmies::Max(PlayerPerk action) {
	for (int i = 0; i < count; ++i) {
		if (armies[i] == max) {
			action(_world.GetPlayer(i));
		}
	}
	return *this;
}

AllArmies& AllArmies::Min(PlayerPerk action) {
	for (int i = 0; i < count; ++i) {
		if (armies[i] == min) {
			action(_world.GetPlayer(i));
		}
	}
	return *this;
}
