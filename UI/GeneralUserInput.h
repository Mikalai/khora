#pragma once

#include <Messages/All.h>
#include <UI/IUserInputHandler.h>
#include <random>
#include <array>
#include <Observers.h>
#include <Messages/All.h>
#include <Resources.h>

class WorldLogic;
class PlayerLogic;
class IUserInputIdleMarker;

class GeneralUserInput : public IUserInputHandler /*public Observer<GameMessage> */ {
public:
    
    GeneralUserInput(int playerId, WorldLogic& world);
	virtual ~GeneralUserInput();

	void AddIdleMarker(std::unique_ptr<IUserInputIdleMarker>&& marker);
	void Update(WorldLogic& world) override;
	// void Next(GameMessage& msg) override;
	// void Complete() override;
	void PostWorldUpdateAction(UpdateCallback action) override;	
    void ExecuteActionAsync(ActionType action, std::function<void()> cb) override;

	int PlayerId() const override { return _playerId; }

protected:	

    //void ActivatePolicy(Policies* policy, int count, int selected, SelectPolicyCallback cb);
    void SetPlayersCount(int value);
    void SetPlayerColor(player_color color);
    void SetPlayerCity(Cities city);
    player_color GetColor(const std::string& value);
    Cities GetCity(const std::string& value);
    void AdvanceEconomyForFree();
    void AdvanceCultureForFree();
    void AdvanceMilitaryForFree();
	const PlayerLogic& GetPlayer() const;
	const WorldLogic& GetWorld() const;
	void ActivateThebesLevel2Perk();
	void ActivateArgosLevel2Perk(int code);
	void ActivateExpedition(int expeditionId, SelectExpeditionCallback cb);
    //void DoTrackAdvance(ProgressTrackType type, int discont);
    void DoDropPolicies(int count);    
    //void DoDropDiscovery(discovery_type policy);
    //void DoPersiaCampaign();

    /*void DoPhilosophyAction() override;
    void DoLawAction() override;
    void DoCultureAction() override;
    void DoTradeAction() override;
    void DoMilitaryAction() override;
    void DoPolicyAction() override;
    void DoExpandAction() override;
    void DoAnyActionExceptMilitary() override;*/
	bool IsIdle() const override;
		
protected:
       

    int NextRandomDiceValue();

private:

    WorldLogic& _world;
	std::vector<std::unique_ptr<IUserInputIdleMarker>> _idleMarkers;
    const int Front = 0;
    const int Back = 1;
	std::array<std::vector<UpdateCallback>, 2> _updateCbs;
	int _playerId;
    std::random_device dev;
    std::mt19937 rng{ dev() };
    std::uniform_int_distribution<std::mt19937::result_type> diceDist{ 1, 6 };

	mutable SpinLock _lock;

       
};
//
//template<typename T>
//class GenericUserInput : public GeneralUserInput {
//    
//protected:
//
//    GenericUserInput(int playerId, WorldLogic& world)
//        : GeneralUserInput(playerId, world){}
//
//    template<typename U>
//    void On(std::function<void(T&, U& msg)> action)
//    {
//        Map().On([action](GeneralUserInput& self, U& msg) {
//            action(static_cast<T&>(self), msg);
//            });
//    }
//};

#define CONNECT(T) On<T>([](auto& self, auto& msg) { self.Handle(msg); })