#pragma once

#include <Resources.h>
#include <functional>

class WorldLogic;

using UpdateCallback = std::function<void(WorldLogic&)>;
using SelectPlayersCountCallback = std::function<void(int count)>;
using SelectCityColorCallback = std::function<void(player_color color)>;
using SelectCityCallback = std::function<void(Cities city)>;
using SelectPolicyFromDraftCallback = std::function<void(Policies policy)>;
using ThrowDiceCallback = std::function<void(int diceIndex, int diceValue)>;
using SelectActionsCallback = std::function<void(ActionType type)>;
using ExecuteActionCallback = std::function<void()>;
using SelectLawPolicyCallback = std::function<void(Policies selected, Policies dropped)>;
using SelectExpeditionCallback = std::function<void(int expedition)>;
using MakeProgressCallback = std::function<void(ProgressTrackType)>;
using SelectPolicyCallback = std::function<void(Policies policy)>;
using SelectDiscoveryCallback = std::function<void(discovery_type discovery)>;

class IUserInputHandler {
public:
    virtual ~IUserInputHandler();    
    /*virtual void AdvanceAnyTrackForFree() = 0;
    virtual void AdvanceAnyTrack(int discont) = 0;
    virtual void AdvanceMilitaryTrack(int discont) = 0;
	virtual void SelectArgosLevel2() = 0;
	virtual void SelectThebesLevel2() = 0;
	virtual void SelectExpedition(SelectExpeditionCallback cb) = 0;
    virtual void PlayOstracism() = 0;
    virtual void TakeDiscovery(int count) = 0;    
    virtual void DropPolicies(int count) = 0;
    virtual void DropDiscovery(DropDiscoveryCallback cb) = 0;
    virtual void TakePolicies(int count) = 0;
    virtual void PlayPersiaCampaign() = 0;    
    virtual void DoAnyActionExceptMilitary() = 0;

    virtual void DoPhilosophyAction() = 0;
	virtual void DoLawAction() = 0;
	virtual void DoCultureAction() = 0;
    virtual void DoTradeAction() = 0;
    virtual void DoMilitaryAction() = 0;
    virtual void DoPolicyAction() = 0;
    virtual void DoExpandAction() = 0;

	virtual void DoDraft() = 0;

    virtual void SelectPolicy(Policies* a, int count, SelectPolicyCallback cb) = 0;	*/
	virtual void SelectPlayersCountAsync(SelectPlayersCountCallback cb) = 0;
	virtual void SelectCityColorAsync(SelectCityColorCallback cb) = 0;
	virtual void SelectCityAsync(SelectCityCallback cb) = 0;
	virtual void SelectPolicyFromDraftAsync(SelectPolicyFromDraftCallback cb) = 0;
	virtual void ThrowDiceAsync(int diceIndex, ThrowDiceCallback cb) = 0;
	virtual void SelectActionAsync(int diceValue, bool allowMilitary, SelectActionsCallback cb) = 0;
	virtual void ExecuteActionAsync(ActionType action, ExecuteActionCallback cb) = 0;
	virtual void SelectLawPolicyAsync(Policies a, Policies b, SelectLawPolicyCallback cb) = 0;
	virtual void SelectExpeditionAsync(SelectExpeditionCallback cb) = 0;
	virtual void MakeProgressAsync(MakeProgressCallback cb) = 0;
	virtual void SelectPolicyFromHandsAsync(PolicySelectionReasonType reason, SelectPolicyCallback cb) = 0;
	virtual void SelectDiscoveryFromHandsAsync(SelectDiscoveryCallback cb) = 0;
	virtual void SelectDiscoveryFromPoolAsync(SelectDiscoveryCallback cb) = 0;
	virtual void SelectPolicyFromActiveDeckAsync(SelectPolicyCallback cb) = 0;

	virtual void Update(WorldLogic& world) = 0;
	virtual bool IsIdle() const = 0;
	virtual void PostWorldUpdateAction(UpdateCallback action) = 0;
	virtual int PlayerId() const = 0;
	// virtual void Next(GameMessage& msg) = 0;
	// virtual void Complete() = 0;
};
