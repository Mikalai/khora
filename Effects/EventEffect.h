#pragma once

#include <functional>
#include <Resources.h>
#include <Effects/WorldEffect.h>

class EventEffect : public WorldEffect {
public:

    EventEffect(GlobalEventType type, WorldEffectAction action);

    GlobalEventType GetType() const;
private:
    GlobalEventType _type;
};
