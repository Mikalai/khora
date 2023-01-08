#include <Log/Log.h>
#include <UI/UI.h>
#include "WorldGameState.h"

const int DEBUG_FIRST_ROUND_OFFSET = 7;

WorldGameState::WorldGameState(WorldLogic& logic)
	: ComplexState(logic) 
	, _roundState{ RoundState{logic}, RoundState{logic}, RoundState{logic}, RoundState{logic}, RoundState{logic}, RoundState{logic}, RoundState{logic}, RoundState{logic}, RoundState{logic} }
{
	first.Transition([](const WorldLogic& world) { return true; }, &_roundState[DEBUG_FIRST_ROUND_OFFSET]);

	for (int i = DEBUG_FIRST_ROUND_OFFSET; i < 8; ++i) {
		_roundState[i].SetEnter([i](WorldLogic& world) {
			INFO("Round {}", i + 1);
			});

		_roundState[i].Transition([](const WorldLogic& world) {
			return ui().IsIdle();
			}, &_roundState[i + 1]);
	}

	_roundState[8].Transition([](const WorldLogic& world) {
		return ui().IsIdle();
		}, &last);
}

void WorldGameState::Reset() {
	
	ComplexState::Reset();
	
	for (auto& round : _roundState) {
		round.Reset();
	}
}