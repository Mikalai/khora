#pragma once

#include <UI/GeneralUserInput.h>
#include <mutex>
#include <deque>
#include <condition_variable>
#include <thread>
#include <Resources.h>

class WorldLogic;

class ConsoleUserInput final : public GeneralUserInput {
	using CallbackFunction = std::function<bool(std::istream& msg)>;
public:
	ConsoleUserInput(int playerId, WorldLogic& world);
	virtual ~ConsoleUserInput();
	void SelectPlayersCountAsync(std::function<void(int count)> cb) override;
	void SelectCityColorAsync(std::function<void(player_color color)> cb) override;
	void SelectCityAsync(std::function<void(Cities city)> cb) override;
    void SelectPolicyFromDraftAsync(std::function<void(Policies policy)> cb) override;
    //void AdvanceAnyTrackForFree() override;
    //void AdvanceAnyTrack(int discont) override;
    //void AdvanceMilitaryTrack(int discont) override;
    //void SelectArgosLevel2() override;
    //void SelectThebesLevel2() override;
    //void SelectExpedition(SelectExpeditionCallback cb) override;
    //void PlayOstracism() override;
    //void TakeDiscovery(int count) override;
    //void DropPolicies(int count) override;
    //void DropDiscovery(DropDiscoveryCallback cb) override;
    //void TakePolicies(int count) override;
    //void PlayPersiaCampaign() override;
    //void DoPhilosophyAction() override;
    //void DoLawAction() override;
    //void DoCultureAction() override;
    //void DoTradeAction() override;
    //void DoMilitaryAction() override;
    //void DoPolicyAction() override;
    //void DoExpandAction() override;
    //void DoAnyActionExceptMilitary() override;
    //void SelectPolicy(Policies* a, int count, SelectPolicyCallback cb) override;	
	//void DoDraft();
	//void Complete() override;
private:
	void TerminalInput();

	void AddCallback(CallbackFunction cb);

private:
	std::thread _thread;
	std::atomic_bool _terminate;
	std::mutex _cs;
	std::condition_variable _cv;	
	std::deque<CallbackFunction> _callbacks;
};
