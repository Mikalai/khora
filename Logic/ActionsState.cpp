#pragma once

#include <array>
#include <Logic/ComplexState.h>
#include <Logic/ThrowDicesState.h>

class RoundState : public ComplexState {
public:
    RoundState(WorldLogic& logic);    

private:

    WorldState _declareEventState;
    WorldState _collectTaxState;
    ThrowDicesState _throwDicesState;
    WorldState _actionState;
    WorldState _progressState;
    WorldState _activateEventState;
    WorldState _achieveState;

};