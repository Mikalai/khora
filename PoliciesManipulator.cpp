#include <Messages/All.h>
#include "PoliciesManipulator.h"
#include "PlayerLogic.h"
#include "PolicyTemplate.h"
#include "WorldLogic.h"


PoliciesManipulator::PoliciesManipulator(WorldLogic& world)
	: _world{ world } {
}

PoliciesType PoliciesManipulator::GetNextPolicy() {
	return _world.GetNextPolicy();
}

bool PoliciesManipulator::CanTake() const {
	return _world._policyDeck.CanTake();
}

void PoliciesManipulator::Drop(PoliciesType policy) {
	_world._policyDeck.Drop(policy);
	PolicyDroppedMessage msg{ -1, policy };
	_world.Notify(msg);
}

void PoliciesManipulator::Shuffle() {
	_world.PoliciesDeck().Reset(true);
    
    _world.PoliciesDeck().ForEach([this](int i, PoliciesType p) {
		PolicyAddedToDeckMessage msg{ i, p };
	_world.Notify(msg);
		});

	PoliciesShuffledMessage msg{};
	_world.Notify(msg);
}

ConstPlayerPoliciesManipulator::ConstPlayerPoliciesManipulator(const PlayerLogic& world)
	: _player{ world } {

}

ConstPlayerFilteredInHandsPolicies ConstPlayerInHandsPoliciesManipulator::Where(PolicyFilter f) {
	return ConstPlayerFilteredInHandsPolicies{ f, _player };
}

ConstPlayerFilteredInHandsPolicies::ConstPlayerFilteredInHandsPolicies(PolicyFilter filter, const PlayerLogic& player)
	: _filter{ filter }
	, _player{ player } {
}

const PolicyTemplate* ConstPlayerFilteredInHandsPolicies::FirstOrNull() {
	
	for (auto& policy : _player._policiesInHands) {
		auto& tmp = GetPolicyTemplate(policy);
		if (_filter(_player, tmp)) {
			INFO("Player {} selected policy {} using id {}", _player.GetId(), (int)tmp.GetType(), (int)policy);
			return &tmp;
		}
	}	

	return nullptr;
}

void ConstPlayerInHandsPoliciesManipulator::ForEach(std::function<void(int index, const PolicyTemplate& policy)> cb) const {
	
	for (int i = 0; i < As<int>(_player._policiesInHands.size()); ++i) {
		auto& tmp = GetPolicyTemplate(_player._policiesInHands[i]);
		cb(i, tmp);
	}

}

ConstPlayerInActiveDeckPoliciesManipulator::ConstPlayerInActiveDeckPoliciesManipulator(const PlayerLogic& player)
	: _player{ player } {
}

ConstPlayerFilteredInActiveDeckPolicies ConstPlayerInActiveDeckPoliciesManipulator::Where(PolicyFilter f) {
	return ConstPlayerFilteredInActiveDeckPolicies{ f, _player };
}

void ConstPlayerInActiveDeckPoliciesManipulator::ForEach(std::function<void(int index, const PolicyTemplate& policy)> cb) const {
	for (int i = 0; i < As<int>(_player._policiesInActiveDeck.size()); ++i) {
		auto& tmp = GetPolicyTemplate(_player._policiesInActiveDeck[i]);
		cb(i, tmp);
	}
}


ConstPlayerInHandsPoliciesManipulator ConstPlayerPoliciesManipulator::InHands() {
	return { _player };
}

ConstPlayerInActiveDeckPoliciesManipulator ConstPlayerPoliciesManipulator::InActiveDeck() {
	return { _player };
}

const PolicyTemplate* ConstPlayerInHandsPoliciesManipulator::FirstOrNull() {
	if (_player._policiesInHands.empty())
		return nullptr;

	auto p = _player._policiesInHands.front();
	return &GetPolicyTemplate(p);
}

ConstPlayerInHandsPoliciesManipulator::ConstPlayerInHandsPoliciesManipulator(const PlayerLogic& player)
	:_player{ player } {
}

ConstPlayerFilteredInActiveDeckPolicies::ConstPlayerFilteredInActiveDeckPolicies(PolicyFilter filter, const PlayerLogic& world)
	: _filter{ filter }
	, _player{ world } {
}

const PolicyTemplate* ConstPlayerFilteredInActiveDeckPolicies::FirstOrNull() {
	for (auto& policy : _player._policiesInActiveDeck) {
		auto& tmp = GetPolicyTemplate(policy);
		if (_filter(_player, tmp)) {
			INFO("Player {} selected policy {} using id {}", _player.GetId(), (int)tmp.GetType(), (int)policy);
			return &tmp;
		}
	}

	return nullptr;
}