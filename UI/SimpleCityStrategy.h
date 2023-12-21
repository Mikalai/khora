#pragma once

#include <UI/ICityStrategy.h>

class SimpleCityStrategy : public ICityStrategy {
public:

	ActionType SelectAction(const PlayerLogic& player, int diceValue) override;
	void ExecuteActionAsync(IUserInputHandler& user, ActionType action, std::function<void()> cb) override;
    void SelectLawPolicy(IUserInputHandler& user, PoliciesType a, PoliciesType b, std::function<void(PoliciesType selected, PoliciesType dropped)> cb) override;
	void SelectExpedition(IUserInputHandler& user, const WorldLogic& world, std::function<void(int)> cb) override;
	void MakeProgress(IUserInputHandler& user, const WorldLogic& world, std::function<void(ProgressTrackType)> cb) override;
	void SelectPolicy(IUserInputHandler& user, const WorldLogic& world, SelectPolicyCallback cb) override;
	void SelectPolicyToDrop(IUserInputHandler& user, const WorldLogic& world, SelectPolicyCallback cb) override;
	void SelectDiscoveryFromHands(IUserInputHandler& user, const WorldLogic& player, SelectDiscoveryCallback cb) override;
	void SelectDiscoveryFromPool(IUserInputHandler& user, const WorldLogic& player, SelectDiscoveryCallback cb) override;
	void SelectPolicyFromActiveDeck(IUserInputHandler& user, const WorldLogic& player, SelectPolicyCallback cb) override;
};