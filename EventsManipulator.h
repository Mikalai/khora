#pragma once

#include <EventTemplate.h>

class WorldLogic;

class EventsManipulator {
public:

    EventsManipulator(WorldLogic& world);
    void SelectNextEvent();
    void Shuffle();
	const EventTemplate& Current() const;

private:
    WorldLogic& _world;
};

class ConstEventsManipulator {
public:

	ConstEventsManipulator(const WorldLogic& world);
	const EventTemplate& Current() const;

private:
	const WorldLogic& _world;
};
