#pragma once

#include <Messages/GameMessage.h>

struct MoneyChangedMessage : GameMessage {

    MoneyChangedMessage(int playerId, int money)
        : GameMessage(MessageType::MsgMoneyChanged)
        , player{ playerId }
        , money{ money }
    {}

    int player;
    int money;
};