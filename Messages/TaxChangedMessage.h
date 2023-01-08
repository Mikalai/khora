#pragma once

#include <Resources.h>
#include <Messages/GameMessage.h>

class WorldLogic;

struct TaxChangedMessage : GameMessage {

    TaxChangedMessage(int playerId, int tax)
        : GameMessage(MessageType::MsgTaxChanged)
        , player{ playerId }
        , tax{ tax }
    {
    }

    int player;
    int tax;
};


struct EconomyChangedMessage : GameMessage {
    EconomyChangedMessage(int playerId, int economy)
        : GameMessage(MessageType::MsgEconomyChanged)
        , player{ playerId }
        , economy{ economy } {
    }

    int player;
    int economy;
};

struct CultureChangedMessage : GameMessage {
    CultureChangedMessage(int playerId, int culture)
        : GameMessage(MessageType::MsgCultureChanged)
        , player{ playerId }
        , culture{ culture } {
    }

    int player;
    int culture;
};

struct MilitaryChangedMessage : GameMessage {
    MilitaryChangedMessage(int playerId, int military)
        : GameMessage(MessageType::MsgMilitaryChanged)
        , player{ playerId }
        , military{ military } {
    }

    int player;
    int military;
};

struct PhilosophyAddedMessage : GameMessage {
    PhilosophyAddedMessage(int playerId, int count)
        : GameMessage(MessageType::MsgPhilosophyAdded)
        , player{ playerId }
        , count{ count } {
    }

    int player;
    int count;
};

struct PhilosophyRemovedMessage : GameMessage {
    PhilosophyRemovedMessage(int playerId, int count)
        : GameMessage(MessageType::MsgPhilosophyRemoved)
        , player{ playerId }
        , count{ count } {
    }

    int player;
    int count;
};

struct ScorePointsChangedMessage : GameMessage {
    ScorePointsChangedMessage(int playerId, int points)
        : GameMessage(MessageType::MsgScorePointsChanged)
        , player{ playerId }
        , points{ points } {
    }

    int player;
    int points;
};

struct ArmyChangedMessage : GameMessage {
	ArmyChangedMessage(int playerId, int army)
		: GameMessage(MessageType::MsgArmyChanged)
		, player{ playerId }
		, army{ army } {
	}

	int player;
	int army;
};

struct GloryChangedMessage : GameMessage {
	GloryChangedMessage(int playerId, int glory)
		: GameMessage(MessageType::MsgGloryChanged)
		, player{ playerId }
		, glory{ glory } {
	}

	int player;
	int glory;
};

struct CityLevelChangedMessage : GameMessage {
    CityLevelChangedMessage(int playerId, int cityLevel)
        : GameMessage(MessageType::MsgCityLevelChanged)
        , player{ playerId }
        , cityLevel{ cityLevel }
    {}

    int player;
    int cityLevel;
};

struct DiscoveryAddedMessage : GameMessage {
	DiscoveryAddedMessage(int playerId, discovery_type discovery, int index, int expedition, int indexInExpedition, int selectionIndex)
		: GameMessage(MessageType::MsgDiscoveryAdded)
		, player{ playerId }
		, discovery{ discovery }
        , index{index}
        , expedition { expedition }
        , indexInExpedition{ indexInExpedition }
        , selectionIndex{ selectionIndex }
	{}

	int player;
	discovery_type discovery;
    int index;
    int expedition;
    int indexInExpedition;
    int selectionIndex;
};

struct DiscoveryRemovedMessage : GameMessage {
	DiscoveryRemovedMessage(int playerId, discovery_type disc, int index)
		: GameMessage(MessageType::MsgDiscoveryRemoved)
		, player{ playerId }
		, discovery{ disc }
        , index{index}
	{}

	int player;
	discovery_type discovery;
    int index;
};

struct ExpeditionCompletedMessage : GameMessage {
	ExpeditionCompletedMessage(int expedition)
		: GameMessage(MessageType::MsgExpeditionCompleted)
		, expedition{ expedition } {}

	int expedition;
};

struct PopulationChangedMessage : GameMessage {

	PopulationChangedMessage(int playerId, int population)
		: GameMessage(MessageType::MsgPopulationChanged)
		, player{ playerId }
		, population{ population }
	{}

	int player;
	int population;
};

struct DiceUnlockedMessage : GameMessage {

    DiceUnlockedMessage(int playerId)
        : GameMessage(MessageType::MsgDiceUnlocked)
        , player{ playerId }
    {}

    int player;
};

struct PolicyDroppedMessage : GameMessage {
    
    PolicyDroppedMessage(int playerId, Policies policy)
        : GameMessage(MessageType::MsgPolicyDropped)
        , player{ playerId }
        , policy{ policy }
    {}

    int player;
    Policies policy;
};

struct DiscoveryDroppedMessage : GameMessage {

    DiscoveryDroppedMessage(int playerId, discovery_type discovery)
        : GameMessage(MessageType::MsgDiscoveryDropped)
        , player{ playerId }
        , discovery{ discovery }
    {}

    int player;
    discovery_type discovery;
};

struct PolicyAddedInHandsMessage : GameMessage {

    PolicyAddedInHandsMessage(int playerId, Policies policy, bool selectFlag)
        : GameMessage(MessageType::MsgPolicyTakenInHands)
        , player{ playerId }
        , policy{ policy }
        , selectFlag{ selectFlag }
    {}

    int player;
    Policies policy;
    bool selectFlag;
};

struct PolicyAddedToPlayedMessage : GameMessage {

    PolicyAddedToPlayedMessage(int playerId, Policies policy, int index)
        : GameMessage(MessageType::MsgPolicyAddedToPlayed)
        , player{ playerId }
        , policy{ policy }
        , index{ index }
    {}

    int player;
    Policies policy;
    int index;
};

struct PolicyRemovedFromHandsMessage : GameMessage {

	PolicyRemovedFromHandsMessage(int playerId, Policies policy, int index)
		: GameMessage(MessageType::MsgPolicyRemovedFromHands)
		, player{ playerId }
		, policy{ policy }
        , index{ index }
	{}

	int player;
	Policies policy;
    int index;
};

struct PolicyActivatedMessage : GameMessage {
    
    PolicyActivatedMessage(int playerId, Policies policy)
        : GameMessage(MessageType::MsgPolicyActivated)
        , player{ playerId }
        , policy{ policy }
    {}

    int player;
    Policies policy;
};

struct DraftCompletedMessage : GameMessage {
    DraftCompletedMessage() 
        : GameMessage{MessageType::MsgDraftComplete}
    {
    }
};

struct PolicyTakenFromDeckMessage : GameMessage {

    PolicyTakenFromDeckMessage(Policies policy)
        : GameMessage{ MessageType::MsgPolicyTakenFromDeck }
        , policy{ policy } {
    }

    Policies policy;
};

struct PlayerCountSelectedMessage : GameMessage {
    PlayerCountSelectedMessage(int count)
        : GameMessage{ MessageType::MsgPlayerCountSelected }
        , playersCount{count}
    {}

    int playersCount;
};

struct CitySelectedMessage : GameMessage {
    CitySelectedMessage(int playerId, Cities city)
        : GameMessage{ MessageType::MsgCitySelected }
        , player{ playerId }
        , city{ city } {}

    int player;
    Cities city;
};

struct PlayerColorSelectedMessage : GameMessage {
    
    PlayerColorSelectedMessage(int playerId, player_color color)
        : GameMessage{ MessageType::MsgPlayerColorSelected }
        , player{ playerId }
        , color{ color } {}

    int player;
    player_color color;
};

struct PoliciesShuffledMessage : GameMessage {
    PoliciesShuffledMessage()
        : GameMessage{ MessageType::MsgPoliciesShuffled } {}
};

struct PolicyAddedToDeckMessage : GameMessage {

    PolicyAddedToDeckMessage(int index, Policies policy)
        : GameMessage{MessageType::MsgPolicyTakenInHandsToDeck}
        , index{index}
        , policy{ policy }
    {
    }

    int index;
    Policies policy;
};

struct EventsShuffledMessage : GameMessage {
    EventsShuffledMessage()
        : GameMessage{ MessageType::MsgEventsShuffled }
    {}
};

struct EventAddedToDeckMessage : GameMessage {

    EventAddedToDeckMessage(int index, GlobalEventType event)
        : GameMessage{ MessageType::MsgEventAddedToDeck }
        , index{ index }
        , event{ event }
    {
    }

    int index;
    GlobalEventType event;
};

struct EventAddedToOpenDeckMessage : GameMessage {

    EventAddedToOpenDeckMessage(int index, GlobalEventType event)
        : GameMessage{ MessageType::MsgEventAddedToOpenDeck }
        , index{ index }
        , event{ event }
    {
    }

    int index;
    GlobalEventType event;
};

struct EventTakenFromDeckMessage : GameMessage {

    EventTakenFromDeckMessage(int index, GlobalEventType event)
        : GameMessage{ MessageType::MsgEventTakenFromDeck }
        , index{ index }
        , event{ event } {
    }

    int index;
    GlobalEventType event;
};
struct PolicyAddedToDraftMessage : GameMessage {
	PolicyAddedToDraftMessage(int player, Policies policy, int index)
		: GameMessage{MessageType::MsgPolicyAddedToDraft }
		, player{player}
		, policy{policy}
		, index{index}
	{}

	int player;
	Policies policy;
	int index;
};

struct PolicyRemovedFromDraftMessage : GameMessage {

	PolicyRemovedFromDraftMessage(int player, Policies policy, int index)
		: GameMessage{ MessageType::MsgPolicyRemovedFromDraft } 
		, player{player}
		, policy{policy}
		, index{index}
	{
	}

	int player;
	int index;
	Policies policy;
};


struct BeginCitySelectionMessage : GameMessage {
	BeginCitySelectionMessage()
		: GameMessage{ MessageType::MsgBeginCitySelection } {}
};

struct EndCitySelectionMessage : GameMessage {
	EndCitySelectionMessage()
		: GameMessage{ MessageType::MsgEndCitySelection } {}
};

struct BeginSelectPlayersCountMessage : GameMessage {
	BeginSelectPlayersCountMessage()
		: GameMessage{ MessageType::MsgBeginSelectPlayersCount } {
	}
};

struct BeginSelectCityColorMessage : GameMessage {
	BeginSelectCityColorMessage()
		: GameMessage{ MessageType::MsgBeginSelectCityColor } {
	}
};

struct BeginDraftMessage : GameMessage {
    BeginDraftMessage(int playerId)
        : GameMessage{ MessageType::MsgBeginDraft } 
        , player{ playerId }
    {}

    int player;
};

struct AddMoneyMessage : GameMessage {
    AddMoneyMessage(int playerId, int count)
        : GameMessage{ MessageType::MsgAddMoney }
        , player{ playerId }
        , count{ count } {}

    int player;
    int count;
};

struct RemoveMoneyMessage : GameMessage {
    RemoveMoneyMessage(int playerId, int count)
        : GameMessage{ MessageType::MsgRemoveMoney }
        , player{ playerId }
        , count{ count } {}

    int player;
    int count;
};

struct ExpeditionAddedMessage : GameMessage {
    ExpeditionAddedMessage(int expeditionId)
        : GameMessage{ MessageType::MsgExpeditionAdded }
        , id{ expeditionId } {
    }

    int id;
};

struct BeginDeclareEventPhaseMessage : GameMessage {
    BeginDeclareEventPhaseMessage()
        : GameMessage{ MessageType::MsgBeginDeclareEventPhase } {
    }
};

struct BeginCollectTaxesPhaseMessage : GameMessage {
    BeginCollectTaxesPhaseMessage()
        : GameMessage{ MessageType::MsgBeginCollectTaxesPhase } {
    }
};

struct BeginThrowDicesPhaseMessage: GameMessage{
    BeginThrowDicesPhaseMessage()
        : GameMessage{ MessageType::MsgBeginThrowDicesPhase } {
    }
};

struct BeginActionPhaseMessage : GameMessage {
    BeginActionPhaseMessage()
        : GameMessage{ MessageType::MsgBeginActionPhase } {
    }
};

struct BeginProgressMessage : GameMessage {
    BeginProgressMessage(int playerId)
        : GameMessage{ MessageType::MsgBeginProgress } 
        , playerId{ playerId } {
    }

    int playerId;
};

struct BeginExtraProgressMessage : GameMessage {
	BeginExtraProgressMessage(int playerId, int discont, ProgressTrackType allowedTrack)
		: GameMessage{ MessageType::MsgBeginExtraProgress }
		, playerId{ playerId } 
		, discont{discont}
		, allowedTrack{ allowedTrack }
	{
	}

	int playerId;
	int discont;
	ProgressTrackType allowedTrack;
};

struct BeginActivateEventPhaseMessage : GameMessage {
    BeginActivateEventPhaseMessage()
        : GameMessage{ MessageType::MsgBeginActivateEventPhase } {
    }
};
  
struct BeginAhievmentsPhaseMessage : GameMessage {
    BeginAhievmentsPhaseMessage()
        : GameMessage{ MessageType::MsgBeginAhievmentsPhase } {
    }
};



struct EndDeclareEventPhaseMessage : GameMessage {
    EndDeclareEventPhaseMessage()
        : GameMessage{ MessageType::MsgEndDeclareEventPhase } {
    }
};

struct EndCollectTaxesPhaseMessage : GameMessage {
    EndCollectTaxesPhaseMessage()
        : GameMessage{ MessageType::MsgEndCollectTaxesPhase } {
    }
};

struct EndThrowDicesPhaseMessage : GameMessage {
    EndThrowDicesPhaseMessage()
        : GameMessage{ MessageType::MsgEndThrowDicesPhase } {
    }
};

struct EndActionPhaseMessage : GameMessage {
    EndActionPhaseMessage()
        : GameMessage{ MessageType::MsgEndActionPhase } {
    }
};

struct EndProgressPhaseMessage : GameMessage {
    EndProgressPhaseMessage()
        : GameMessage{ MessageType::MsgEndProgressPhase } {
    }
};

struct EndActivateEventPhaseMessage : GameMessage {
    EndActivateEventPhaseMessage()
        : GameMessage{ MessageType::MsgEndActivateEventPhase } {
    }
};

struct EndAhievmentsPhaseMessage : GameMessage {
    EndAhievmentsPhaseMessage()
        : GameMessage{ MessageType::MsgEndAhievmentsPhase } {
    }
};

struct ThrowDiceMessage : GameMessage {
    ThrowDiceMessage(int playerId, int diceIndex)
        : GameMessage{ MessageType::MsgThrowDice } 
        , playerId{playerId}
        , diceIndex{ diceIndex }
    {
    }

    int playerId;
    int diceIndex;
};

struct DiceValueChangedMessage : GameMessage {
    DiceValueChangedMessage(int playerId, int diceIndex, int diceValue)
        :GameMessage{ MessageType::MsgDiceValueChanged }
        , playerId{ playerId }
        , diceIndex{ diceIndex }
        , diceValue{ diceValue } {
    }

    int playerId;
    int diceIndex;
    int diceValue;
};

struct ActionUnselectedMessage : GameMessage {
    ActionUnselectedMessage(int playerId, int index, ActionType action)
        :GameMessage{ MessageType::MsgActionUnselected}
        , playerId{ playerId }
        , index{ index }
        , action{ action } {
    }

    int playerId;
    int index;
    ActionType action;
};

struct ActionSelectedMessage : GameMessage {
    ActionSelectedMessage(int playerId, int index, ActionType action)
        :GameMessage{ MessageType::MsgActionSelected }
        , playerId{ playerId }
        , index{ index }
        , action{ action } {
    }

    int playerId;
    int index;
    ActionType action;
};

//struct BeginSelectActionsMessage : GameMessage {
//    BeginSelectActionsMessage(bool allowMilitary)
//        : GameMessage(MessageType::MsgBeginSelectActions)
//		, allowMilitary{ allowMilitary }
//    {
//    }
//
//	bool allowMilitary;
//};

struct OpenSelectedActionsMessage : GameMessage {
    OpenSelectedActionsMessage()
        : GameMessage(MessageType::MsgOpenSelectedActions) {
    }
};

struct ExecuteActionMessage : GameMessage {
    ExecuteActionMessage(int playerId, int diceValue, ActionType action)
        : GameMessage{ MessageType::MsgExecuteAction }
        , playerId{playerId}
        , diceValue{diceValue}
        , action{action}{}

    int playerId;
    int diceValue;
    ActionType action;
};

struct SelectLawPolicyMessage : GameMessage {
    SelectLawPolicyMessage(int playerId, Policies a, Policies b)
        : GameMessage{ MessageType::MsgSelectLawPolicy }
        , playerId{ playerId }
        , policyA{ a }
        , policyB{ b } {
    }

    int playerId;
    Policies policyA;
    Policies policyB;
};

struct SelectExpeditionMessage : GameMessage {
    SelectExpeditionMessage(int playerId)
        : GameMessage{ MessageType::MsgSelectExpedition } 
        , playerId{playerId} 
    {
    }

    int playerId;
};

struct SelectPolicyFromHandsMessage : GameMessage {
	SelectPolicyFromHandsMessage(int playerId, PolicySelectionReasonType reason)
		: GameMessage{ MessageType::MsgSelectPolicy }
		, playerId{ playerId }
		, reason{ reason }
	{
	}

	int playerId;
	PolicySelectionReasonType reason;
};

struct SelectDiscoveryFromPoolMessage : GameMessage {
	SelectDiscoveryFromPoolMessage(int playerId)
		: GameMessage{ MessageType::MsgSelectDiscovery } 
		, playerId{playerId}
	{

	}

	int playerId;
};

//struct BeginDropDiscoveryMessage : GameMessage {
//    BeginDropDiscoveryMessage(int playerId)
//        : GameMessage{ MessageType::MsgBeginDropDiscovery }
//        , playerId{ playerId } {
//
//    }
//
//    int playerId;
//};

//struct BeginDropPolicyMessage : GameMessage {
//    BeginDropPolicyMessage(int playerId)
//        : GameMessage{ MessageType::MsgBeginDropPolicy }
//        , playerId{ playerId } {
//
//    }
//
//    int playerId;
//};

struct SelectActionMessage : GameMessage {
	SelectActionMessage(int playerId, int diceValue, bool allowMilitary)
		: GameMessage{ MessageType::MsgSelectionActions } 
		, playerId{ playerId }
		, allowMilitary{ allowMilitary }
		, diceValue{ diceValue }
	{
	}

	int playerId;
	bool allowMilitary;
	int diceValue;
};

struct SelectPolicyFromActiveDeckMessage : GameMessage {
	SelectPolicyFromActiveDeckMessage(int playerId)
		: GameMessage{ MessageType::MsgSelectPolicyFromActiveDeck }
		, playerId{ playerId } {
	}

	int playerId;
};

struct SelectBonusMessage : GameMessage {
	SelectBonusMessage(int playerId, int army, int money, int points, int population)
		: GameMessage{ MessageType::MsgSelectBonus }
		, playerId{ playerId }
		, army{ army }
		, money{ money }
		, points{ points }
		, population{ population } {
	}

	int playerId;
	int army;
	int money;
	int points;
	int population;
};

struct SelectDiscoveryFromHandsMessage : GameMessage {
	SelectDiscoveryFromHandsMessage(int playerId)
		: GameMessage{ MessageType::MsgSelectDiscoveryFromHands } 
		, playerId{playerId}
	{
	}

	int playerId;
};