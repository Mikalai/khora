#pragma once

#include <Effects/PlayerPerk.h>
#include <PlayerPerkAcceptor.h>

class PlayerLogic;
class PlayerPerks;
class PlayerPerkAcceptor;

class PlayerPerks {
public:
	PlayerPerks(PlayerLogic& player);

	PlayerPerkAcceptor Tax();
private:
	PlayerLogic& _player;
};
