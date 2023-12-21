#pragma once

#include <functional>
#include <Resources.h>
#include <PolicyTemplate.h>
#include "UserInputDispatcher.h"
#include <WorldLogic.h>

using UserInputDispatcherMapping = MessageMapping<UserInputDispatcher,
	ALL_MESSAGES>;

struct InitMapping {
	InitMapping(UserInputDispatcherMapping& m) {
		m.On([](UserInputDispatcher& self, BeginCitySelectionMessage& msg) {
			self.Handlers().ForEach([&msg](IUserInputHandler& h) {
				h.SelectCityAsync([&h](Cities city) {
					h.PostWorldUpdateAction([&h, city](WorldLogic& logic) {
						logic.SetPlayerCity(h.PlayerId(), city);
						});
					});
				});
			});

		m.On([](UserInputDispatcher& self, BeginSelectPlayersCountMessage& msg) {
			self.Handlers().ForEach([&msg](IUserInputHandler& h) {
				h.SelectPlayersCountAsync([&h](int count) {
					h.PostWorldUpdateAction([count](WorldLogic& logic) {
						logic.SetPlayersCount(count);
						});
					});
				});
			});

		m.On([](UserInputDispatcher& self, BeginSelectCityColorMessage& msg) {
			self.Handlers().ForEach([&msg](IUserInputHandler& h) {
				h.SelectCityColorAsync([&h](player_color color) {
					h.PostWorldUpdateAction([&h, color](WorldLogic& logic) {
						logic.SetPlayerColor(h.PlayerId(), color);
						});
					});
				});
			});

		/*	m.On([](UserInputDispatcher& self, BeginCitySelectionMessage& msg) {
				self.Handlers().ForEach([&msg](IUserInputHandler& h) {
					h.Next(msg);
					});
				});*/

		m.On([](UserInputDispatcher& self, PlayerCountSelectedMessage& msg) {
			self.SetPlayersCount(msg.playersCount);
			});

		m.On([](UserInputDispatcher& self, BeginDraftMessage& msg) {
			auto& h = self.Handlers().Select(msg.player);
            h.SelectPolicyFromDraftAsync([&h](PoliciesType policy) {
				h.PostWorldUpdateAction([&h, policy](WorldLogic& logic) {
					logic.GetPlayer(h.PlayerId()).Draft().Take(policy);
					});
				});
			});

		m.On([](UserInputDispatcher& self, ThrowDiceMessage& msg) {
			auto& h = self.Handlers().Select(msg.playerId);
			h.ThrowDiceAsync(msg.diceIndex, [&h](int diceIndex, int diceValue) {
				h.PostWorldUpdateAction([&h, diceIndex, diceValue](WorldLogic& logic) {
					logic.GetPlayer(h.PlayerId()).SetDiceValue(diceIndex, diceValue);
					});
				});
			});

		/*m.On([](UserInputDispatcher& self, BeginSelectActionsMessage& msg) {
			self.Handlers().ForEach([&msg](IUserInputHandler& h) {
				h.SelectActionAsync(msg.dices, [&h](int index, ActionType action) {
					h.PostWorldUpdateAction([&h, index, action](WorldLogic& logic) {
						logic.GetPlayer(h.PlayerId()).SetAction(index, action);
						});
					});
				});
			});*/

		m.On([](UserInputDispatcher& self, ExecuteActionMessage& msg) {
			auto& h = self.Handlers().Select(msg.playerId);
			h.ExecuteActionAsync(msg.action, [&h]() {
				h.PostWorldUpdateAction([&h](WorldLogic& world) {
					world.GetPlayer(h.PlayerId()).EndExecuteAction();
					});
				});
			});

		m.On([](UserInputDispatcher& self, SelectLawPolicyMessage& msg) {
			auto& h = self.Handlers().Select(msg.playerId);
            h.SelectLawPolicyAsync(msg.policyA, msg.policyB, [&h](PoliciesType selected, PoliciesType dropped) {
				h.PostWorldUpdateAction([&h, selected, dropped](WorldLogic& world) {
					INFO("Player {} selected policy {}, dropped policy {}", h.PlayerId(), GetPolicyTemplate(selected).GetName(), GetPolicyTemplate(dropped).GetName());
					PlayerLogic& p = world.GetPlayer(h.PlayerId());
					p.EndDoLaw(selected, dropped);
					});
				});
			});

		m.On([](UserInputDispatcher& self, SelectExpeditionMessage& msg) {
			auto& h = self.Handlers().Select(msg.playerId);
			h.SelectExpeditionAsync([&h, msg](int expedition) {
				h.PostWorldUpdateAction([&h, expedition, msg](WorldLogic& world) {
					INFO("Player {} expedition selected {}", h.PlayerId(), expedition);
					PlayerLogic& p = world.GetPlayer(h.PlayerId());
					if (p.CanGoExpedition(expedition)) {
						p.EndExpedition(expedition);
					}
					else {
						h.PostWorldUpdateAction([&h, msg](WorldLogic& world) {
							auto v = msg;
							world.Notify(v);
							});
					}
					});
				});
			});

		m.On([](UserInputDispatcher& self, BeginProgressMessage& msg) {
			auto& h = self.Handlers().Select(msg.playerId);
			h.MakeProgressAsync([&h, msg](ProgressTrackType track) {
				h.PostWorldUpdateAction([&h, track, msg](WorldLogic& world) {
					INFO("Player {} advance track {}", h.PlayerId(), (int)track);
					PlayerLogic& p = world.GetPlayer(h.PlayerId());

					if (p.CanUpgradeTrack(track, 0, false)) {
						p.UpgradeTrack(track, 0, false);
					}
					else {
						WARN("Player {} can't advance track {}. Submit another request.", h.PlayerId(), (int)track);
						h.PostWorldUpdateAction([&h, msg](WorldLogic& world) {
							auto v = msg;
							world.Notify(v);
							});
					}

					});
				});
			});

		m.On([](UserInputDispatcher& self, BeginExtraProgressMessage& msg) {
			auto& h = self.Handlers().Select(msg.playerId);
			h.MakeProgressAsync([&h, msg](ProgressTrackType track) {
				h.PostWorldUpdateAction([&h, track, msg](WorldLogic& world) {
					INFO("Player {} advance track {}", h.PlayerId(), (int)track);
					PlayerLogic& p = world.GetPlayer(h.PlayerId());

					if (track == ProgressTrackType::Unknown) {
						p.EndExtraProgress();
					}
					else if ((msg.allowedTrack == ProgressTrackType::Any || msg.allowedTrack == track) 
						&& p.CanUpgradeTrack(track, msg.discont, true)) {
						p.UpgradeTrack(track, msg.discont, true);
						p.EndExtraProgress();
					}
					else {
						WARN("Player {} can't advance track {}. Submit another request.", h.PlayerId(), (int)track);
						h.PostWorldUpdateAction([&h, msg](WorldLogic& world) {
							auto v = msg;
							world.Notify(v);
							});
					}

					});
				});
			});

		m.On([](UserInputDispatcher& self, SelectPolicyFromHandsMessage& msg) {
			auto& h = self.Handlers().Select(msg.playerId);
            h.SelectPolicyFromHandsAsync(msg.reason, [&h, msg](PoliciesType policy) {
				auto tag = rand();
				INFO("{}: Player {} selected policy {} ({})", tag, h.PlayerId(), ToString(policy), (int)policy);
				h.PostWorldUpdateAction([&h, tag, policy, msg](WorldLogic& world) {
					INFO("{}: Player {} selected policy {} ({})", tag, h.PlayerId(), ToString(policy), (int)policy);
					PlayerLogic& p = world.GetPlayer(h.PlayerId());
					p.EndSelectPolicyFromHands(policy);				
				});
			});
		});

		m.On([](UserInputDispatcher& self, SelectPolicyFromActiveDeckMessage& msg) {
			auto& h = self.Handlers().Select(msg.playerId);
            h.SelectPolicyFromActiveDeckAsync([&h, msg](PoliciesType policy) {
				h.PostWorldUpdateAction([&h, policy, msg](WorldLogic& world) {
					INFO("Player {} selected activated policy {} ({})", h.PlayerId(), ToString(policy), (int)policy);
					PlayerLogic& p = world.GetPlayer(h.PlayerId());
					p.EndSelectPolicyFromActiveDeck(policy);					
				});
			});
		});		

		m.On([](UserInputDispatcher& self, SelectDiscoveryFromHandsMessage& msg) {
			auto& h = self.Handlers().Select(msg.playerId);
			h.SelectDiscoveryFromHandsAsync([&h, msg](discovery_type discovery) {
				h.PostWorldUpdateAction([&h, discovery, msg](WorldLogic& world) {
					INFO("Player {} selected discovery {}", h.PlayerId(), (int)discovery);
					PlayerLogic& p = world.GetPlayer(h.PlayerId());
					p.EndSelectDiscoveryFromHands(discovery);
				});
			});
		});
		
		/*m.On([](UserInputDispatcher& self, BeginDropPolicyMessage& msg) {
			auto& h = self.Handlers().Select(msg.playerId);
			h.SelectPolicyFromHandsAsync([&h, msg](Policies policy) {
				h.PostWorldUpdateAction([&h, policy, msg](WorldLogic& world) {
					INFO("Player {} selected policy {} to drop", h.PlayerId(), (int)policy);
					PlayerLogic& p = world.GetPlayer(h.PlayerId());
					p.EndSelectPolicyFromHands(policy);
				});
			});
		});		*/

		m.On([](UserInputDispatcher& self, SelectDiscoveryFromPoolMessage& msg) {
			auto& h = self.Handlers().Select(msg.playerId);
			h.SelectDiscoveryFromPoolAsync([&h, msg](discovery_type discovery) {
				h.PostWorldUpdateAction([&h, discovery, msg](WorldLogic& world) {
					INFO("Player {} selected discovery {} ({}) to drop", h.PlayerId(), ToString(discovery), (int)discovery);
					PlayerLogic& p = world.GetPlayer(h.PlayerId());
					p.EndSelectDiscoveryFromPool(discovery);
				});
			});
		});		

		m.On([](UserInputDispatcher& self, SelectActionMessage& msg) {
				auto& h = self.Handlers().Select(msg.playerId);
				h.SelectActionAsync(msg.diceValue, msg.allowMilitary, [&h, msg](ActionType action) {
				auto tag = rand();
				INFO("{}: Player {} action select {} ({})", tag, h.PlayerId(), ToString(action), (int)action);
				h.PostWorldUpdateAction([&h, action, msg, tag](WorldLogic& world) {
					INFO("{}: Player {} action select {} ({})", tag, h.PlayerId(), ToString(action), (int)action);
					PlayerLogic& p = world.GetPlayer(h.PlayerId());
					p.EndSelectionAction(action);
				});
			});
		});		
	}
};

static UserInputDispatcherMapping g_mapping;
static InitMapping g_initMapping{ g_mapping };

void UserInputDispatcher::Next(GameMessage& msg) {
	g_mapping.Process(*this, msg);
}

void UserInputDispatcher::Complete() {
	assert(false);
}

void UserInputDispatcher::SelectPlayersCount() {
	assert(false);
}

void UserInputDispatcher::SelectPlayersColor() {
	assert(false);
}

void UserInputDispatcher::SelectCity() {
	assert(false);
}
//
//void UserInputDispatcher::AdvanceAnyTrackForFree(int playerId) { assert(false); }
//void UserInputDispatcher::AdvanceAnyTrack(int playerId, int discont) { assert(false); }
//void UserInputDispatcher::AdvanceMilitaryTrack(int playerId, int discont) { assert(false); }
//void UserInputDispatcher::SelectArgosLevel2(int playerId) { assert(false); }
//void UserInputDispatcher::SelectThebesLevel2(int playerId) { assert(false); }
////void UserInputDispatcher::SelectExpedition(int playerId, SelectExpeditionCallback cb) { assert(false); }
//void UserInputDispatcher::PlayOstracism(int playerId) { assert(false); }
//void UserInputDispatcher::TakeDiscovery(int playerId, int count) { assert(false); }
//void UserInputDispatcher::DropPolicies(int playerId, int count) { assert(false); }
////void UserInputDispatcher::DropDiscovery(int playerId, DropDiscoveryCallback cb) { assert(false); }
//void UserInputDispatcher::TakePolicies(int playerId, int count) { assert(false); }
//void UserInputDispatcher::PlayPersiaCampaign() { assert(false); }
//void UserInputDispatcher::DoAnyActionExceptMilitary(int playerId) { assert(false); }
//
//void UserInputDispatcher::DoPhilosophyAction(int playerId) { assert(false); }
//void UserInputDispatcher::DoLawAction(int playerId) { assert(false); }
//void UserInputDispatcher::DoCultureAction(int playerId) { assert(false); }
//void UserInputDispatcher::DoTradeAction(int playerId) { assert(false); }
//void UserInputDispatcher::DoMilitaryAction(int playerId) {
//	assert(false);
//}
//
//void UserInputDispatcher::DoPolicyAction(int playerId) {
//	// _handlers[playerId]->DoExpandAction();
//	assert(false);
//}
//
//void UserInputDispatcher::DoExpandAction(int playerId) {
//	//_handlers[playerId]->DoExpandAction();
//	assert(false);
//}
//
//void UserInputDispatcher::DoDraft(int playerId) {
//	//_handlers[playerId]->DoDraft();
//	assert(false);
//}

//void UserInputDispatcher::SelectPolicy(int playerId, Policies* a, int count, SelectPolicyCallback cb) {
//	assert(false);
//	//_handlers[playerId]->SelectPolicy(a, count, cb);
//}

void UserInputDispatcher::SetHandler(int playerId, IUserInputHandler* handler) {
	_handlers[playerId] = handler;
}

void UserInputDispatcher::Update(WorldLogic& world) {
	for (int i = 0; i < _playersCount; ++i) {
		_handlers[i]->Update(world);
	}

	{
		SpinLockScope scope{ _lock };
		std::swap(_updateCallbacks[0], _updateCallbacks[1]);
	}

	for (auto& cb : _updateCallbacks[1]) {
		cb(world);
	}

	_updateCallbacks[1].clear();
}

bool UserInputDispatcher::IsIdle() const {
	for (int i = 0; i < _playersCount; ++i) {
		if (!_handlers[i]->IsIdle())
			return false;
	}
	return true;
}

AllHandler UserInputDispatcher::Handlers() {
	return AllHandler{ *this };
}

void UserInputDispatcher::SetPlayersCount(int count) {
	_playersCount = count;
	for (int i = 1; i < _playersCount; ++i) {
		_handlers[i] = &_aiHandlers[i];
	}
}

void UserInputDispatcher::AddUpdateCallback(UpdateCallback cb) {
	SpinLockScope scope{ _lock };
	_updateCallbacks[0].push_back(cb);
}

UserInputDispatcher::UserInputDispatcher(WorldLogic& world)
	: _world{ world }
	, _aiHandlers{ AIUserInput {0, world}, AIUserInput {1, world},AIUserInput {2, world},AIUserInput {3, world} }
{
}