#pragma once

#include "WorldLogicRound.h"
#include "WorldLogic.h"
#include "EventsManipulator.h"
#include <Platform/NumberConverter.h>
#include <Messages/All.h>
#include <EventTemplate.h>
#include <PlayerPerks.h>

WorldLogicRound::WorldLogicRound(WorldLogic& world)
	: _world{ world } {
}

void WorldLogicRound::DeclareEvent() {
	//_world.SetPhase(WorldLogic::RoundPhase::DeclareEvent);
	_world.Events().SelectNextEvent();	
}

void WorldLogicRound::CollectTax() {
	_world.Players().ForEach([](PlayerLogic& p) {
		auto tax = p.GetTax();
		p.AddMoney(tax);
		p.Perks().Tax().Apply();
		});
}
void WorldLogicRound::ThrowDices() {
	_world.Players().ForEach([](PlayerLogic& player) {
		player.ResetDices();		
		});

	_world.Players().ForEach([](PlayerLogic& player) {
		player.ThrowDices();
		});
}

void WorldLogicRound::IdentifyOrder() {	
	_world.Players().ForEach([](PlayerLogic& player) {
		player.SortDices();
		});
}

void WorldLogicRound::ApplyThrowDicesStagePerks() {
	auto evt = _world.EventsDeck().Current();
	auto t = GetEventTemplate(evt);
	if (t.GetStage() == GlobalEventStage::DiceStage) {
		t.GetEffect().Apply(_world);		
	}
}

void WorldLogicRound::SelectActions() {
	_world.Players().ForEach([](PlayerLogic& player) {
		player.BeginSelectAction(player.GetDice(0), true, [&player](ActionType type) {
			INFO("Player {} selected for dice {} with value {} action {} ({})", player.GetId(), 0, player.GetDice(0), ActionToString[(int)type], (int)type);
			player.SetAction(0, type);
			player.BeginSelectAction(player.GetDice(1), true, [&player](ActionType type) {
				INFO("Player {} selected for dice {} with value {} action {} ({})", player.GetId(), 1, player.GetDice(1), ActionToString[(int)type], (int)type);
				player.SetAction(1, type);
				if (player.GetDiceCount() == 3) {
					player.BeginSelectAction(player.GetDice(2), true, [&player](ActionType type) {
						INFO("Player {} selected for dice {} with value {} action {} ({})", player.GetId(), 2, player.GetDice(2), ActionToString[(int)type], (int)type);
						player.SetAction(2, type);
						});
				}
				});
			});
		});

	/*BeginSelectActionsMessage msg{ true };
	_world.Notify(msg);*/
}

void WorldLogicRound::OpenActions() {
	OpenSelectedActionsMessage msg{};
	_world.Notify(msg);
}

bool WorldLogicRound::AllActionsDone() const {
	return _world.Players().All([](const PlayerLogic& player) {
		return player.AreActionsDone();
		});
}

ConstWorldLogicRound::ConstWorldLogicRound(const WorldLogic& world)
	:_world{ world } {
}

bool ConstWorldLogicRound::AllActionsDone() const {
	return _world.Players().All([](const PlayerLogic& player) {
		return player.AreActionsDone() && player.IsIdle();
		});
}

bool ConstWorldLogicRound::AllProgressDone() const {
	return _world.Players().All([](const PlayerLogic& player) {
		return player.IsProgressDone() && player.IsIdle();
		});
}

bool ConstWorldLogicRound::AllEventEffectsApplied() const {
	auto& evt = _world.Events().Current();
	if (evt.GetStage() == GlobalEventStage::DiceStage)
		return true;

	return _world.Players().All([](const PlayerLogic& player) {
		return player.IsIdle();
		});
}

void WorldLogicRound::BeginExecuteActions() {
	_world.BeginExecuteActions();
	_world.Players().ForEach([](PlayerLogic& player) {
		player.BeginExecuteActions();
		});
}

void WorldLogicRound::ExecuteNextAction() {
	auto [newAction, playerId, diceCount, actionType] = _world._actionExecutionState.Next();
	if (newAction) {		
		auto requireValue = As<int>(actionType);
		bool canExecute = true;
		auto diff = diceCount - requireValue;

		if (diff < 0) {
			auto population = _world.GetPlayer(playerId).GetPopulation();
			if (population + diff >= 0) {
				_world.GetPlayer(playerId).RemovePopulation(-diff);
			}
			else {
				canExecute = false;
			}
		}

		if (canExecute) {
			_world.GetPlayer(playerId).BeginExecuteAction(diceCount, actionType, [&world = _world, playerId = playerId]() mutable {
					INFO("Player {} ExecuteNextAction", playerId);
					world.GetPlayer(playerId).ExecuteNextAction();
				});			
		}
	}
}

void WorldLogicRound::BeginProgressStage() {
	_world.BeginProgressStage();	
}

void WorldLogicRound::ExecuteProgressAction() {
	_world._progressState.Execute(_world, [](PlayerLogic& player) {
		BeginProgressMessage msg{ player.GetId() };
		player.Notify(msg);
	});
}

void WorldLogicRound::EndProgressStage() {
	_world.EndProgressStage();	
}

void WorldLogicRound::ApplyGlobalEvent() {
	auto& evt = _world.Events().Current();
	if (evt.GetStage() == GlobalEventStage::DiceStage)
		return;

	INFO("Global event: {}", ToString(evt.GetType()));

	evt.GetEffect().Apply(_world);
}
