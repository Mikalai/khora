#pragma once

#include <Logic/WorldState.h>
#include <Logic/WorldDraftState.h>

class WorldInitState : public ComplexState {
public:

    WorldInitState(WorldLogic& logic);
    //WorldState* Update() override;
    //void Transition(std::function<bool(const WorldLogic&)> predicate, WorldState* next) override;
	void Reset() override;

    WorldState state_add_expeditions;
    WorldState state_select_players_count;
    WorldState state_select_color;
    WorldState state_shuffle_policies;
    WorldState state_shuffle_events;
    WorldState state_select_city;
    WorldState state_give_policies;
    WorldDraftState state_draft_policies;
    WorldState state_give_startup_money;
    WorldState state_set_players_levels;
    WorldState state_advance_city_to_first_level;
    WorldState state_give_initial_money;
};
