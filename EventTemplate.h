#pragma once

#include <Resources.h>
#include <array>
#include <Effects/EventEffect.h>
#include <GlobalEventStage.h>

class EventTemplate {
public:
	EventTemplate(GlobalEventStage stage, GlobalEventType Event, EventEffect& effect);

	const EventEffect& GetEffect() const;
	GlobalEventType GetType() const;
	GlobalEventStage GetStage() const;

private:
	GlobalEventStage _stage;
	GlobalEventType _type;
	EventEffect* effect;
};

const EventTemplate& GetEventTemplate(GlobalEventType Event);