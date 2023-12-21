#pragma once

#include <functional>
#include <Resources.h>
#include <Effects/PlayerEffect.h>


class PolicyEffect : public PlayerEffect {
public:
    PolicyEffect(PoliciesType policy, int money, int red, int blue, int green, PlayerPerk action);
    
    constexpr PoliciesType GetType() const { return policy; }
private:
    PoliciesType policy;
};
