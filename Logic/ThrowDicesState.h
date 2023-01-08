#pragma once

#include <array>
#include <Logic/ComplexState.h>

class ThrowDicesState : public ComplexState {
public:
    ThrowDicesState(WorldLogic& logic);

private:
    WorldState _throwDices;
    WorldState _identifyOrder;
    WorldState _applyThrowDiceEventsPerks;
    WorldState _selectActions;
    WorldState _openActions;
};