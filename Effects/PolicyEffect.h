#pragma once

#include <functional>
#include <Resources.h>
#include <Effects/PlayerEffect.h>


class PolicyEffect : public PlayerEffect {
public:
	PolicyEffect(Policies policy, int money, int red, int blue, int green, PlayerPerk action);

	constexpr Policies GetType() const { return policy; }
private:
	Policies policy;
};
