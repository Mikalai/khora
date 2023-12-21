#include <array>
#include <Log/Log.h>
#include <UI/UI.h>
#include <WorldLogic.h>
#include <WorldLogicRound.h>
#include "ThrowDicesState.h"

ThrowDicesState::ThrowDicesState(WorldLogic& logic)
	: ComplexState{ logic } 
	, _throwDices{ logic }
	, _identifyOrder{ logic }
	, _applyThrowDiceEventsPerks{ logic }
	, _selectActions{ logic }
	, _openActions{ logic }
{
	first.Transition([](const WorldLogic& world) { return true; }, &_throwDices);

	_throwDices.SetEnter([](WorldLogic& world) {	
		INFO("=== BEGIN: THROW DICE STAGE ===")
		world.Round().ThrowDices();
		});

	_throwDices.Transition([](const WorldLogic& world) {
        return ui().IsIdle() && world.GetPlayers().All([](const PlayerLogic& player) {
			return player.AreDicesThrown();
			});
		}, & _identifyOrder);

	_identifyOrder.SetEnter([](WorldLogic& world) {
		world.Round().IdentifyOrder();
		});

	_identifyOrder.Transition([](const WorldLogic& world) {
		return ui().IsIdle();
		}, &_applyThrowDiceEventsPerks);

	_applyThrowDiceEventsPerks.SetEnter([](WorldLogic& world) {
		INFO("Apply dice stage perks");
		world.Round().ApplyThrowDicesStagePerks();
		});

	_applyThrowDiceEventsPerks.Transition([](const WorldLogic& world) {
		return ui().IsIdle();
		}, &_selectActions);

	_selectActions.SetEnter([](WorldLogic& world) {
		INFO("Begin action selection...");
		world.Round().SelectActions();
		});

	_selectActions.Transition([](const WorldLogic& world) {
        return ui().IsIdle() && world.GetPlayers().All([](const PlayerLogic& player) {
			return player.AreActionsSelected();
			});
		}, &_openActions);
	
	_selectActions.SetExit([](WorldLogic& world) {
		INFO("Action selection complete.");
		});
	
	_openActions.SetEnter([](WorldLogic& world) {
		world.Round().OpenActions();
		});

	_openActions.Transition([](const WorldLogic& world) {
		return ui().IsIdle();
		}, &last);

	_openActions.SetExit([](WorldLogic& world) {
		INFO("=== COMPLETE: THROW DICE STAGE ===");
		});
}
