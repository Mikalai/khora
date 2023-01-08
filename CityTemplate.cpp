#include <cassert>
#include <UI/UI.h>
#include <PlayerLogic.h>
#include "CityTemplate.h"

CityTemplate::CityTemplate(Cities city, CityEffect& l1, CityEffect& l2, CityEffect& l3, CityEffect& l4)
	: _type{ city } {

    _effects[0] = &l1;
    _effects[1] = &l2;
    _effects[2] = &l3;
    _effects[3] = &l4;
}

const CityEffect& CityTemplate::GetUpgradeEffect(int level) const {    
    assert(level >= 0 && level < 4);
    return *_effects[level];
}

const PlayerPerk& CityTemplate::GetTrackPerk(ProgressTrackType type, int level) const {
	assert(level >= 0 && level < max_city_track_level);
	return std::get<1>(_trackPerks[(int)type][level]);
}

int CityTemplate::GetTrackUpgradeCost(ProgressTrackType type, int level) const {
	assert(level >= 0 && level < max_city_track_level);
	return std::get<0>(_trackPerks[(int)type][level]);
}

std::array<std::array<std::tuple<int, PlayerPerk>, max_city_track_upgrades>, 3> CityTemplate::_trackPerks
{
	// Economy perks
	std::array<std::tuple<int, PlayerPerk>, max_city_track_upgrades> {
		{
			{
				2,
				[](PlayerLogic& logic) {
					logic.AddPopulation(3);
				}
			},
			{
				2,
				[](PlayerLogic& logic) {
					logic.AddPopulation(3);
				}
			},
			{
				3,
				[](PlayerLogic& logic) {
					logic.AddPoints(5);
				}
			},
			{
				3,
				[](PlayerLogic& logic) {
					logic.AddPopulation(5);
				}
			},
			{
				4,
				[](PlayerLogic& logic) {

				},
			},
			{
				4,
				[](PlayerLogic& logic) {
					logic.AddPoints(10);
				}
			}
		}
	},
	// Culture perks
	std::array<std::tuple<int, PlayerPerk>, max_city_track_upgrades> {
		{
			{
				1,
				[](PlayerLogic& logic) {

				},
			},
			{
				4,
				[](PlayerLogic& logic) {
					logic.AddTaxLevel(1);
				}
			},
			{
				6,
				[](PlayerLogic& logic) {
					logic.UnlockDice();
				}
			},
			{
				6,
				[](PlayerLogic& logic) {
					logic.AddTaxLevel(1);
				}
			},
			{
				7,
				[](PlayerLogic& logic) {
					logic.AddTaxLevel(1);
				}
			},
			{
				7,
				[](PlayerLogic& logic) {
					logic.AddTaxLevel(2);
				}
			}
		}
	},
	// Military perks
	std::array<std::tuple<int, PlayerPerk>, max_city_track_upgrades> {
		{
			{
				2,
				[](PlayerLogic& logic) {
					logic.AddGlory(1);
				}
			},
			{
				3,
				[](PlayerLogic& logic) {

				}
			},
			{
				4,
				[](PlayerLogic& logic) {
					logic.AddGlory(1);
				}
			},
			{
				5,
				[](PlayerLogic& logic) {

				}
			},
			{
				7,
				[](PlayerLogic& logic) {
					logic.AddGlory(1);
				}
			},
			{
				9,
				[](PlayerLogic& logic) {
					logic.AddGlory(2);
				}
			}
		}
	}
};

CityEffect milet_levels[] = {
    { 
        0, 0, 0, 0,        
        [](PlayerLogic& logic) {
            logic.AddEconomyLevel(1);
		}
	},
	{
		1, 1, 0, 0,
		[](PlayerLogic& logic) {
			// this is for free
			logic.BeginExtraProgress(ProgressTrackType::Any, 10, [](PlayerLogic& player) {
				player.BeginExtraProgress(ProgressTrackType::Any, 10, [](PlayerLogic& player) {});
			});
		}
    },
    {
        2, 1, 0, 1,
        [](PlayerLogic& logic) {
            logic.AddTradePerk([](PlayerLogic& self) { self.AddPoints(3); });
        }
    },
    {
        4, 3, 0, 2,
        [](PlayerLogic& logic) {
            logic.AddPoints(15);
        }
    }
};

CityEffect thebes_levels[] = {
	{
		0, 0, 0, 0,
		[](PlayerLogic& logic) {
			logic.AddMilitaryLevel(1);
		}
	},
	{
		0, 0, 1, 1,
		[](PlayerLogic& logic) {
			logic.AddAnyMomentPerk([](PlayerLogic& v) {
				if (v.GetGlory() == 0)
					return;

				v.RemoveGlory(1);
				v.AddMoney(2);
				v.AddPoints(4);
			});
		}
	},
	{
		0, 1, 2, 0,
		[](PlayerLogic& logic) {
			logic.AddMilitaryPerk([](PlayerLogic& v) {
				v.BeginExpedition([]() {});
			});
		}
	},
	{
		2, 2, 2, 2,
		[](PlayerLogic& logic) {
			logic.AddEndGamePerk([](PlayerLogic& v) {
				auto count = v.GetSmallDiscoveries();
				v.AddPoints(count * 2);
			});
		}
	}
};

CityEffect sparta_levels[] = {
	{
		0, 0, 0, 0,
		[](PlayerLogic& logic) {
			logic.AddMilitaryLossesPerk([](int baseLosses) {
				return std::max(0, baseLosses - 1);
			});
		}
	},
	{
		1, 0, 2, 0,
		[](PlayerLogic& logic) {
			logic.AddMilitaryPerk([](PlayerLogic& v) {
				v.AddTaxLevel(1);
			});
		}
	},
	{
		2, 1, 3, 1,
		[](PlayerLogic& logic) {
			logic.BeginDoMilitary([&logic]() {
				logic.BeginDoMilitary([] () {});
				});			
		}
	},
	{
		4, 2, 3, 2,
		[](PlayerLogic& logic) {
			logic.AddEndGamePerk([](PlayerLogic& v) {
				auto count = v.GetBlueDiscovery();
				v.AddPoints(count * 4);
			});
		}
	}
};

CityEffect olymp_levels[] = {
	{
		0, 0, 0, 0,
		[](PlayerLogic& logic) {
			logic.AddTaxLevel(1);
		}
	},
	{
		0, 0, 0, 1,
		[](PlayerLogic& logic) {
			logic.AddCulturePerk([](PlayerLogic& self) {
				self.AddArmy(1, false);
				self.AddPhilosophy(1);
			});
		}
	},
	{
		2, 1, 0, 2,
		[](PlayerLogic& logic) {
			logic.AddCulture(2);
		}
	},
	{
		3, 2, 1, 3,
		[](PlayerLogic& logic) {
			logic.DoCulture([]() {});
			logic.DoCulture([]() {});
			logic.DoCulture([]() {});
		}
	}
};

CityEffect corinth_levels[] = {
	{
		0, 0, 0, 0,
		[](PlayerLogic& logic) {
			logic.AddMoney(4);
		}
	},
	{
		1, 1, 0, 0,
		[](PlayerLogic& logic) {
			auto count = logic.GetDiscoveries().size();
			logic.AddTaxLevel(count);
		}
	},
	{
		2, 2, 1, 1,
		[](PlayerLogic& logic) {
			logic.AddProgressCostPerk([](ProgressTrackType type, int baseCost) {
				return std::max(0, baseCost - 1);
			});
			logic.AddAvailableProgress(1);
		}
	},
	{
		3, 2, 2, 2,
		[](PlayerLogic& logic) {
			logic.AddEndGamePerk([](PlayerLogic& v) {
				auto count = v.GetDiscoveries().size();
				v.AddPoints(2 * count);
			});
		}
	}
};

CityEffect athenes_levels[] = {
	{
		0,0,0,0,
		[](PlayerLogic& logic) {
			logic.AddPhilosophy(3);
		}
	},
	{
		0,1,0,1,
		[](PlayerLogic& logic) {
			logic.AddPolicyPerk([](PlayerLogic& v) {
				v.AddMoney(2);
				v.AddPoints(3);
			});
		}
	},
	{	1, 0, 2, 0,
		[](PlayerLogic& logic) {
			logic.AddPolicyPerk([](PlayerLogic& v) {
				v.AddArmy(2, false);
			});
		}
	},
	{
		2, 2, 2, 2,
		[](PlayerLogic& logic) {
			logic.AddEndGamePerk([](PlayerLogic& v) {
				auto activePolicies = v.GetPoliciesInActiveDeckCount();
				v.AddPoints(3 * activePolicies);
			});
		}
	}
};

CityEffect argos_levels[] = {
	{
		0, 0, 0, 0,
		[](PlayerLogic& logic) {
			logic.AddArmy(2, false);
		}
	},
	{
		0, 0, 2, 0,
		[](PlayerLogic& logic) {
			logic.BeginSelectBonus(2, 3, 4, 5,[]() {});
		}
	},
	{
		0, 1, 2, 0,
		[](PlayerLogic& logic) {
			logic.AddMilitaryLevel(1);
		}
	},
	{
		2, 1, 3, 2,
		[](PlayerLogic& logic) {
			logic.AddGlory(2);
		}
	}
};

const CityTemplate g_cityTemplate[] = {
    CityTemplate{city_milet, milet_levels[0], milet_levels[1], milet_levels[2], milet_levels[3] },
    CityTemplate{city_thebes, thebes_levels[0], thebes_levels[1], thebes_levels[2], thebes_levels[3] },
	CityTemplate{city_sparta, sparta_levels[0], sparta_levels[1], sparta_levels[2], sparta_levels[3] },
    CityTemplate{city_olymp, olymp_levels[0], olymp_levels[1], olymp_levels[2], olymp_levels[3] },
    CityTemplate{city_corinth, corinth_levels[0], corinth_levels[1], corinth_levels[2], corinth_levels[3] },
    CityTemplate{city_athens, athenes_levels[0], athenes_levels[1], athenes_levels[2], athenes_levels[3] },
    CityTemplate{city_argos, argos_levels[0], argos_levels[1], argos_levels[2], argos_levels[3]}
};


const CityTemplate& GetCityTemplate(Cities city) {
    return g_cityTemplate[(int)city];
}
