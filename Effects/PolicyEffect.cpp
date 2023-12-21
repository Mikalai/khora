#include <functional>
#include <Effects/PolicyEffect.h>

PolicyEffect::PolicyEffect(PoliciesType policy, int money, int red, int blue, int green, PlayerPerk action)
	: PlayerEffect({money, red, blue, green}, action) 
	, policy{ policy } {}