#pragma once

#include <array>
#include <UI/UI.h>
#include <Log/Log.h>
#include <WorldLogic.h>
#include <PlayerLogic.h>

#include "World.h"

World::World(WorldLogic& logic)
	: state_init(logic)
	, state_game(logic)
	, state_caculate_scores(logic)
	, _logic{ logic }
{
	state_init.Transition([](auto&) { 
		return ui().IsIdle();
		}, &state_game);

	state_init.SetEnter([](WorldLogic& world) {
		INFO("**** BEGIN INIT GAME ****");
	});

	state_init.SetExit([](WorldLogic& world) {
		INFO("**** END INIT GAME ****");
	});

	state_game.SetEnter([](WorldLogic& world) {
		INFO("**** BEGIN PLAY GAME ****");
	});

	state_game.SetExit([](WorldLogic& world) {
		INFO("**** END PLAY GAME ****");
		});
	
	state_game.Transition([](const WorldLogic& world) {
		return ui().IsIdle() && world.Players().All([](const PlayerLogic& player) {
			return player.IsIdle();
			});
		}, &state_caculate_scores);	

	state_caculate_scores.SetEnter([this](WorldLogic& logic) {
		INFO("**** CALCULATE SCORE POINTS ****");
		logic.Players().ForEach([](PlayerLogic& player) {
			player.ExecuteEndGamePerks();
		});

		state_init.Reset();
		state_game.Reset();		
		_started = false;
		
		logic.EndGame();
	});

	state_caculate_scores.Transition([](const WorldLogic& world) {
		return ui().IsIdle() && world.Players().All([](const PlayerLogic& player) {
			return player.IsIdle();
			});
		}, &state_init);

	current = &state_init;
}

void World::Update() {
	if (!_started) {
		_started = true;
		current->Enter();
	}

	if (current) {
		current = current->Update();
	}
}

