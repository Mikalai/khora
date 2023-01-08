//#pragma once
//
//#include <UI/GeneralUserInput.h>
//#include <Resources.h>
//
//class WorldLogic;
//
//class NetworkUserInput sealed : public GeneralUserInput {
//public:
//	NetworkUserInput(WorldLogic& world);
//    void SelectPlayersCount() override;
//    void SelectPlayersColor() override;
//    void SelectCity() override;
//    void AdvanceAnyTrackForFree(int playerId) override;
//    void AdvanceAnyTrack(int playerId, int discont) override;
//    void AdvanceMilitaryTrack(int playerId, int discont) override;
//    void SelectArgosLevel2(int playerId) override;
//    void SelectThebesLevel2(int playerId) override;
//    void SelectExpedition(int playerId, SelectExpeditionCallback cb) override;
//    void PlayOstracism(int playerId) override;
//    void TakeDiscovery(int playerId, int count) override;
//    void DropPolicies(int playerId, int count) override;
//    void DropDiscovery(int playerId, DropDiscoveryCallback cb) override;
//    void TakePolicies(int playerId, int count) override;
//    void PlayPersiaCampaign() override;
//    void DoPhilosophyAction(int playerId) override;
//    void DoLawAction(int playerId) override;
//    void DoCultureAction(int playerId) override;
//    void DoTradeAction(int playerId) override;
//    void DoMilitaryAction(int playerId) override;
//    void DoPolicyAction(int playerId) override;
//    void DoExpandAction(int playerId) override;
//    void DoAnyActionExceptMilitary(int playerId) override;
//    void SelectPolicy(int playerId, Policies* a, int count, SelectPolicyCallback cb) override;	
//};
