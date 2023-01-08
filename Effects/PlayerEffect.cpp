#include <cassert>
#include <PlayerLogic.h>
#include "PlayerEffect.h"

PlayerEffect::PlayerEffect(PlayerEffectRequirenment req, PlayerPerk action)
	: _cond{ req }
	, _action{ action } {
}

void PlayerEffect::Apply(PlayerLogic& player) const {
	if (_cond.money != 0) {
		player.RemoveMoney(_cond.money);
	}
	int d[]{ _cond.red, _cond.blue, _cond.green };
	int c[]{ player.GetRedDiscovery(), player.GetBlueDiscovery(), player.GetGreenDiscovery() };

	int count = player.GetPhilosophyCount();
	
	for (int i = 0; i < 3; ++i) {
		auto need = d[i];
		auto has = c[i];

		if (need >= has) {
			int count = 2 * (need - has);
			count -= count;
			assert(count >= 0);
			player.RemovePhilosophy(count);
		}
	}

	_action(player);
}

bool PlayerEffect::CanApply(const PlayerLogic& player) const {
	if (!player.HasMoney(_cond.money))
		return false;
	int d[]{ _cond.red, _cond.blue, _cond.green };
	int c[]{ player.GetRedDiscovery(), player.GetBlueDiscovery(), player.GetGreenDiscovery() };

	int count = player.GetPhilosophyCount();
	for (int i = 0; i < 3; ++i) {
		auto need = d[i];
		auto has = c[i];
		
		if (need >= has) {
			count -= 2 * (need - has);
			if (count < 0)
				return false;
		}
	}
	return true;
}
