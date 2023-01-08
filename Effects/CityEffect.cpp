#include <cassert>
#include <PlayerLogic.h>
#include "CityEffect.h"

CityEffect::CityEffect(int money, int red, int blue, int green, PlayerPerk action)
	: PlayerEffect({ money, red, blue, green }, action) {}
