#pragma once

#include <Resources.h>
#include <array>
#include <functional>

class PlayerLogic;
class IUserInputHandler;
class WorldLogic;

using SelectPolicyCallback = std::function<void(PoliciesType policy)>;
using SelectDiscoveryCallback = std::function<void(discovery_type d)>;

class ICityStrategy {
public:
	virtual ~ICityStrategy();
	virtual ActionType SelectAction(const PlayerLogic& world, int diceValue) = 0;
	virtual void ExecuteActionAsync(IUserInputHandler& user, ActionType action, std::function<void()> cb) = 0;
    virtual void SelectLawPolicy(IUserInputHandler& user, PoliciesType a, PoliciesType b, std::function<void(PoliciesType selected, PoliciesType dropped)> cb) = 0;
	virtual void SelectExpedition(IUserInputHandler& user, const WorldLogic& world, std::function<void(int)> cb) = 0;
	virtual void MakeProgress(IUserInputHandler& user, const WorldLogic& world, std::function<void(ProgressTrackType)> cb) = 0;
	virtual void SelectPolicy(IUserInputHandler& user, const WorldLogic& world, SelectPolicyCallback cb) = 0;
	virtual void SelectPolicyToDrop(IUserInputHandler& user, const WorldLogic& world, SelectPolicyCallback cb) = 0;
	virtual void SelectDiscoveryFromHands(IUserInputHandler& user, const WorldLogic& world, SelectDiscoveryCallback cb) = 0;
	virtual void SelectDiscoveryFromPool(IUserInputHandler& user, const WorldLogic& world, SelectDiscoveryCallback cb) = 0;
	virtual void SelectPolicyFromActiveDeck(IUserInputHandler& user, const WorldLogic& world, SelectPolicyCallback cb) = 0;
};
