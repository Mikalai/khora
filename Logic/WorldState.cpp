#pragma once

#include <functional>
#include "WorldState.h"

WorldState::WorldState(WorldLogic& logic)
	: _logic{ logic }
{
}

WorldState* WorldState::Update() {

	if (_update)
		_update(_logic);

	for (auto& transition : transition_table) {
		if (transition.predicate(_logic)) {
			
			Exit();

			if (transition.next)
				transition.next->Enter();


			return transition.next;
		}
	}

	return this;
}


void WorldState::Transition(std::function<bool(const WorldLogic&)> predicate, WorldState* next) {
	transition_table.push_back({ predicate, next });
}

void WorldState::SetEnter(std::function<void(WorldLogic&)> action) {
	_enter = action;
}

void WorldState::SetExit(std::function<void(WorldLogic&)> action) {
	_exit = action;
}

void WorldState::SetUpdate(std::function<void(WorldLogic&)> action) {
	_update = action;
}

void WorldState::Exit() {
	if (_exit) {
		_exit(_logic);
	}
}

void WorldState::Enter() {	
	if (_enter) {
		_enter(_logic);
	}	
}

void WorldState::Reset() {

}