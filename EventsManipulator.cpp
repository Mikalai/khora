
#include <Messages/All.h>
#include "WorldLogic.h"
#include "EventsManipulator.h"

EventsManipulator::EventsManipulator(WorldLogic& world)
	: _world{ world } {
}

void EventsManipulator::SelectNextEvent() {
	auto evt = _world.TakeNextEvent();
	_world.SetGlobalEvent(evt);
}


void EventsManipulator::Shuffle() {
	_world.EventsDeck().Reset(true);

	_world.EventsDeck().ForEach([this](int i, GlobalEventType p) {
		EventAddedToDeckMessage msg{ i, p };
		_world.Notify(msg);
		});

	EventsShuffledMessage msg{};
	_world.Notify(msg);
}

ConstEventsManipulator::ConstEventsManipulator(const WorldLogic& world)
	:_world{ world } {

}
const EventTemplate& ConstEventsManipulator::Current() const {
	auto evt = _world.EventsDeck().Current();
	return GetEventTemplate(evt);
}

const EventTemplate& EventsManipulator::Current() const {
	return ConstEventsManipulator(_world).Current();
}
