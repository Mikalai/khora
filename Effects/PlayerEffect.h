#pragma once

#include <Effects/PlayerPerk.h>
#include <Effects/PlayerPredicate.h>
#include <Effects/Effect.h>
#include <Effects/PlayerEffectRequirenment.h>

class PlayerLogic;

class PlayerEffect : public Effect {
public:
	PlayerEffect(PlayerEffectRequirenment, PlayerPerk action);
    void Apply(PlayerLogic& player) const;
    bool CanApply(const PlayerLogic& player) const;

private:
    PlayerEffectRequirenment _cond;
    PlayerPerk _action;
};
