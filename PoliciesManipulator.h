#pragma once

#include <Resources.h>

class PolicyTemplate;
class PlayerLogic;
class WorldLogic;

class PoliciesManipulator {
public:

	PoliciesManipulator(WorldLogic& world);
    PoliciesType GetNextPolicy();
	bool CanTake() const;
	void Shuffle();
    void Drop(PoliciesType policy);

private:
	WorldLogic& _world;
};

using PolicyFilter = std::function<bool(const PlayerLogic& player, const PolicyTemplate&)>;

class ConstPlayerFilteredInActiveDeckPolicies {
public:
	ConstPlayerFilteredInActiveDeckPolicies(PolicyFilter filter, const PlayerLogic& world);
	const PolicyTemplate* FirstOrNull();

private:
	PolicyFilter _filter;
	const PlayerLogic& _player;
};

class ConstPlayerFilteredInHandsPolicies {
public:
	ConstPlayerFilteredInHandsPolicies(PolicyFilter filter, const PlayerLogic& world);
	const PolicyTemplate* FirstOrNull();

private:
	PolicyFilter _filter;
	const PlayerLogic& _player;
};

class ConstPlayerInActiveDeckPoliciesManipulator {
public:
	ConstPlayerInActiveDeckPoliciesManipulator(const PlayerLogic& player);

	ConstPlayerFilteredInActiveDeckPolicies Where(PolicyFilter f);
	void ForEach(std::function<void(int index, const PolicyTemplate& policy)> cb) const;

private:
	const PlayerLogic& _player;
};

class ConstPlayerInHandsPoliciesManipulator {
public:
	ConstPlayerInHandsPoliciesManipulator(const PlayerLogic& player);

	ConstPlayerFilteredInHandsPolicies Where(PolicyFilter f);
	void ForEach(std::function<void(int index, const PolicyTemplate& policy)> cb) const;
	const PolicyTemplate* FirstOrNull();

private:
	const PlayerLogic& _player;
};


class ConstPlayerPoliciesManipulator {
public:

	ConstPlayerPoliciesManipulator(const PlayerLogic& world);

	ConstPlayerInHandsPoliciesManipulator InHands();
	ConstPlayerInActiveDeckPoliciesManipulator InActiveDeck();

private:
	const PlayerLogic& _player;
};
