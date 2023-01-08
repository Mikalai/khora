#include <array>
#include <UI/UI.h>
#include <Log/Log.h>
#include <WorldLogic.h>
#include <WorldLogicRound.h>
#include "RoundState.h"

RoundState::RoundState(WorldLogic& logic)
	: ComplexState{ logic }
	, _declareEventState{ logic }
	, _collectTaxState{ logic }
	, _throwDicesState{ logic }
	, _actionState{ logic }
	, _progressState{ logic }
	, _activateEventState{ logic }
	, _achieveState{ logic }
{
	first.Transition([](const WorldLogic& world) { return true; }, &_declareEventState);

	_declareEventState.SetEnter([](WorldLogic& world) {
		world.Round().DeclareEvent();
		});

	_declareEventState.Transition([](const WorldLogic& world) {
		return ui().IsIdle();
		}, &_collectTaxState);

	_collectTaxState.SetEnter([](WorldLogic& world) {
		world.Round().CollectTax();
		});

	_collectTaxState.Transition([](const WorldLogic& world) {
		return ui().IsIdle();
		}, &_throwDicesState);

	_throwDicesState.SetEnter([](WorldLogic& world) {
		world.Round().ThrowDices();
		});

	_throwDicesState.Transition([](const WorldLogic& world) {
		return true;
		}, &_actionState);

	_actionState.SetEnter([](WorldLogic& world) {
		INFO("=== BEGIN: ACTION STAGE ===");
		world.Round().BeginExecuteActions();
		});

	_actionState.SetUpdate([](WorldLogic& world) {
		if (!world.Round().AllActionsDone()) 
			world.Round().ExecuteNextAction();
		});

	_actionState.SetExit([](WorldLogic& world) {
		INFO("=== COMPLETE: ACTION STAGE ===");
		});

	_actionState.Transition([](const WorldLogic& world) {
		return ui().IsIdle() && world.Round().AllActionsDone();
		}, &_progressState);

	_progressState.SetEnter([](WorldLogic& world) {
		INFO("=== BEGIN: PROGRESS STAGE ===");
		world.Round().BeginProgressStage();
		});

	_progressState.SetUpdate([](WorldLogic& world) {
		world.Round().ExecuteProgressAction();
		});

	_progressState.Transition([](const WorldLogic& world) {
		return ui().IsIdle() && world.Round().AllProgressDone();
		}, &_activateEventState);

	_progressState.SetExit([](WorldLogic& world) {
		INFO("=== COMPLETE: PROGRESS STAGE ===");
		});

	_activateEventState.SetEnter([](WorldLogic& world) {
		INFO("=== BEGIN: GLOBAL EVENT ===");
		world.Round().ApplyGlobalEvent();
		});

	_activateEventState.Transition([](const WorldLogic& world) {
		return ui().IsIdle() && world.Round().AllEventEffectsApplied();
		}, &_achieveState);

	_activateEventState.SetExit([](WorldLogic& world) {
		INFO("=== COMPLETE: GLOBAL EVENT ===");
		});

	_achieveState.SetEnter([](WorldLogic& world) {
		INFO("=== BEGIN: ACHIEVE STAGE ===");		
		world.Players().ForEach([](PlayerLogic& player) {
			player.ResetActions();
			});
		});		

	_achieveState.Transition([](const WorldLogic& world) {
		return ui().IsIdle() && world.Players().All([](const PlayerLogic& player) { return player.IsIdle(); });
		}, &last);

	_achieveState.SetExit([](WorldLogic& world) {
		INFO("=== COMPLETE: ACHIEVE STAGE ===");
		});
}

void RoundState::Reset() {
}