#pragma once

#include <string>

enum class MessageType {
    MsgMoneyChanged,
    MsgPopulationChanged,
    MsgTaxChanged,
    MsgEconomyChanged,
    MsgCultureChanged,
    MsgMilitaryChanged,
    MsgCityLevelChanged,
    MsgPhilosophyAdded,
    MsgScorePointsChanged,
    MsgArmyChanged,
    MsgGloryChanged,
    MsgDiscoveryAdded,
    MsgDiscoveryRemoved,
    MsgExpeditionCompleted,
    MsgDiceUnlocked,
    MsgPolicyDropped,
    MsgDiscoveryDropped,
    MsgPolicyTakenInHands,
    MsgDraftComplete,
    MsgPolicyTakenFromDeck,
    MsgPlayerCountSelected,
    MsgCitySelected,
    MsgPlayerColorSelected,
    MsgPoliciesShuffled,
    MsgPolicyTakenInHandsToDeck,
    MsgEventsShuffled,
    MsgEventAddedToDeck,
    MsgEventTakenFromDeck,
    MsgPolicyActivated,
    MsgPolicyRemovedFromHands,
    MsgPolicyAddedToDraft,
    MsgPolicyRemovedFromDraft,
    MsgBeginCitySelection,
    MsgEndCitySelection,
    MsgBeginSelectPlayersCount,
    MsgBeginSelectCityColor,
    MsgBeginDraft,
    MsgAddMoney,
    MsgRemoveMoney,
    MsgExpeditionAdded,
    MsgBeginDeclareEventPhase,
    MsgBeginCollectTaxesPhase,
    MsgBeginThrowDicesPhase,
    MsgBeginActionPhase,
    MsgBeginProgress,
    MsgBeginActivateEventPhase,
    MsgBeginAhievmentsPhase,
    MsgEndDeclareEventPhase,
    MsgEndCollectTaxesPhase,
    MsgEndThrowDicesPhase,
    MsgEndActionPhase,
    MsgEndProgressPhase,
    MsgEndActivateEventPhase,
    MsgEndAhievmentsPhase,
    MsgEventAddedToOpenDeck,
    MsgThrowDice,
    MsgDiceValueChanged,
    MsgActionUnselected,
    MsgActionSelected,
    MsgPhilosophyRemoved,
    MsgOpenSelectedActions,
    MsgExecuteAction,
    MsgSelectLawPolicy,
    MsgSelectExpedition,
	MsgBeginExtraProgress,
	MsgSelectPolicy,
    MsgPolicyAddedToPlayed,
	MsgSelectDiscovery,
	MsgSelectionActions,
	MsgSelectPolicyFromActiveDeck,
	MsgSelectBonus,
	MsgSelectDiscoveryFromHands,
    End,
    Count = End
};

#define ALL_MESSAGES     MessageType::MsgMoneyChanged, \
MessageType::MsgPopulationChanged,\
MessageType::MsgTaxChanged,\
MessageType::MsgEconomyChanged,\
MessageType::MsgCultureChanged,\
MessageType::MsgMilitaryChanged,\
MessageType::MsgCityLevelChanged,\
MessageType::MsgPhilosophyAdded,\
MessageType::MsgScorePointsChanged,\
MessageType::MsgArmyChanged,\
MessageType::MsgGloryChanged,\
MessageType::MsgDiscoveryAdded,\
MessageType::MsgDiscoveryRemoved,\
MessageType::MsgExpeditionCompleted,\
MessageType::MsgDiceUnlocked,\
MessageType::MsgPolicyDropped,\
MessageType::MsgDiscoveryDropped,\
MessageType::MsgPolicyTakenInHands,\
MessageType::MsgDraftComplete,\
MessageType::MsgPolicyTakenFromDeck,\
MessageType::MsgPlayerCountSelected,\
MessageType::MsgCitySelected,\
MessageType::MsgPlayerColorSelected,\
MessageType::MsgPoliciesShuffled,\
MessageType::MsgPolicyTakenInHandsToDeck,\
MessageType::MsgEventsShuffled,\
MessageType::MsgEventAddedToDeck,\
MessageType::MsgEventTakenFromDeck,\
MessageType::MsgPolicyActivated,\
MessageType::MsgPolicyRemovedFromHands,\
MessageType::MsgPolicyAddedToDraft,\
MessageType::MsgPolicyRemovedFromDraft,\
MessageType::MsgBeginCitySelection,\
MessageType::MsgEndCitySelection,\
MessageType::MsgBeginSelectPlayersCount,\
MessageType::MsgBeginSelectCityColor,\
MessageType::MsgAddMoney,\
MessageType::MsgRemoveMoney,\
MessageType::MsgExpeditionAdded,\
MessageType::MsgBeginDraft,\
MessageType::MsgBeginDeclareEventPhase,\
MessageType::MsgBeginCollectTaxesPhase,\
MessageType::MsgBeginThrowDicesPhase,\
MessageType::MsgBeginActionPhase,\
MessageType::MsgBeginProgress,\
MessageType::MsgBeginActivateEventPhase,\
MessageType::MsgBeginAhievmentsPhase,\
MessageType::MsgEndDeclareEventPhase,\
MessageType::MsgEndCollectTaxesPhase,\
MessageType::MsgEndThrowDicesPhase,\
MessageType::MsgEndActionPhase,\
MessageType::MsgEndProgressPhase,\
MessageType::MsgEndActivateEventPhase,\
MessageType::MsgEndAhievmentsPhase, \
MessageType::MsgEventAddedToOpenDeck, \
MessageType::MsgThrowDice, \
MessageType::MsgDiceValueChanged, \
MessageType::MsgActionUnselected,\
MessageType::MsgActionSelected, \
MessageType::MsgPhilosophyRemoved, \
MessageType::MsgOpenSelectedActions, \
MessageType::MsgExecuteAction, \
MessageType::MsgSelectLawPolicy, \
MessageType::MsgSelectExpedition,\
MessageType::MsgBeginExtraProgress,\
MessageType::MsgSelectPolicy,\
MessageType::MsgPolicyAddedToPlayed,\
MessageType::MsgSelectDiscovery,\
MessageType::MsgSelectionActions,\
MessageType::MsgSelectPolicyFromActiveDeck,\
MessageType::MsgSelectBonus, \
MessageType::MsgSelectDiscoveryFromHands \

const std::string& ToString(MessageType type);
