#include <Effects/WorldEffect.h>

#include <functional>

WorldEffect::WorldEffect(WorldEffectAction action) : _action{action} {}

void WorldEffect::Apply(WorldLogic& world) const { _action(world); }
