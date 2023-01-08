#pragma once

#include "PlayerLogic.h"
#include "PlayerPerkAcceptor.h"

PlayerPerkAcceptor::PlayerPerkAcceptor(PlayerLogic& player, const std::vector<PlayerPerk>& perks)
	: _player{ player }
	, _perks{ perks }
{}

void PlayerPerkAcceptor::Apply() {
	for (auto& p : _perks) {
		p(_player);
	}
}

PlayerPerks::PlayerPerks(PlayerLogic& player)
	: _player{ player } {
}

PlayerPerkAcceptor PlayerPerks::Tax() {
	return { _player, _player._taxPerks };
}
