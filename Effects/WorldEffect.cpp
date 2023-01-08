#pragma once

#include <functional>
#include <Effects/WorldEffect.h>


WorldEffect::WorldEffect(WorldEffectAction action)
    : _action{ action } {
}
 
void WorldEffect::Apply(WorldLogic& world) const {
    _action(world);
}
