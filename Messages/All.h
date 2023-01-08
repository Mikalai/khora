#pragma once

#include <functional>
#include <cassert>
#include <Log/Log.h>
#include <Messages/MoneyChangedMessage.h>
#include <Messages/TaxChangedMessage.h>

template<MessageType V>
struct To {   
};

template<> struct To<MessageType::MsgMoneyChanged> { using Type = MoneyChangedMessage; };
template<> struct To<MessageType::MsgPopulationChanged> { using Type = PopulationChangedMessage; };
template<> struct To<MessageType::MsgTaxChanged> { using Type = TaxChangedMessage; };
template<> struct To<MessageType::MsgEconomyChanged> { using Type = EconomyChangedMessage; };
template<> struct To<MessageType::MsgCultureChanged> { using Type = CultureChangedMessage; };
template<> struct To<MessageType::MsgMilitaryChanged> { using Type = MilitaryChangedMessage; };
template<> struct To<MessageType::MsgCityLevelChanged> { using Type = CityLevelChangedMessage; };
template<> struct To<MessageType::MsgPhilosophyAdded> { using Type = PhilosophyAddedMessage; };
template<> struct To<MessageType::MsgPhilosophyRemoved> { using Type = PhilosophyRemovedMessage; };
template<> struct To<MessageType::MsgScorePointsChanged> { using Type = ScorePointsChangedMessage; };
template<> struct To<MessageType::MsgArmyChanged> { using Type = ArmyChangedMessage; };
template<> struct To<MessageType::MsgGloryChanged> { using Type = GloryChangedMessage; };
template<> struct To<MessageType::MsgDiscoveryAdded> { using Type = DiscoveryAddedMessage; };
template<> struct To<MessageType::MsgDiscoveryRemoved> { using Type = DiscoveryRemovedMessage; };
template<> struct To<MessageType::MsgExpeditionCompleted> { using Type = ExpeditionCompletedMessage; };
template<> struct To<MessageType::MsgDiceUnlocked> { using Type = DiceUnlockedMessage; };
template<> struct To<MessageType::MsgPolicyDropped> { using Type = PolicyDroppedMessage; };
template<> struct To<MessageType::MsgDiscoveryDropped> { using Type = DiscoveryDroppedMessage; };
template<> struct To<MessageType::MsgPolicyTakenInHands> { using Type = PolicyAddedInHandsMessage; };
template<> struct To<MessageType::MsgDraftComplete> { using Type = DraftCompletedMessage; };
template<> struct To<MessageType::MsgPolicyTakenFromDeck> { using Type = PolicyTakenFromDeckMessage; };
template<> struct To<MessageType::MsgPlayerCountSelected> { using Type = PlayerCountSelectedMessage; };
template<> struct To<MessageType::MsgCitySelected> { using Type = CitySelectedMessage; };
template<> struct To<MessageType::MsgPlayerColorSelected> { using Type = PlayerColorSelectedMessage; };
template<> struct To<MessageType::MsgPoliciesShuffled> { using Type = PoliciesShuffledMessage; };
template<> struct To<MessageType::MsgPolicyTakenInHandsToDeck> { using Type = PolicyAddedToDeckMessage; };
template<> struct To<MessageType::MsgEventsShuffled> { using Type = EventsShuffledMessage; };
template<> struct To<MessageType::MsgEventAddedToDeck> { using Type = EventAddedToDeckMessage; };
template<> struct To<MessageType::MsgPolicyActivated> { using Type = PolicyActivatedMessage; };
template<> struct To<MessageType::MsgBeginCitySelection> { using Type = BeginCitySelectionMessage; };
template<> struct To<MessageType::MsgEndCitySelection> { using Type = EndCitySelectionMessage; };
template<> struct To<MessageType::MsgBeginSelectPlayersCount> { using Type = BeginSelectPlayersCountMessage; };
template<> struct To<MessageType::MsgPolicyRemovedFromDraft> { using Type = PolicyRemovedFromDraftMessage; };
template<> struct To<MessageType::MsgPolicyAddedToDraft> { using Type = PolicyAddedToDraftMessage; };
template<> struct To<MessageType::MsgPolicyRemovedFromHands> { using Type = PolicyRemovedFromHandsMessage; };
template<> struct To<MessageType::MsgEventTakenFromDeck > { using Type = EventTakenFromDeckMessage; };
template<> struct To<MessageType::MsgBeginSelectCityColor > { using Type = BeginSelectCityColorMessage; };
template<> struct To<MessageType::MsgBeginDraft > { using Type = BeginDraftMessage; };
template<> struct To<MessageType::MsgAddMoney > { using Type = AddMoneyMessage; };
template<> struct To<MessageType::MsgRemoveMoney > { using Type = RemoveMoneyMessage; };
template<> struct To<MessageType::MsgExpeditionAdded> { using Type = ExpeditionAddedMessage; };
template<> struct To<MessageType::MsgBeginDeclareEventPhase> { using Type = BeginDeclareEventPhaseMessage; };
template<> struct To<MessageType::MsgBeginCollectTaxesPhase> { using Type = BeginCollectTaxesPhaseMessage; };
template<> struct To<MessageType::MsgBeginThrowDicesPhase> { using Type = BeginThrowDicesPhaseMessage; };
template<> struct To<MessageType::MsgBeginActionPhase> { using Type = BeginActionPhaseMessage; };
template<> struct To<MessageType::MsgBeginProgress> { using Type = BeginProgressMessage; };
template<> struct To<MessageType::MsgBeginActivateEventPhase> { using Type = BeginActivateEventPhaseMessage; };
template<> struct To<MessageType::MsgBeginAhievmentsPhase> { using Type = BeginAhievmentsPhaseMessage; };
template<> struct To<MessageType::MsgEndDeclareEventPhase> { using Type = EndDeclareEventPhaseMessage; };
template<> struct To<MessageType::MsgEndCollectTaxesPhase> { using Type = EndCollectTaxesPhaseMessage; };
template<> struct To<MessageType::MsgEndThrowDicesPhase> { using Type = EndThrowDicesPhaseMessage; };
template<> struct To<MessageType::MsgEndActionPhase> { using Type = EndActionPhaseMessage; };
template<> struct To<MessageType::MsgEndProgressPhase> { using Type = EndProgressPhaseMessage; };
template<> struct To<MessageType::MsgEndActivateEventPhase> { using Type = EndActivateEventPhaseMessage; };
template<> struct To<MessageType::MsgEndAhievmentsPhase> { using Type = EndAhievmentsPhaseMessage; };
template<> struct To<MessageType::MsgEventAddedToOpenDeck> { using Type = EventAddedToOpenDeckMessage; }; 
template<> struct To<MessageType::MsgThrowDice> { using Type = ThrowDiceMessage; };
template<> struct To<MessageType::MsgDiceValueChanged> { using Type = DiceValueChangedMessage; };
template<> struct To<MessageType::MsgActionUnselected> { using Type = ActionUnselectedMessage; };
template<> struct To<MessageType::MsgActionSelected> { using Type = ActionSelectedMessage; };
//template<> struct To<MessageType::MsgBeginSelectActions> { using Type = BeginSelectActionsMessage; };
template<> struct To<MessageType::MsgOpenSelectedActions> { using Type = OpenSelectedActionsMessage; };
template<> struct To<MessageType::MsgExecuteAction> { using Type = ExecuteActionMessage; };
template<> struct To<MessageType::MsgSelectLawPolicy> { using Type = SelectLawPolicyMessage; };
template<> struct To<MessageType::MsgSelectExpedition> { using Type = SelectExpeditionMessage; };
template<> struct To<MessageType::MsgBeginExtraProgress> { using Type = BeginExtraProgressMessage; };
template<> struct To<MessageType::MsgSelectPolicy> { using Type = SelectPolicyFromHandsMessage; };
template<> struct To<MessageType::MsgPolicyAddedToPlayed> { using Type = PolicyAddedToPlayedMessage; };
//template<> struct To<MessageType::MsgBeginDropDiscovery> { using Type = BeginDropDiscoveryMessage; };
//template<> struct To<MessageType::MsgBeginDropPolicy> { using Type = BeginDropPolicyMessage; };
template<> struct To<MessageType::MsgSelectDiscovery> { using Type = SelectDiscoveryFromPoolMessage; };
template<> struct To<MessageType::MsgSelectionActions> { using Type = SelectActionMessage; };
template<> struct To<MessageType::MsgSelectPolicyFromActiveDeck> { using Type = SelectPolicyFromActiveDeckMessage; };
template<> struct To<MessageType::MsgSelectBonus> { using Type = SelectBonusMessage; };
template<> struct To<MessageType::MsgSelectDiscoveryFromHands> { using Type = SelectDiscoveryFromHandsMessage; };


template<MessageType V>
using ToType = typename To<V>::Type;

template<typename T, MessageType ... V>
struct MessageMapping;

template<typename T, MessageType H, MessageType ... V>
struct MessageMapping<T, H, V...> : MessageMapping<T, V...> {
    
    using MessageMapping<T, V...>::On;

    void On(std::function<void(T& self, ToType<H>& msg)> action) {
        static_assert(std::is_same_v<decltype(action), decltype(_action)>);
        _action = action;
    }

    void Process(T& self, GameMessage& msg) {
        if (msg.Type == H) {
            if (_action) {
                this->_action(self, static_cast<ToType<H>&>(msg));
            }
        }
        else {
            MessageMapping<T, V...>::Process(self, msg);
        }
    }

private:
    std::function<void(T& self, ToType<H>& msg)> _action;
};

template<typename T, MessageType H>
struct MessageMapping<T, H> : MessageMapping<T> {

    void On(std::function<void(T& self, ToType<H>& msg)> action) {
        _action = action;
    }

    void Process(T& self, GameMessage& msg) {
        if (msg.Type == H) {
            if (_action) {
                this->_action(self, static_cast<ToType<H>&>(msg));
            }
        }
        else {
            MessageMapping<T>::Process(self, msg);
        }
    }

private:
    std::function<void(T& self, ToType<H>& msg)> _action;
};

template<typename T>
struct MessageMapping<T> {
    void Process(T& self, GameMessage& msg) {
        ERROR("Can't process {}", ToString(msg.Type));
        assert(false);
    }    
};
