#include <cassert>
#include <WorldLogic.h>
#include <Log/Log.h>
#include <UI/UI.h>
#include <WorldLogicPrepare.h>
#include "WorldInitState.h"

WorldInitState::WorldInitState(WorldLogic& logic)
	: ComplexState(logic)
	, state_add_expeditions(logic)
	, state_select_players_count(logic)
	, state_select_color(logic)
	, state_select_city(logic)
	, state_shuffle_policies(logic)
	, state_shuffle_events(logic)
	, state_give_policies(logic)
	, state_draft_policies(logic)
	, state_give_startup_money(logic)
	, state_set_players_levels(logic)
	, state_advance_city_to_first_level(logic)
	, state_give_initial_money(logic)
{
	first.Transition([](const WorldLogic& world) { return true; }, &state_add_expeditions);

	state_add_expeditions.Transition([](const WorldLogic& world) {
		return ui().IsIdle();
		}, &state_select_players_count);

	state_add_expeditions.SetEnter([](WorldLogic& world) {
		world.Prepare().CreateExpeditions();
		});

	state_select_players_count.Transition([](const WorldLogic& world) {
		return world.GetPlayersCount() >= 2 && world.GetPlayersCount() <= 4 && ui().IsIdle();
		}, &state_select_color);

	state_select_players_count.SetEnter([](WorldLogic& world) {
		world.Prepare().SelectPlayersCount();
		});

	state_select_color.Transition([](const WorldLogic& world) {
		return world.AllColorsUnique() && ui().IsIdle();
		}, &state_select_city);

	state_select_color.SetEnter([](WorldLogic& world) {
		world.Prepare().SelectCityColor();
		});

	state_select_city.Transition([](const WorldLogic& world) {
		return world.AllCitiesUnique() && ui().IsIdle();
		}, &state_shuffle_policies);

	state_select_city.SetEnter([](WorldLogic& world) {		
		world.Prepare().SelectCities();
		});

	state_shuffle_policies.Transition([](const WorldLogic& world) {
		return true;
		}, &state_shuffle_events);

	state_shuffle_policies.SetEnter([](WorldLogic& world) {
		world.Prepare().ShufflePolicies();
		});

	state_shuffle_events.Transition([](const WorldLogic& logic) {
		return ui().IsIdle();
		}, &state_give_policies);

	state_shuffle_events.SetEnter([](WorldLogic& world) {
		world.Prepare().ShuffleEvents();
		});
		
	state_give_policies.Transition([](const WorldLogic& world) {
		return ui().IsIdle();
		}, &state_draft_policies);

	state_give_policies.SetEnter([](WorldLogic& world) {
		INFO("=== ENTER GIVE POLICIES ===");
		world.Prepare().GivePolicies();
		});

	state_give_policies.SetExit([](WorldLogic& world) {
		INFO("=== EXIT GIVE POLICIES ===");
        assert(world.GetPlayers().All([](const PlayerLogic& player) { return player.GetPoliciesInHandCount() == 5; }));
		});

	state_draft_policies.SetEnter([](WorldLogic& world) {
		INFO("=== ENTER DRAFT POLICIES ===");
		});

	state_draft_policies.SetExit([](WorldLogic& world) {
		INFO("=== EXIT DRAFT POLICIES ===");
		});

	state_draft_policies.Transition([](const WorldLogic& world) {
		return world.DraftComplete() && ui().IsIdle();
		}, & state_give_startup_money);

	state_give_startup_money.Transition([](const WorldLogic& world) {
		return ui().IsIdle();
		}, &state_set_players_levels);

	state_give_startup_money.SetEnter([](WorldLogic& world) {
        world.GetPlayers().ForEach([](PlayerLogic& player) {
			player.AddMoney(STARTUP_MONEY);
			});
		});

	state_set_players_levels.Transition([](const WorldLogic& world) {
		return ui().IsIdle();
		}, &state_advance_city_to_first_level);
		
	state_set_players_levels.SetEnter([](WorldLogic& world) {
        world.GetPlayers().ForEach([](PlayerLogic& player) {
			player.SetPoints(0);
			player.SetPopulation(3);
			player.SetTax(0);
			player.SetGlory(0);
			player.SetArmy(0, false);
			player.SetEconomy(0);
			player.SetCulture(0);
			player.SetMilitary(0);
			});
		});

	state_advance_city_to_first_level.Transition([](const WorldLogic& world) {
        return world.GetPlayers().All([](const PlayerLogic& player) {
			return player.IsIdle();
			}) && ui().IsIdle();
		}, &last);

	state_advance_city_to_first_level.SetEnter([](WorldLogic& world) {
		world.Prepare().UpgradeCitiesToFirstLevel();
		});	
}
//
//WorldState* WorldInitState::Update() {
//
//	if (!_started) {
//		_started = true;
//		current->Enter();
//	}
//
//	current = current->Update();
//
//	if (current == nullptr) {
//
//		for (auto& transition : transition_table) {
//			if (transition.predicate(_logic)) {
//				_exit(_logic);
//				transition.next->_enter(_logic);
//				return transition.next;
//			}
//		}
//
//		assert(current != nullptr);
//		return current;
//	}
//	else {
//		return this;
//	}
//}

//void WorldInitState::Transition(std::function<bool(const WorldLogic&)> predicate, WorldState* next) {
//	last.Transition(predicate, next);
//}

void WorldInitState::Reset() {
	ComplexState::Reset();
	state_draft_policies.Reset();
}
