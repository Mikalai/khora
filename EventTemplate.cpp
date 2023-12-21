#include <cassert>
#include <Resources.h>
#include <Log/Log.h>
#include <UI/UI.h>
#include <WorldLogic.h>
#include <PlayerLogic.h>
#include <PoliciesManipulator.h>
#include <EventTemplate.h>

EventTemplate::EventTemplate(GlobalEventStage stage, GlobalEventType Event, EventEffect& effect)
	: _stage{ stage }
    , _type{ Event }
	, effect{ &effect }
{
    assert(Event == effect.GetType());
}

GlobalEventStage EventTemplate::GetStage() const {
    return _stage;
}

const EventEffect& EventTemplate::GetEffect() const {
	return *effect;
}

GlobalEventType EventTemplate::GetType() const {
	return _type;
}

EventEffect g_effects[] = {
    {
        GlobalEventType::PopulationGrowth, [](WorldLogic& logic) {
            for (int i = 0; i < logic.GetPlayersCount(); ++i) {
                auto& player = logic.GetPlayer(i);
                int sum = 0;
                for (int j = 0; j < player.GetDiceCount(); ++j) {
                    auto c = player.GetDice(j);
                    sum += c;
                }

                if (sum <= 4) {
                    player.AddPhilosophy(1);
                }
            }
        }
    },   	
    { 
        GlobalEventType::SaviorOfGreece, [](WorldLogic& logic) {
            auto armies = logic.Armies();
            armies.Max([](PlayerLogic& player) {
                player.AddMoney(2);
            });
            armies.Min([](PlayerLogic& player) {
                player.RemoveMoney(std::min(player.GetMoney(), 2));
            });
        }
    },
    { 
        GlobalEventType::InventionOfTheTrireme, [](WorldLogic& logic) {
            for (int i = 0; i < logic.GetPlayersCount(); ++i) {
                logic.GetPlayer(i).AddArmy(3, false);
            }
        }
    },
    { 
        GlobalEventType::Conscription, [](WorldLogic& logic) {
            auto armies = logic.Armies();
            armies.Max([](PlayerLogic& player) {
                player.AddPopulation(3);
            });
            armies.Min([](PlayerLogic& player) {
                player.RemovePopulation(3);
            });
        }
    },
    { 
		GlobalEventType::MilitarySuperiority, [](WorldLogic& logic) {
            auto armies = logic.Armies();
            armies.Max([](PlayerLogic& player) {
				player.BeginExtraProgress(ProgressTrackType::Any, 2, [](PlayerLogic&) {});
            });
		} 
	},
    { 
        GlobalEventType::RiseOfPersia, [](WorldLogic& logic) {
         logic.GetPlayers().ForEach([](PlayerLogic& player) {
				player.BeginExtraProgress(ProgressTrackType::Military, 2, [](PlayerLogic&) {});
			});
        }
    },
    { 
        GlobalEventType::Prosperity, [](WorldLogic& logic) {
            auto armies = logic.Armies();
			armies.Max([](PlayerLogic& player) {
                player.BeginSelectPolicyFromHands(PolicySelectionReasonType::Activate, [&player](PoliciesType policy) {
					if (player.CanActivatePolicy(policy)) {
						player.ActivatePolicy(policy);
					}					
                });
                //ui().DoPolicyAction(player.GetId());
            });
        }
    },
    { 
        GlobalEventType::DeliveriesFromLydia, [](WorldLogic& logic) {
         logic.GetPlayers().ForEach([](PlayerLogic& player) {
                player.AddMoney(3);
            });
        } 
    },
    { 
        GlobalEventType::Hostilities, [](WorldLogic& logic) {
         logic.GetPlayers().ForEach([](PlayerLogic& player) {
                player.RemoveArmy(std::min(2, player.GetArmySize()));
            });
        }
    },
    {
        GlobalEventType::ThirtyTyrants, [](WorldLogic& logic) {
            logic.Armies().Max([&logic](PlayerLogic& player) {
                for (int i = 0; i < 2; ++i) {
					if (logic.Policies().CanTake()) {
						auto policy = logic.Policies().GetNextPolicy();
						player.AddPolicy(policy, false);
					}
                }
            });

			logic.Armies().Min([](PlayerLogic& player) {
                player.BeginSelectPolicyFromHandsToDrop([&player](PoliciesType policy) {
                    if (policy != PoliciesType::policy_unknown) {
						player.RemovePolicy(policy);
                        player.BeginSelectPolicyFromHandsToDrop([&player](PoliciesType policy) {
                            if (policy != PoliciesType::policy_unknown) {
								player.RemovePolicy(policy);
							}
							else {
								assert(player.GetPoliciesInHandCount() == 0);
							}
                        });
					}
					else {
						assert(player.GetPoliciesInHandCount() == 0);
					}
                });
            });
        } 
    },
    { 
        GlobalEventType::PlagueOfAthens, [](WorldLogic& logic) {
         logic.GetPlayers().ForEach([](PlayerLogic& player) {
                player.RemovePopulation(2);
            });
        }
    },
    { 
        GlobalEventType::DelphicOracle, [](WorldLogic& logic) {
         logic.GetPlayers().ForEach([](PlayerLogic& player) {
                player.BeginSelectDiscoveryFromHands([&player](discovery_type discovery) {
                    if (discovery != discovery_type::no) {
                        player.AddPhilosophy(2);
						player.RemoveDiscovery(discovery);
					}
					else {
						assert(player.GetDiscoveries().empty());
					}
                });
            });
        }
    },
    { 
        GlobalEventType::Drought, [](WorldLogic& logic) {
         logic.GetPlayers().ForEach([](PlayerLogic& player) {
                player.RemoveMoney(std::min(2, player.GetMoney()));
            });
        } 
    },
    { 
        GlobalEventType::EleusinianMysteries, [](WorldLogic& logic) {
            logic.Armies().Max([](PlayerLogic& player) {
                player.AddPoints(4);
            }).Min([](PlayerLogic& player) {
                player.RemovePoints(std::min(4, player.GetPoints()));
            });
        }
    },
    { 
        GlobalEventType::TheBirthOfTheAcademy, [](WorldLogic& logic) {
            logic.Armies().Max([](PlayerLogic& player) {
                player.AddPhilosophy(1);
            }).Min([](PlayerLogic& player) {
                player.RemovePhilosophy(player.GetPhilosophyCount());
            });
        }
    },
	{
		GlobalEventType::MilitaryCampaignAgainstPersia, [](WorldLogic& logic) {
			if (logic.IsPersipolisTaken()) {
             
             logic.GetPlayers().OrderedByDices().Apply([](PlayerLogic& player) {
					player.ResetActions();
					player.BeginSelectAction(6, false, [&player](ActionType action) {
						INFO("Player {} selected {} during military campaing", player.GetId(), ActionToString[As<int>(action)]);
						player.BeginExecuteAction(6, action, [&player, action]() {
							INFO("Player {} completed execution", player.GetId(), ActionToString[As<int>(action)]);
							});
						});
					});
			}
		}
	}
};

EventTemplate g_eventTemplates[] {
    {GlobalEventStage::DiceStage, GlobalEventType::PopulationGrowth, g_effects[(int)GlobalEventType::PopulationGrowth]},    
    {GlobalEventStage::RoundStage, GlobalEventType::SaviorOfGreece, g_effects[(int)GlobalEventType::SaviorOfGreece]},
    {GlobalEventStage::RoundStage, GlobalEventType::InventionOfTheTrireme, g_effects[(int)GlobalEventType::InventionOfTheTrireme]},
    {GlobalEventStage::RoundStage, GlobalEventType::Conscription, g_effects[(int)GlobalEventType::Conscription]},
    {GlobalEventStage::RoundStage, GlobalEventType::MilitarySuperiority, g_effects[(int)GlobalEventType::MilitarySuperiority]},
    {GlobalEventStage::RoundStage, GlobalEventType::RiseOfPersia, g_effects[(int)GlobalEventType::RiseOfPersia]},
    {GlobalEventStage::RoundStage, GlobalEventType::Prosperity, g_effects[(int)GlobalEventType::Prosperity]},
    {GlobalEventStage::RoundStage, GlobalEventType::DeliveriesFromLydia, g_effects[(int)GlobalEventType::DeliveriesFromLydia]},
    {GlobalEventStage::RoundStage, GlobalEventType::Hostilities, g_effects[(int)GlobalEventType::Hostilities]},
    {GlobalEventStage::RoundStage, GlobalEventType::ThirtyTyrants, g_effects[(int)GlobalEventType::ThirtyTyrants]},
    {GlobalEventStage::RoundStage, GlobalEventType::PlagueOfAthens, g_effects[(int)GlobalEventType::PlagueOfAthens]},
    {GlobalEventStage::RoundStage, GlobalEventType::DelphicOracle, g_effects[(int)GlobalEventType::DelphicOracle]},
    {GlobalEventStage::RoundStage, GlobalEventType::Drought, g_effects[(int)GlobalEventType::Drought]},
    {GlobalEventStage::RoundStage, GlobalEventType::EleusinianMysteries, g_effects[(int)GlobalEventType::EleusinianMysteries]},
    {GlobalEventStage::RoundStage, GlobalEventType::TheBirthOfTheAcademy, g_effects[(int)GlobalEventType::TheBirthOfTheAcademy]},
	{GlobalEventStage::RoundStage, GlobalEventType::MilitaryCampaignAgainstPersia, g_effects[(int)GlobalEventType::MilitaryCampaignAgainstPersia]}
};

const EventTemplate& GetEventTemplate(GlobalEventType Event) {
    return g_eventTemplates[(int)Event];
}
