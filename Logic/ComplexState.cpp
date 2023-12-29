#include "ComplexState.h"

#include <cassert>

ComplexState::ComplexState(WorldLogic& logic)
    : WorldState{logic}, first{logic}, last{logic} {
    current = &first;
}

WorldState* ComplexState::Update() {
    current = current->Update();

    if (current == nullptr) {
        for (auto& transition : transition_table) {
            if (transition.predicate(_logic)) {
                _exit(_logic);
                transition.next->_enter(_logic);
                return transition.next;
            }
        }

        assert(current != nullptr);
        return current;
    } else {
        return this;
    }
}

void ComplexState::Transition(std::function<bool(const WorldLogic&)> predicate,
                              WorldState* next) {
    last.Transition(predicate, next);
}

void ComplexState::Enter() {
    WorldState::Enter();
    current->Enter();
}

void ComplexState::Reset() { current = &first; }
