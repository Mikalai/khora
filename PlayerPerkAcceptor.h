#pragma once

#include <vector>
#include <Effects/PlayerPerk.h>

class PlayerLogic;
class PlayerPerks;

class PlayerPerkAcceptor {
	friend class PlayerPerks;

	PlayerPerkAcceptor(PlayerLogic& player, const std::vector<PlayerPerk>& perks);

	PlayerLogic& _player;
	const std::vector<PlayerPerk>& _perks;

public:
	void Apply();
};
