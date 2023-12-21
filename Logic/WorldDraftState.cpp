#include <UI/UI.h>
#include <Log/Log.h>
#include <WorldLogic.h>
#include "WorldLogicPrepare.h"
#include "WorldDraftState.h"

WorldDraftState::WorldDraftState(WorldLogic& logic)
	: ComplexState(logic)
	, state_round{ WorldState{logic}, WorldState{logic}, WorldState{logic}, WorldState{logic}, WorldState{logic} }
{
	first.Transition([](const WorldLogic& world) { return true; }, &state_round[0]);

	state_round[0].SetEnter([](WorldLogic& world) {
		INFO("=== BEGIN DRAFT ROUND 0 ===");
		world.Prepare().BeginDraft();
		});	

	for (int i = 0; i < 5; ++i) {
		if (i != 0) {
			state_round[i].SetEnter([i](WorldLogic& world) {
				INFO("=== BEGIN DRAFT ROUND {}", i);
				});
		}

		state_round[i].Transition([i](const WorldLogic& world) {
            return ui().IsIdle() && world.GetPlayers().All([i](const PlayerLogic& p) {
				return p.GetDraftSize() == 5 - i - 1;
				});			

			}, i < 4 ? &state_round[i + 1] : &last);		

		state_round[i].SetExit([i](WorldLogic& world) {
			INFO("=== END DRAFT ROUND {} ===", i);
			world.Prepare().ChangeDraft();
			});
	};

	state_round[4].SetExit([](WorldLogic& world) {
		INFO("=== END DRAFT ROUND 4 ===");
		world.Prepare().EndDraft();
		});
}

void WorldDraftState::Reset() {
	ComplexState::Reset();	
}