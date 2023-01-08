#include <functional>
#include <Effects/EventEffect.h>

EventEffect::EventEffect(GlobalEventType type, WorldEffectAction action)
	: WorldEffect(action)
	, _type{ type } {}

GlobalEventType EventEffect::GetType() const {
	return _type;
}