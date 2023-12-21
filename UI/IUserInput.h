#pragma once

#include <functional>
#include <Resources.h>
#include <memory>

struct GameMessage;
class PlayerLogic;
class WorldLogic;
using DropDiscoveryCallback = std::function<void(PlayerLogic& player, int count)>;
//using SelectPolicyCallback = std::function<void(PlayerLogic& player, PoliciesType* other, int count, int selected)>;
// using SelectExpeditionCallback = std::function<void(PlayerLogic& player, int expedition)>;
using DraftStepCallback = std::function<void(PlayerLogic& player, PoliciesType policy)>;
class IUserInputHandler;

class IUserInput {
public:
	virtual ~IUserInput();
	virtual void SelectPlayersCount() = 0;
	virtual void SelectPlayersColor() = 0;
	virtual void SelectCity() = 0;
	//virtual void AdvanceAnyTrackForFree(int playerId) = 0;
	//virtual void AdvanceAnyTrack(int playerId, int discont) = 0;
	//virtual void AdvanceMilitaryTrack(int playerId, int discont) = 0;
	//virtual void SelectArgosLevel2(int playerId) = 0;
	//virtual void SelectThebesLevel2(int playerId) = 0;
	//virtual void SelectExpedition(int playerId, SelectExpeditionCallback cb) = 0;
	//virtual void PlayOstracism(int playerId) = 0;
	//virtual void TakeDiscovery(int playerId, int count) = 0;
	//virtual void DropPolicies(int playerId, int count) = 0;
	//virtual void DropDiscovery(int playerId, DropDiscoveryCallback cb) = 0;
	//virtual void TakePolicies(int playerId, int count) = 0;
	//virtual void PlayPersiaCampaign() = 0;
	//virtual void DoAnyActionExceptMilitary(int playerId) = 0;

	/*virtual void DoPhilosophyAction(int playerId) = 0;
	virtual void DoLawAction(int playerId) = 0;
	virtual void DoCultureAction(int playerId) = 0;
	virtual void DoTradeAction(int playerId) = 0;
	virtual void DoMilitaryAction(int playerId) = 0;
	virtual void DoPolicyAction(int playerId) = 0;
	virtual void DoExpandAction(int playerId) = 0;*/

	//virtual void DoDraft(int playerId) = 0;

	//virtual void SelectPolicy(int playerId, Policies* a, int count, SelectPolicyCallback cb) = 0;
	virtual void SetHandler(int playerId, IUserInputHandler* handler) = 0;
	virtual void SetPlayersCount(int count) = 0;
	virtual void Update(WorldLogic& world) = 0;
	virtual bool IsIdle() const = 0;	
};
