#pragma once

#include <array>
#include <Logic/ComplexState.h>

class ActionState : public ComplexState {
public:
    RoundState(WorldLogic& logic);    

private:

    WorldState _declareEventState;
    WorldState _collectTaxState;
    WorldState _actionState;
    WorldState _progressState;
    WorldState _activateEventState;
    WorldState _achieveState;

};