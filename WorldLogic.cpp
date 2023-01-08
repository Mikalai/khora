#pragma once

#include <cassert>
#include <chrono>
#include <algorithm>
#include <random>
#include <Messages/All.h>
#include "WorldLogicPrepare.h"
#include "WorldLogicRound.h"
#include "WorldLogic.h"
#include "PoliciesManipulator.h"
#include "EventsManipulator.h"

WorldLogic::WorldLogic() {
	for (int i = 0; i < players_count; ++i) {
		GetPlayer(i).SetId(i);
	}	
}

WorldLogicPrepare WorldLogic::Prepare() {
	return { *this };
}

bool WorldLogic::AllCitiesUnique() const {
	for (int i = 0; i < GetPlayersCount(); ++i) {
		auto& player = GetPlayer(i);
		if (player.GetCity() == city_unknown)
			return false;
		for (int j = i + 1; j < GetPlayersCount(); ++j) {
			auto& another = GetPlayer(j);
			if (player.GetCity() == another.GetCity())
				return false;
		}
		return true;
	}
	return false;
}

bool WorldLogic::AllColorsUnique() const {
	for (int i = 0; i < GetPlayersCount(); ++i) {
		auto& player = GetPlayer(i);
		if (player.GetColor() == player_color_unknown)
			return false;
		for (int j = i + 1; j < GetPlayersCount(); ++j) {
			auto& another = GetPlayer(j);
			if (player.GetColor() == another.GetColor())
				return false;
		}
		return true;
	}
	return false;
}

void WorldLogic::SetPlayersCount(int value) {
	_playersCount = std::max(2, std::min(4, value));
	for (int i = 0; i < _playersCount; ++i) {
		_players[i].SetWorld(this);
	}

	PlayerCountSelectedMessage msg(_playersCount);
	Notify(msg);
}

void WorldLogic::SetPlayerColor(int playerId, player_color color) {
	_players[playerId].SetColor(color);	
}

void WorldLogic::SetPlayerCity(int playerId, Cities city) {
	_players[playerId].SetCity(city);
}

int WorldLogic::GetPlayersCount() const { return _playersCount; }

PlayerLogic& WorldLogic::GetPlayer(int i) {
	return _players[i];
}

const PlayerLogic& WorldLogic::GetPlayer(int i) const {
	return _players[i];
}

bool WorldLogic::IsExpeditionAvailable(int index) const {
	return _expeditions[index];
}

const ExpeditionTemplate& WorldLogic::GetExpeditionInfo(int index) const {
	return GetExpeditionTemplate(index);
}

void WorldLogic::CompleteExpedition(int player, int index) {
	assert(IsExpeditionAvailable(index));
	_expeditions[index] = false;

	ExpeditionCompletedMessage msg(index);
	Notify(msg);
}

bool WorldLogic::IsPersipolisTaken() const {
	return _expeditions.back() == false;
}

Players WorldLogic::Players() {
	return ::Players{ *this };
}

ConstPlayers WorldLogic::Players() const {
	return ::ConstPlayers{ *this };
}

AllArmies WorldLogic::Armies() {
	return AllArmies{ *this };
}


Policies WorldLogic::GetNextPolicy() {
	auto policy = _policyDeck.Next();
	PolicyTakenFromDeckMessage msg{ std::get<0>(policy) };
	Notify(msg);
	return std::get<0>(policy);
}

bool WorldLogic::HasPoliciesInDeck() const {
	return !_policyDeck.Empty();
}

GlobalEventType WorldLogic::TakeNextEvent() {
	auto [evt, index] = _eventsDeck.Next();	
	EventTakenFromDeckMessage msg{ index, evt };
	Notify(msg);
	return evt;
}

void WorldLogic::CompleteDraft() {

	Players().ForEach([](PlayerLogic& player) {
		player.EndDraft();
		});

	_draftComplete = true;
	DraftCompletedMessage msg{};
	Notify(msg);
}

ConstPlayers::ConstPlayers(const WorldLogic& world)
	:_world{ world } {
}

bool ConstPlayers::All(std::function<bool(const PlayerLogic& player)> action) {
	bool result = true;
	for (int i = 0; i < _world.GetPlayersCount(); ++i) {
		result &= action(_world.GetPlayer(i));
	}
	return result;
}

bool WorldLogic::DraftComplete() const {
	return _draftComplete;
}

void WorldLogic::Subscribe(Observer<GameMessage>* observer) {
	Observable<GameMessage>::Subscribe(observer);
	for (auto& player : _players) {
		player.Subscribe(observer);
	}
}

PoliciesManipulator WorldLogic::Policies() {
	return { *this };
}

EventsManipulator WorldLogic::Events() {
	return { *this };
}

ConstEventsManipulator WorldLogic::Events() const {
	return { *this };
}

PoliciesDeck& WorldLogic::PoliciesDeck() {
	return _policyDeck;
}

::GlobalEventsDeck& WorldLogic::EventsDeck() {
	return _eventsDeck;
}

const ::GlobalEventsDeck& WorldLogic::EventsDeck() const {
	return _eventsDeck;
}

int WorldLogic::ValidatePlayerId(int playerId) const{
	assert(playerId >= 0 && playerId < GetPlayersCount());
	return playerId;
}

void WorldLogic::ActivateExpedition(int playerId, int discoveryId) {
	
}

//void WorldLogic::SetPhase(WorldLogic::RoundPhase phase) {
//	_currentPhase = phase;
//
//	switch (_currentPhase)
//	{
//	case WorldLogic::RoundPhase::DeclareEvent: {
//		BeginDeclareEventPhaseMessage msg;
//		Notify(msg);
//	}
//		break;
//	case WorldLogic::RoundPhase::CollectTaxes: {
//		BeginCollectTaxesPhaseMessage msg;
//		Notify(msg);
//	}
//		break;
//	case WorldLogic::RoundPhase::ThrowDices: {
//		BeginThrowDicesPhaseMessage msg;
//		Notify(msg);
//	}
//		break;
//	case WorldLogic::RoundPhase::Action: {
//		BeginActionPhaseMessage msg;
//		Notify(msg);
//	}
//		break;
//	case WorldLogic::RoundPhase::Progress: {
//		BeginProgressMessage msg{;
//		Notify(msg);
//	}
//		break;
//	case WorldLogic::RoundPhase::ActivateEvent: {
//		BeginActivateEventPhaseMessage msg;
//		Notify(msg);
//	}
//		break;
//	case WorldLogic::RoundPhase::Ahievments: {
//		BeginAhievmentsPhaseMessage msg;
//		Notify(msg);
//	}
//		break;
//	}
//}

WorldLogicRound WorldLogic::Round() {
	return { *this };
}

ConstWorldLogicRound  WorldLogic::Round() const {
	return { *this };
}

void WorldLogic::SetGlobalEvent(GlobalEventType evt) {
	int index = _eventsDeck.AddToOpen(evt);
	EventAddedToOpenDeckMessage msg{ index, evt };
	Notify(msg);
}

void WorldLogic::BeginExecuteActions() {
	_actionExecutionState.Reset(*this);
}

void WorldLogic::BeginProgressStage() {
	_progressState.Reset(*this);

	Players().ForEach([](PlayerLogic& player) {
		player.BeginProgressStage();
		});
}

void WorldLogic::EndProgressStage() {
	_progressState.Complete(*this);
	Players().ForEach([](PlayerLogic& player) {
		player.EndProgressStage();
		});
}

void WorldLogic::ActionExecutionState::Reset(WorldLogic& w) {

	_world = &w;
	int index = 0;
	std::array<int, 4> players;
	w.Players().OrderedByDices().Apply([&index, &players, this](PlayerLogic& p) {
		players[index] = p.GetId();
		index++;		
		});

	firstPlayer = w.Players().OrderedByDices().First();
}

bool WorldLogic::ActionExecutionState::IsComplete() const {
	return world().Players().All([](const PlayerLogic& p) {
		return p.AreActionsDone();
		});
}

std::tuple<bool, int, int, ActionType> WorldLogic::ActionExecutionState::Next() {
	
	assert(!IsComplete());

	int count = 0;
	std::array<std::tuple<int, int, ActionType>, 4> possibleActions;

	for (int i = firstPlayer; i < firstPlayer + world().GetPlayersCount(); ++i) {
		auto index = i % world().GetPlayersCount();

		auto& p = world().GetPlayer(index);
		if (p._actionExecutionState.IsComplete())
			continue;
		auto [diceValue, actionType] = p._actionExecutionState.Current();
		possibleActions[count] = std::tuple(index, diceValue, actionType);
		count++;
	}

	std::sort(possibleActions.begin(), possibleActions.begin() + count, [](auto& l, auto& r) {
		return std::get<2>(l) < std::get<2>(r);
		});

	auto action = possibleActions.front();
	bool newAction = action != lastAction;
	lastAction = action;
	return std::tuple(newAction, std::get<0>(action), std::get<1>(action), std::get<2>(action));
}

void WorldLogic::ProgressState::Reset(WorldLogic& w) {
	for (auto& v : lastUpgradedTracksCount) {
		v = -1;
	}
	stageInProgress = true;
	playersCount = w.GetPlayersCount();
}

void WorldLogic::ProgressState::Execute(WorldLogic& w, PlayerPerk cb) {
	for (int i = 0; i < playersCount; ++i) {
		auto& p = w.GetPlayer(i);
		auto stepsLeft = p._progressState.upgradedTracksCount;
		if (stepsLeft != lastUpgradedTracksCount[i]) {
			lastUpgradedTracksCount[i] = stepsLeft;
			cb(p);
		}
	}
}

void WorldLogic::ProgressState::Complete(WorldLogic& w) {
	stageInProgress = false;
}

void WorldLogic::EndGame() {
	int index = 1;
	Players().OrderedByPoints().Apply([&index](PlayerLogic& logic) {
		INFO("Player {} took {} place with {} score points! Congratulations!!!", logic.GetId(), index++, logic.GetPoints());
	});
}