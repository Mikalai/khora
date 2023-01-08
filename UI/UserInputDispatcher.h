#pragma once

#include <functional>
#include <array>
#include <Resources.h>
#include <Observers.h>
#include <UI/IUserInput.h>
#include <UI/AIUserInput.h>
#include <Messages/All.h>
#include <UI/AllHandler.h>

class UserInputDispatcher;
class WorldLogic;

using UpdateCallback = std::function<void(WorldLogic& world)>;

class UserInputDispatcher : public IUserInput, public Observer<GameMessage> {
public:	
	UserInputDispatcher(WorldLogic& logic);
	void SelectPlayersCount() override;
	void SelectPlayersColor() override;
	void SelectCity() override;
	//void AdvanceAnyTrackForFree(int playerId) override;
	//void AdvanceAnyTrack(int playerId, int discont) override;
	//void AdvanceMilitaryTrack(int playerId, int discont) override;
	//void SelectArgosLevel2(int playerId) override;
	//void SelectThebesLevel2(int playerId) override;
	//void SelectExpedition(int playerId, SelectExpeditionCallback cb) override;
	//void PlayOstracism(int playerId) override;
	//void TakeDiscovery(int playerId, int count) override;
	//void DropPolicies(int playerId, int count) override;
	// void DropDiscovery(int playerId, DropDiscoveryCallback cb) override;
	//void TakePolicies(int playerId, int count) override;
	//void PlayPersiaCampaign() override;
	//void DoAnyActionExceptMilitary(int playerId) override;

	/*void DoPhilosophyAction(int playerId) override;
	void DoLawAction(int playerId) override;
	void DoCultureAction(int playerId) override;
	void DoTradeAction(int playerId) override;
	void DoMilitaryAction(int playerId) override;
	void DoPolicyAction(int playerId) override;
	void DoExpandAction(int playerId) override;*/

	//void DoDraft(int playerId) override;

	//void SelectPolicy(int playerId, Policies* a, int count, SelectPolicyCallback cb) override;
	void SetHandler(int playerId, IUserInputHandler* handler) override;
	void SetPlayersCount(int count);
	void Update(WorldLogic& world) override;
	bool IsIdle() const override;

	void Next(GameMessage& msg) override;
	void Complete() override;

	AllHandler Handlers();

protected:

	void AddUpdateCallback(UpdateCallback cb);

private:
	WorldLogic& _world;
	int _playersCount{ 0 };	
	std::array<IUserInputHandler*, 4> _handlers{nullptr};

	IUserInputHandler& Get(int playerId) { return *_handlers[playerId]; }

	SpinLock _lock;
	std::array<std::vector<UpdateCallback>, 2> _updateCallbacks;
	std::array<AIUserInput, 4> _aiHandlers;
	friend struct AllHandler;
};
