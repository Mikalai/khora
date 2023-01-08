#pragma once

#include <array>
#include <algorithm>
#include <numeric>
#include <random>
#include <PlayerLogic.h>
#include <ExpeditionTemplate.h>
#include <EventsManipulator.h>
#include <PoliciesManipulator.h>
#include <cassert>
#include <PoliciesDeck.h>
#include <GlobalEventsDeck.h>
#include <AllArmies.h>
#include <Players.h>
#include <PlayersConst.h>

class WorldLogicPrepare;
class WorldLogicRound;
class ConstWorldLogicRound;

class WorldLogic : public Observable<GameMessage> {
    friend class PoliciesManipulator;    
    friend class EventsManipulator;
	friend class ConstEventsManipulator;
    friend class WorldLogicPrepare;
    friend class WorldLogicRound;
    friend class ConsWorldLogicRound;
public:

    WorldLogic();

	WorldLogic(const WorldLogic& ) = delete;
	WorldLogic(WorldLogic&&) = delete;
	WorldLogic& operator = (const WorldLogic&) = delete;
	WorldLogic& operator = (WorldLogic&&) = delete;

    WorldLogicPrepare Prepare();
    WorldLogicRound Round();
    ConstWorldLogicRound Round() const;
    bool AllCitiesUnique() const;
    bool AllColorsUnique() const;
    bool DraftComplete() const;
    void SetPlayersCount(int value);
    void SetPlayerColor(int playerId, player_color color);
    void SetPlayerCity(int playerId, Cities city);
    int GetPlayersCount() const;
    PlayerLogic& GetPlayer(int i);
    const PlayerLogic& GetPlayer(int i) const;

	bool IsExpeditionAvailable(int index) const;
	const ExpeditionTemplate& GetExpeditionInfo(int index) const;
	void CompleteExpedition(int player, int index);
    bool IsPersipolisTaken() const;
    AllArmies Armies();
    Players Players();
    ConstPlayers Players() const;    
    void CompleteDraft();    
    void ActivateExpedition(int playerId, int expeditionId);

    PoliciesManipulator Policies();
    EventsManipulator Events();
	ConstEventsManipulator Events() const;

    void Subscribe(Observer<GameMessage>* observer) override;  
	void EndGame();

private:
    ::Policies GetNextPolicy();
	bool HasPoliciesInDeck() const;
    GlobalEventType TakeNextEvent();
    ::PoliciesDeck& PoliciesDeck();
    ::GlobalEventsDeck& EventsDeck();
	const ::GlobalEventsDeck& EventsDeck() const;
    void SetGlobalEvent(GlobalEventType evt);

    int ValidatePlayerId(int playerId) const;

    void BeginExecuteActions();
    void BeginProgressStage();
    void EndProgressStage();
private:
    enum class RoundPhase {
        Init = -1,
        DeclareEvent,
        CollectTaxes,
        ThrowDices,
        Action,
        Progress,
        ActivateEvent,
        Ahievments,
        Count
    };

    //void SetPhase(RoundPhase phase);

private:

    int _currentPlayer{ -1 };
    //RoundPhase _currentPhase{ RoundPhase::Init };
    int _round{ 0 };
    int _playersCount;
    ::PoliciesDeck _policyDeck;
    GlobalEventsDeck _eventsDeck;
    bool _draftComplete{ false };
	std::array<bool, GetExpeditionsCount()> _expeditions;
    std::array<PlayerLogic, 4> _players;

    struct ActionExecutionState {
        int playersCount;
        int firstPlayer;

        std::tuple<int, int, ActionType> lastAction;

        void Reset(WorldLogic& w);
        bool IsComplete() const;
        std::tuple<bool, int, int, ActionType> Next();

    private:
        WorldLogic& world() { return *_world; }
        const WorldLogic& world() const { return *_world; }
        WorldLogic* _world;
    };

    ActionExecutionState _actionExecutionState;

    struct ProgressState {
        int playersCount = 0;
        std::array<int, 4> lastUpgradedTracksCount;
        bool stageInProgress;
        void Reset(WorldLogic& w);
        void Execute(WorldLogic& w, PlayerPerk cb);
        void Complete(WorldLogic& w);        
    };

    ProgressState _progressState;
};
