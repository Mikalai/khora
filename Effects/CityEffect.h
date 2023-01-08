#pragma once

#include <functional>
#include <Effects/PlayerEffect.h>

class CityEffect : public PlayerEffect {
public:
	CityEffect(int money, int red, int blue, int green, PlayerPerk action);
};
