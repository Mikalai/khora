#pragma once

#include <cassert>
#include <UI/UI.h>
#include <Log/Log.h>
#include <Locale/Translate.h>
#include <WorldLogic.h>
#include <WorldLogicRound.h>
#include "GeneralUserInput.h"
#include "IUserInputIdleMarker.h"

GeneralUserInput::GeneralUserInput(int playerId, WorldLogic& world)
	: _world{ world }
	, _playerId{ playerId } {

	///*Map().On([](GeneralUserInput& self, BeginSelectPlayersCountMessage& msg) {
	//	self.SelectPlayersCountAsync([&self](int count) {
	//		self.PostWorldUpdateAction([count](WorldLogic& logic) {
	//			logic.SetPlayersCount(count);
	//			});
	//		});
	//	});*/

	//Map().On([](GeneralUserInput& self, BeginSelectCityColorMessage& msg) {
	//	/*self.SelectCityColorAsync([&self](player_color color) {
	//		self.PostWorldUpdateAction([&self, color](WorldLogic& logic) {
	//			logic.SetPlayerColor(self.PlayerId(), color);
	//			});
	//		});*/
	//	});

	//Map().On([](GeneralUserInput& self, BeginCitySelectionMessage& msg) {
	//	self.SelectCityAsync([&self](Cities city) {
	//		self.PostWorldUpdateAction([&self, city](WorldLogic& logic) {
	//			logic.SetPlayerCity(self.PlayerId(), city);
	//			});
	//		});
	//	});

	//Map().On([](GeneralUserInput& self, BeginDraftMessage& msg) {
	//	self.SelectPolicyFromDraftAsync([&self](Policies policy) {
	//		self.PostWorldUpdateAction([&self, policy](WorldLogic& logic) {
	//			logic.GetPlayer(self.PlayerId()).Draft().Take(policy);
	//			});
	//		});
	//	});

	//Map().On([](GeneralUserInput& self, ThrowDiceMessage& msg) {
	//	self.ThrowDiceAsync(msg.diceIndex, [&self](int diceIndex, int diceValue) {
	//		self.PostWorldUpdateAction([&self, diceIndex, diceValue](WorldLogic& logic) {
	//			logic.GetPlayer(self.PlayerId()).SetDiceValue(diceIndex, diceValue);
	//			});
	//		});
	//	});

	/*Map().On([](GeneralUserInput& self, BeginSelectActionsMessage& msg) {
		self.SelectActionAsync([&self](int index, ActionType action) {
			self.PostWorldUpdateAction([&self, index, action](WorldLogic& logic) {
				logic.GetPlayer(self.PlayerId()).SetAction(index, action);
				});
			});
		});*/
}

GeneralUserInput::~GeneralUserInput() {

}

void GeneralUserInput::SetPlayersCount(int value) {
    _world.SetPlayersCount(value);
}

void GeneralUserInput::SetPlayerColor(player_color color) {
    _world.SetPlayerColor(PlayerId(), color);
}

void GeneralUserInput::SetPlayerCity(Cities city) {
    _world.SetPlayerCity(PlayerId(), city);
}

player_color GeneralUserInput::GetColor(const std::string& value) {
    if (value == tr("red"))
        return red;
    else if (value == tr("black"))
        return black;
    else if (value == tr("blue"))
        return blue;
    else if (value == tr("green"))
        return green;
    return red;
}

Cities GeneralUserInput::GetCity(const std::string& value) {
    if (value == tr("Miles"))
        return city_milet;
    else if (value == tr("Thebes"))
        return city_thebes;
    else if (value == tr("Athens"))
        return city_athens;
    else if (value == tr("Sparta"))
        return city_sparta;
    else if (value == tr("Argos"))
        return city_argos;
    else if (value == tr("Olympia"))
        return city_olymp;
    else if (value == tr("Corinth"))
        return city_corinth;
    return city_milet;
}

void GeneralUserInput::AdvanceEconomyForFree() {
    _world.GetPlayer(PlayerId()).AddEconomyLevel(1);
}

void GeneralUserInput::AdvanceCultureForFree() {
    _world.GetPlayer(PlayerId()).AddCulture(1);
}

void GeneralUserInput::AdvanceMilitaryForFree() {
    _world.GetPlayer(PlayerId()).AddMilitaryLevel(1);
}

const PlayerLogic& GeneralUserInput::GetPlayer() const {
	return _world.GetPlayer(PlayerId());
}

void GeneralUserInput::ActivateThebesLevel2Perk() {
	auto& player = _world.GetPlayer(PlayerId());
	assert(player.GetGlory() != 0);
	player.RemoveGlory(1);
	player.AddMoney(2);
	player.AddPoints(4);
}

void GeneralUserInput::ActivateArgosLevel2Perk(int code) {
	auto& player = _world.GetPlayer(PlayerId());
	switch (code)
	{
	case 1:
		player.AddArmy(2, false);
		break;
	case 2:
		player.AddMoney(3);
		break;
	case 3:
		player.AddPoints(4);
		break;
	case 4:
		player.AddPopulation(5);
		break;
	default:
		break;
	}

}

const WorldLogic& GeneralUserInput::GetWorld() const {
	return _world;
}

//void GeneralUserInput::ActivateExpedition(int expeditionId, SelectExpeditionCallback cb) {
//	auto& player = _world.GetPlayer(PlayerId());
//    cb(player, expeditionId);
//}

//void GeneralUserInput::DoTrackAdvance(ProgressTrackType type, int discont) {
//    auto& player = _world.GetPlayer(PlayerId());
//    assert(player.CanUpgradeTrack(type, discont));
//    player.UpgradeTrack(type, discont);
//}

void GeneralUserInput::DoDropPolicies(int count) {
    auto& player = _world.GetPlayer(PlayerId());
    assert(player.GetPoliciesInHandCount() <= count);
    while (player.GetPoliciesInHandCount()) {
        player.DropPolicy(0);
    }
}

//void GeneralUserInput::DoDropDiscovery(discovery_type discovery) {
//    auto& player = _world.GetPlayer(PlayerId());
//    assert(std::find(player.GetDiscoveries().begin(), player.GetDiscoveries().end(), discovery) != player.GetDiscoveries().end());
//    player.DropDiscovery(discovery);
//}

//void GeneralUserInput::DoPersiaCampaign() {
//    if (!_world.IsPersipolisTaken())
//        return;
//
//
//}

void GeneralUserInput::ExecuteActionAsync(ActionType action, std::function<void()> cb) {
	assert(action != ActionType::Unknown);

	INFO("GeneralUserInput[{}]: ExecuteActionAsync {}", PlayerId(), ActionToString[As<int>(action)]);

	switch (action)
	{
	case ActionType::Philosophy:
		PostWorldUpdateAction([this, cb](WorldLogic& world) {
			world.GetPlayer(PlayerId()).DoPhilosophy(cb);
			});
		break;
	case ActionType::Law:
		PostWorldUpdateAction([this, cb](WorldLogic& world) {
			world.GetPlayer(PlayerId()).BeginDoLaw(cb);
			});
		break;
	case ActionType::Culture:
		PostWorldUpdateAction([this, cb](WorldLogic& world) {
			world.GetPlayer(PlayerId()).DoCulture(cb);			
			});
		break;
	case ActionType::Trade:
		PostWorldUpdateAction([this, cb](WorldLogic& world) {
			world.GetPlayer(PlayerId()).DoTrade(cb);
			});
		break;
	case ActionType::Military:
		PostWorldUpdateAction([this, cb](WorldLogic& world) {
			world.GetPlayer(PlayerId()).BeginDoMilitary(cb);
			});
		break;
	case ActionType::Policy:
		PostWorldUpdateAction([this, cb](WorldLogic& world) {
            world.GetPlayer(PlayerId()).BeginSelectPolicyFromHandsToActivate([this, cb, &world](PoliciesType policy) {
				auto& p = world.GetPlayer(PlayerId());
				if (p.CanActivatePolicy(policy)) {
					p.ActivatePolicy(policy);
					cb();
				}
				else {
					WARN("Player {} can't activate policy {}. Submit another request.", PlayerId(), (int)policy);
					PostWorldUpdateAction([this](WorldLogic& world) {
						SelectPolicyFromHandsMessage msg{ PlayerId(), PolicySelectionReasonType::Activate };
						auto v = msg;
						world.Notify(v);
					});
				}
			});
		});
		break;
	case ActionType::Development:
		PostWorldUpdateAction([this, cb](WorldLogic& world) {
			world.GetPlayer(PlayerId()).DoExpand(cb);
			});
		break;
	default:
		assert(false && "Unexpected action type");
	}

}

//
//void GeneralUserInput::DoPhilosophyAction() {
//    auto& player = _world.GetPlayer(PlayerId());
//    player.DoPhilosophy();
//}
//
//void GeneralUserInput::DoLawAction() {    
//    auto& player = _world.GetPlayer(PlayerId());        
//    player.DoLaw();
//}
//
//void GeneralUserInput::DoCultureAction() {
//    auto& player = _world.GetPlayer(PlayerId());
//    player.DoCulture();
//}
//
//void GeneralUserInput::DoTradeAction() {
//    auto& player = _world.GetPlayer(PlayerId());
//    player.DoTrade();
//}
//
//void GeneralUserInput::DoMilitaryAction() {
//
//}
//
//void GeneralUserInput::DoPolicyAction() {
//
//}
//
//void GeneralUserInput::DoExpandAction() {
//
//}
//
//void GeneralUserInput::DoAnyActionExceptMilitary() {
//
//}

//void GeneralUserInput::ActivatePolicy(Policies* policy, int count, int selected, SelectPolicyCallback cb) {
//    auto& player = _world.GetPlayer(PlayerId());
//    cb(player, policy, count, selected);
//}

bool GeneralUserInput::IsIdle() const {
	if (!std::all_of(_idleMarkers.begin(), _idleMarkers.end(), [](auto& v) {
		return v->IsIdle();
		})) {
		return false;
	}

	{
		SpinLockScope scope{ _lock };
		return _updateCbs[Front].empty() && _updateCbs[Back].empty();
	}
}

void GeneralUserInput::AddIdleMarker(std::unique_ptr<IUserInputIdleMarker>&& marker) {
	_idleMarkers.push_back(std::move(marker));
}

void GeneralUserInput::PostWorldUpdateAction(UpdateCallback action) {
	SpinLockScope scop{ _lock };
	_updateCbs[Back].push_back(action);
}

void GeneralUserInput::Update(WorldLogic& world) {
	
	{
		SpinLockScope scop{ _lock };
		std::swap(_updateCbs[Back], _updateCbs[Front]);
	}

	for (auto& c : _updateCbs[Front]) {
		c(world);
	}

	_updateCbs[Front].clear();
}

//void GeneralUserInput::Next(GameMessage& msg) {
//	Map().Process(*this, msg);
//}

//void GeneralUserInput::Complete() {
//
//}

int GeneralUserInput::NextRandomDiceValue()
{
	return diceDist(rng);
}
