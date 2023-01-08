#include <functional>
#include <Effects/PolicyEffect.h>

PolicyEffect::PolicyEffect(Policies policy, int money, int red, int blue, int green, PlayerPerk action)
	: PlayerEffect({money, red, blue, green}, action) 
	, policy{ policy } {}