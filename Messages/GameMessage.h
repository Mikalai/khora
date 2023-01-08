#pragma once

#include <Messages/MessageType.h>

struct GameMessage {

    GameMessage(MessageType type)
        : Type{ type } {
    }

    MessageType Type;
};
