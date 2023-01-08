#pragma once

#include <functional>
#include <Effects/Effect.h>

class WorldLogic;

using WorldEffectAction = std::function<void(WorldLogic&)>;

class WorldEffect : public Effect {
public:

    WorldEffect(WorldEffectAction action);
    void Apply(WorldLogic& player) const;    

private:
    WorldEffectAction _action;
};
