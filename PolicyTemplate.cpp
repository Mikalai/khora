#pragma once

#include <cassert>
#include <Resources.h>
#include <Locale/Translate.h>
#include <array>
#include <Log/Log.h>
#include <UI/UI.h>
#include <WorldLogic.h>
#include <PoliciesManipulator.h>
#include <PlayerLogic.h>
#include <PolicyTemplate.h>

PolicyTemplate::PolicyTemplate(PoliciesType policy, PolicyEffect& effect, PolicyType type)
	: policy{ policy }
	, effect{ &effect }
	, type{ type }
{
	assert(policy == effect.GetType());
}

const PolicyEffect& PolicyTemplate::GetEffect() const {
	return *effect;
}

PoliciesType PolicyTemplate::GetType() const { return policy; }

std::tuple<PolicyEffect, PolicyType> g_policyEffects[As<int>(PoliciesType::policies_count)] = {
	{
		{
      PoliciesType::policy_front_old_guard,
			POLICY_OLD_GUARD_COST, POLICY_OLD_GUARD_RED, POLICY_OLD_GUARD_BLUE, POLICY_OLD_GUARD_GREEN,
			[](PlayerLogic& logic) {
				logic.AddPostProgressPerk([](PlayerLogic& v) {
					if (!v.HasUpgradedAnyTrack()) {
                  INFO("Player {} uses perk {} ({})", v.GetId(), ToString(PoliciesType::policy_front_old_guard), As<int>(PoliciesType::policy_front_old_guard));
						v.AddPoints(POLICY_OLD_GUARD_ADD_POINTS);
					}
				});
			}
		}, PolicyType::Multiple
	},
	{
		{
      PoliciesType::policy_front_archives,
			POLICY_ARCHIVES_COST, POLICY_ARCHIVES_RED, POLICY_ARCHIVES_BLUE, POLICY_ARCHIVES_GREEN,
			[](PlayerLogic& logic) {
				logic.AddPhilosophy(POLICY_ARCHIVES_ADD_PHILOSOPHY);
			}
		}, PolicyType::Single
	},
	{
		{
      PoliciesType::policy_front_asket,
			POLICY_ASKET_COST, POLICY_ASKET_RED, POLICY_ASKET_BLUE, POLICY_ASKET_GREEN,
			[](PlayerLogic& logic) {
				logic.AddEndGamePerk([](PlayerLogic& v) {
					auto count = v.GetPoliciesInHandCount();
					v.AddPoints(count * 3);
				});
			}
		}, PolicyType::EndGame
	},
	{
		{
      PoliciesType::policy_front_bank,
			POLICY_BANK_COST, POLICY_BANK_RED, POLICY_BANK_BLUE, POLICY_BANK_GREEN,
			[](PlayerLogic& logic) {
				logic.AddEndGamePerk([](PlayerLogic& v) {
					auto count = v.GetMoney();
					v.AddPoints(count / 2);
				});
			}
		}, PolicyType::EndGame
	},
	{
		{
      PoliciesType::policy_front_central_government,
			POLICY_CENTRAL_GOVERNMENT_COST, POLICY_CENTRAL_GOVERNMENT_RED, POLICY_CENTRAL_GOVERNMENT_BLUE, POLICY_CENTRAL_GOVERNMENT_GREEN,
			[](PlayerLogic& logic) {
				logic.AddEndGamePerk([](PlayerLogic& v) {
					auto count = v.GetPoliciesInActiveDeckCount();
					v.AddPoints(count * 2);
				});
			}
		}, PolicyType::EndGame
	},
	{
		{
      PoliciesType::policy_front_coloss,
			POLICY_COLOSS_COST, POLICY_COLOSS_RED, POLICY_COLOSS_BLUE, POLICY_COLOSS_GREEN,
			[](PlayerLogic& logic) {
				logic.AddPoints(POLICY_COLOSS_ADD_POINTS);
			}
		}, PolicyType::Single
	},
	{
		{
      PoliciesType::policy_front_contribution,
			POLICY_CONTRIBUTION_COST, POLICY_CONTRIBUTION_RED, POLICY_CONTRIBUTION_BLUE, POLICY_CONTRIBUTION_GREEN,
			[](PlayerLogic& logic) {
				auto count = logic.GetDiscoveries().size();
				logic.AddPoints(count);
			}
		}, PolicyType::Single
	},
	{
		{
      PoliciesType::policy_front_corinthian_order,
			POLICY_CORINTHIAN_ORDER_COST, POLICY_CORINTHIAN_ORDER_RED, POLICY_CORINTHIAN_ORDER_BLUE, POLICY_CORINTHIAN_ORDER_GREEN,
			[](PlayerLogic& logic) {
				logic.AddDiscoveryCostTradePerk([id = logic.GetId()](int baseCost) {
              INFO("Player {} uses perk {} ({})", id, ToString(PoliciesType::policy_front_corinthian_order), As<int>(PoliciesType::policy_front_corinthian_order));
					return POLICY_CORINTHIAN_ORDER_DISCOVERY_PRICE;
				});
			}
		}, PolicyType::Multiple
	},
	{
		{
      PoliciesType::policy_front_diolk,
			POLICY_DIOLK_COST, POLICY_DIOLK_RED, POLICY_DIOLK_BLUE, POLICY_DIOLK_GREEN,
			[](PlayerLogic& logic) {
				logic.AddTradePerk([](PlayerLogic& logic) {
              INFO("Player {} uses perk {} ({})", logic.GetId(), ToString(PoliciesType::policy_front_diolk), As<int>(PoliciesType::policy_front_diolk));
					logic.AddMoney(POLICY_DIOLK_ADD_MONEY);
					logic.AddPoints(POLICY_DIOLK_ADD_POINTS);
					logic.AddArmy(POLICY_DIOLK_ADD_ARMY, false);
				});
			}
		}, PolicyType::Multiple
	},
	{
		{
      PoliciesType::policy_front_diversification,
			POLICY_DIVERSIFICATION_COST, POLICY_DIVERSIFICATION_RED, POLICY_DIVERSIFICATION_BLUE, POLICY_DIVERSIFICATION_GREEN,
			[](PlayerLogic& logic) {
				logic.AddEndGamePerk([](PlayerLogic& v) {
					auto count = std::min(v.GetMilitaryLevel(), std::min(v.GetCultureLevel(), v.GetEconomy()));
					v.AddPoints(count * 3);
				});
			}
		}, PolicyType::EndGame
	},
	{
		{
      PoliciesType::policy_front_evpalin_tunnel,
			POLICY_EVPALIN_TUNNEL_COST, POLICY_EVPALIN_TUNNEL_RED, POLICY_EVPALIN_TUNNEL_BLUE, POLICY_EVPALIN_TUNNEL_GREEN,
			[](PlayerLogic& logic) {
				logic.AddPoints(POLICY_EVPALIN_TUNNEL_ADD_POINTS);
			}
		}, PolicyType::Single
	},
	{
		{
      PoliciesType::policy_front_gold_reserve,
			POLICY_GOLD_RESERVE_COST, POLICY_GOLD_RESERVE_RED, POLICY_GOLD_RESERVE_BLUE, POLICY_GOLD_RESERVE_GREEN,
			[](PlayerLogic& logic) {
				auto count = logic.GetEconomy();
				logic.AddPoints(count * 2);
			}
		}, PolicyType::EndGame
	},
	{
		{
      PoliciesType::policy_front_gradualism,
			POLICY_GRADUALISM_COST, POLICY_GRADUALISM_RED, POLICY_GRADUALISM_BLUE, POLICY_GRADUALISM_GREEN,
			[](PlayerLogic& logic) {
				logic.AddProgressCostPerk([id = logic.GetId()](ProgressTrackType type, int baseCost) {
					// INFO("Player {} uses perk {} ({})", id, ToString(Policies::policy_front_gradualism), As<int>(Policies::policy_front_gradualism));
					return baseCost - POLICY_GRADUALISM_COST_DISCONT;
				});
			}
		}, PolicyType::Multiple
	},
	{
		{
      PoliciesType::policy_front_greek_fire,
			POLICY_GREEK_FIRE_COST, POLICY_GREEK_FIRE_RED, POLICY_GREEK_FIRE_BLUE, POLICY_GREEK_FIRE_GREEN,
			[](PlayerLogic& logic) {
				logic.AddArmy(POLICY_GREEK_FIRE_ADD_ARMY, false);
			}
		}, PolicyType::Single
	},
	{
		{
      PoliciesType::policy_front_helepolis,
			POLICY_HELEPOLIS_COST, POLICY_HELEPOLIS_RED, POLICY_HELEPOLIS_BLUE, POLICY_HELEPOLIS_GREEN,
			[](PlayerLogic& logic) {
				logic.AddMilitaryLossesPerk([id = logic.GetId()](int baseLose) {
              INFO("Player {} uses perk {} ({})", id, ToString(PoliciesType::policy_front_helepolis), As<int>(PoliciesType::policy_front_helepolis));
					return baseLose - POLICY_HELEPOLIS_EXPEDISION_LOSE_DISCONT;
				});
			}
		}, PolicyType::Multiple
	},
	{
		{
      PoliciesType::policy_front_high_tax,
			POLICY_HIGH_TAX_COST, POLICY_HIGH_TAX_RED, POLICY_HIGH_TAX_BLUE, POLICY_HIGH_TAX_GREEN,
			[](PlayerLogic& logic) {
				logic.AddEndGamePerk([](PlayerLogic& v) {
					auto count = v.GetTax();
					v.AddPoints(count * 2);
				});
			}
		}, PolicyType::EndGame
	},
	{
		{
      PoliciesType::policy_front_hire_mercenay,
			POLICY_HIRE_MERCENAY_COST, POLICY_HIRE_MERCENAY_RED, POLICY_HIRE_MERCENAY_BLUE, POLICY_HIRE_MERCENAY_GREEN,
			[](PlayerLogic& player) {
				auto count = player.GetEconomy();
				player.AddArmy(count, false);
			}
		}, PolicyType::Single
	},
	{
		{
      PoliciesType::policy_front_lighthouse,
			POLICY_LIGHTHOUSE_COST, POLICY_LIGHTHOUSE_RED, POLICY_LIGHTHOUSE_BLUE, POLICY_LIGHTHOUSE_GREEN,
			[](PlayerLogic& player) {
				player.AddTradePerk([](PlayerLogic& v) {
              INFO("Player {} uses perk {} ({})", v.GetId(), ToString(PoliciesType::policy_front_lighthouse), As<int>(PoliciesType::policy_front_lighthouse));
					v.AddPoints(POLICY_LIGHTHOUSE_ADD_POINTS);
				});
			}
		}, PolicyType::Multiple
	},
	{
		{
      PoliciesType::policy_front_lyceum_foundation,
			POLICY_LYCEUM_FOUNDATION_COST, POLICY_LYCEUM_FOUNDATION_RED, POLICY_LYCEUM_FOUNDATION_BLUE, POLICY_LYCEUM_FOUNDATION_GREEN,
			[](PlayerLogic& logic) {
				logic.AddPhilosophyPerk([](PlayerLogic& v) {
              INFO("Player {} uses perk {} ({})", v.GetId(), ToString(PoliciesType::policy_front_lyceum_foundation), As<int>(PoliciesType::policy_front_lyceum_foundation));
					v.AddPhilosophy(POLICY_LYCEUM_FOUNDATION_ADD_PHILOSOPHY);
				});
			}
		}, PolicyType::Multiple
	},
	{
		{
      PoliciesType::policy_front_mint,
			POLICY_MINT_COST, POLICY_MINT_RED, POLICY_MINT_BLUE, POLICY_MINT_GREEN,
			[](PlayerLogic& logic) {
				logic.AddProgressCostPerk([id = logic.GetId()](ProgressTrackType type, int baseCost) {
              INFO("Player {} uses perk {} ({})", id, ToString(PoliciesType::policy_front_mint), As<int>(PoliciesType::policy_front_mint));

					if (type == ProgressTrackType::Economy) {
						return 0;
					}
					return baseCost;
				});
			}
		}, PolicyType::Multiple
	},
	{
		{
      PoliciesType::policy_front_oracle,
			POLICY_ORACLE_COST, POLICY_ORACLE_RED, POLICY_ORACLE_BLUE, POLICY_ORACLE_GREEN,
			[](PlayerLogic& logic) {
				logic.AddUpgradePerk([](PlayerLogic& v) {
              INFO("Player {} uses perk {} ({})", v.GetId(), ToString(PoliciesType::policy_front_oracle), As<int>(PoliciesType::policy_front_oracle));
					v.AddPoints(POLICY_ORACLE_ADD_POINTS);
				});
			}
		}, PolicyType::Multiple
	},
	{
		{
      PoliciesType::policy_front_ostracism,
			POLICY_OSTRACISM_COST, POLICY_OSTRACISM_RED, POLICY_OSTRACISM_BLUE, POLICY_OSTRACISM_GREEN,
			[](PlayerLogic& logic) {
          logic.BeginSelectPolicyFromActiveDeck([&logic](PoliciesType policy) {
					logic.AddPolicy(policy, false);
              logic.BeginSelectPolicyFromHandsToActivate([&logic](PoliciesType policy) {
						if (logic.CanActivatePolicy(policy)) {
							logic.ActivatePolicy(policy);
						}
					});
				});
			}
		}, PolicyType::Single
	},
	{
		{
      PoliciesType::policy_front_painter_standing,
			POLICY_PAINTER_STANDING_COST, POLICY_PAINTER_STANDING_RED, POLICY_PAINTER_STANDING_BLUE, POLICY_PAINTER_STANDING_GREEN,
			[](PlayerLogic& logic) {
				logic.AddCulturePerk([](PlayerLogic& v) {
              INFO("Player {} uses perk {} ({})", v.GetId(), ToString(PoliciesType::policy_front_painter_standing), As<int>(PoliciesType::policy_front_painter_standing));
					v.AddPoints(POLICY_PAINTER_STANDING_ADD_POINTS);
				});
			}
		}, PolicyType::Multiple
	},
	{
		{
      PoliciesType::policy_front_peripter,
			POLICY_PERIPTER_COST, POLICY_PERIPTER_RED, POLICY_PERIPTER_BLUE, POLICY_PERIPTER_GREEN,
			[](PlayerLogic& logic) {
				logic.AddCulture(POLICY_PERIPTER_ADD_CULTURE);
			}
		}, PolicyType::Single
	},
	{
		{
      PoliciesType::policy_front_persia,
			POLICY_PERSIANS_COST, POLICY_PERSIANS_RED, POLICY_PERSIANS_BLUE, POLICY_PERSIANS_GREEN,
			[](PlayerLogic& logic) {
				logic.AddCulturePerk([](PlayerLogic& v) {
              INFO("Player {} uses perk {} ({})", v.GetId(), ToString(PoliciesType::policy_front_persia), As<int>(PoliciesType::policy_front_persia));
					v.AddArmy(POLICY_PERSIANS_ADD_ARMY, false);
				});
			}
		}, PolicyType::Multiple
	},
	{
		{
      PoliciesType::policy_front_power,
			POLICY_POWER_COST, POLICY_POWER_RED, POLICY_POWER_BLUE, POLICY_POWER_GREEN,
			[](PlayerLogic& logic) {
				logic.AddTaxPerk([](PlayerLogic& v) {
              INFO("Player {} uses perk {} ({})", v.GetId(), ToString(PoliciesType::policy_front_power), As<int>(PoliciesType::policy_front_power));

					auto& world = v.GetWorld();
					auto culture = v.GetCultureLevel();

					for (int i = 0; i < world.GetPlayersCount(); ++i) {
						if (i == v.GetId())
							continue;
						auto& other = world.GetPlayer(i);
						if (culture > other.GetCultureLevel())
							return;
					}

					v.AddPoints(POLICY_POWER_ADD_POINTS);
				});			
			}
		}, PolicyType::Multiple
	},
	{
		{
      PoliciesType::policy_front_proscenium,
			POLICY_PROSCENIUM_COST, POLICY_PROSCENIUM_RED, POLICY_PROSCENIUM_BLUE, POLICY_PROSCENIUM_GREEN,
			[](PlayerLogic& logic) {
				logic.AddEndGamePerk([](PlayerLogic& v) {
					auto count = v.GetPopulation();
					v.AddPoints(count);
				});
			}
		}, PolicyType::EndGame
	},
	{
		{
      PoliciesType::policy_front_public_market,
			POLICY_PUBLIC_MARKET_COST, POLICY_PUBLIC_MARKET_RED, POLICY_PUBLIC_MARKET_BLUE, POLICY_PUBLIC_MARKET_GREEN,
			[](PlayerLogic& logic) {
				logic.AddTaxPerk([](PlayerLogic& v) {
              INFO("Player {} uses perk {} ({})", v.GetId(), ToString(PoliciesType::policy_front_public_market), As<int>(PoliciesType::policy_front_public_market));

					auto& world = v.GetWorld();
					auto economy = v.GetEconomy();

					for (int i = 0; i < world.GetPlayersCount(); ++i) {
						if (i == v.GetId())
							continue;
						auto& other = world.GetPlayer(i);
						if (other.GetEconomy() > economy)
							return;
					}

					v.AddPoints(POLICY_PUBLIC_MARKET_ADD_POINTS);
				});			
			}
		}, PolicyType::Multiple
	},
	{
		{
      PoliciesType::policy_front_rare_collection,
			POLICY_RARE_COLLECTION_COST, POLICY_RARE_COLLECTION_RED, POLICY_RARE_COLLECTION_BLUE, POLICY_RARE_COLLECTION_GREEN,
			[](PlayerLogic& logic) {				
				logic.AddPolicyPerk([](PlayerLogic& v) {
              INFO("Player {} uses perk {} ({})", v.GetId(), ToString(PoliciesType::policy_front_rare_collection), As<int>(PoliciesType::policy_front_rare_collection));
					v.AddMoney(POLICY_RARE_COLLECTION_ADD_MONEY);
				});
			}
		}, PolicyType::Multiple
	},
	{
		{
      PoliciesType::policy_front_reform,
			POLICY_REFORM_COST, POLICY_REFORM_RED, POLICY_REFORM_BLUE, POLICY_REFORM_GREEN,
			[](PlayerLogic& logic) {
				logic.AddProgressPerk([](PlayerLogic& v) {
              INFO("Player {} uses perk {} ({})", v.GetId(), ToString(PoliciesType::policy_front_reform), As<int>(PoliciesType::policy_front_reform));
					v.BeginExtraProgress(ProgressTrackType::Any, 0, [](PlayerLogic&) {});
				});
			}
		}, PolicyType::Multiple
	},
	{
		{
      PoliciesType::policy_front_rivalvary,
			POLICY_RIVALVARY_COST, POLICY_RIVALVARY_RED, POLICY_RIVALVARY_BLUE, POLICY_RIVALVARY_GREEN,
			[](PlayerLogic& logic) {
				auto& world = logic.GetWorld();
				auto military = logic.GetMilitaryLevel();
				for (int i = 0; i < world.GetPlayersCount(); ++i) {
					if (i == logic.GetId())
						continue;
					auto& other = world.GetPlayer(i);
					if (military >= other.GetMilitaryLevel())
						return;
				}
				logic.AddMilitaryLevel(1);
			}
		}, PolicyType::Single
	},
	{
		{
      PoliciesType::policy_front_science_respect,
			POLICY_SCIENCE_RESPECT_COST, POLICY_SCIENCE_RESPECT_RED, POLICY_SCIENCE_RESPECT_BLUE, POLICY_SCIENCE_RESPECT_GREEN,
			[](PlayerLogic& logic) {
				assert(POLICY_SCIENCE_RESPECT_ADD_DISCOVERY == 1);
				logic.BeginSelectDiscoveryFromPool([](discovery_type discovery) {});				
			}
		}, PolicyType::Single
	},
	{
		{
      PoliciesType::policy_front_silver_mine,
			POLICY_SILVER_MINE_COST, POLICY_SILVER_MINE_RED, POLICY_SILVER_MINE_BLUE, POLICY_SILVER_MINE_GREEN,
			[](PlayerLogic& logic) {
				logic.AddTaxLevel(POLICY_SILVER_MINE_ADD_TAX);
			}
		}, PolicyType::Single
	},
	{
		{
      PoliciesType::policy_front_soviet,
			POLICY_SOVIET_COST, POLICY_SOVIET_RED, POLICY_SOVIET_BLUE, POLICY_SOVIET_GREEN,
			[](PlayerLogic& logic) {			
				for (int i = 0; i < POLICY_SOVIET_POLICIES_COUNT; ++i) {
					if (!logic.GetWorld().Policies().CanTake())
						break;
					auto p = logic.GetWorld().Policies().GetNextPolicy();
					logic.AddPolicy(p, false);
				}
			}
		}, PolicyType::Single
	},
	{
		{
      PoliciesType::policy_front_stadium,
			POLICY_STADIUM_COST, POLICY_STADIUM_RED, POLICY_STADIUM_BLUE, POLICY_STADIUM_GREEN,
			[](PlayerLogic& logic) {
				logic.AddTaxPerk([](PlayerLogic& v) {
              INFO("Player {} uses perk {} ({})", v.GetId(), ToString(PoliciesType::policy_front_stadium), As<int>(PoliciesType::policy_front_stadium));
					v.AddArmy(POLICY_STADIUM_ADD_ARMY, false);
				});
			}
		}, PolicyType::Multiple
	},
	{
		{
      PoliciesType::policy_front_statue_hall,
			POLICY_STATUE_HALL_COST, POLICY_STATUE_HALL_RED, POLICY_STATUE_HALL_BLUE, POLICY_STATUE_HALL_GREEN,
			[](PlayerLogic& logic) {
				logic.AddEndGamePerk([](PlayerLogic& v) {
					auto count = v.GetDiscoveries().size();
					v.AddPoints(count);
				});
			}
		}, PolicyType::EndGame
	},
	{
		{
      PoliciesType::policy_front_stone_mine,
			POLICY_STONE_MINE_COST, POLICY_STONE_MINE_RED, POLICY_STONE_MINE_BLUE, POLICY_STONE_MINE_GREEN,
			[](PlayerLogic& logic) {
				logic.AddTaxLevel(POLICY_STONE_MINE_ADD_TAX);
			}
		}, PolicyType::Single
	},
	{
		{
      PoliciesType::policy_front_supplies_from_overseas,
			POLICY_SUPPLIES_FROM_OVERSEAS_COST, POLICY_SUPPLIES_FROM_OVERSEAS_RED, POLICY_SUPPLIES_FROM_OVERSEAS_BLUE, POLICY_SUPPLIES_FROM_OVERSEAS_GREEN,
			[](PlayerLogic& logic) {
				logic.AddTradePerk([](PlayerLogic& v) {
              INFO("Player {} uses perk {} ({})", v.GetId(), ToString(PoliciesType::policy_front_supplies_from_overseas), As<int>(PoliciesType::policy_front_supplies_from_overseas));
					v.AddArmy(POLICY_SUPPLIES_FROM_OVERSEAS_ADD_ARMY, false);
				});
			}
		}, PolicyType::Multiple
	},
	{
		{
      PoliciesType::policy_front_western_gifts,
			0, 0, 0, 0,
			[](PlayerLogic& logic) {
				logic.AddMoney(3);
			}
		}, PolicyType::Single
	},
	{
		{
      PoliciesType::policy_front_amnesty_for_socrat,
			POLICY_AMNESTY_FOR_SOCRAT_COST, POLICY_AMNESTY_FOR_SOCRAT_RED, POLICY_AMNESTY_FOR_SOCRAT_BLUE, POLICY_AMNESTY_FOR_SOCRAT_GREEN,
			[](PlayerLogic& logic) {
				logic.AddLawPerk([](PlayerLogic& v) {
              INFO("Player {} uses perk {} ({})", v.GetId(), ToString(PoliciesType::policy_front_amnesty_for_socrat), As<int>(PoliciesType::policy_front_amnesty_for_socrat));
					v.AddPhilosophy(POLICY_AMNESTY_FOR_SOCRAT_ADD_PHILOSOPHY);
				});
			}
		}, PolicyType::Multiple
	}
};

PolicyTemplate g_policyTemplates[As<int>(PoliciesType::policies_count)] = {
    { PoliciesType::policy_front_old_guard, std::get<0>(g_policyEffects[As<int>(PoliciesType::policy_front_old_guard)]), std::get<1>(g_policyEffects[As<int>(PoliciesType::policy_front_old_guard)]) },
    { PoliciesType::policy_front_archives, std::get<0>(g_policyEffects[As<int>(PoliciesType::policy_front_archives)]), std::get<1>(g_policyEffects[As<int>(PoliciesType::policy_front_archives)]) },
    { PoliciesType::policy_front_asket, std::get<0>(g_policyEffects[As<int>(PoliciesType::policy_front_asket)]), std::get<1>(g_policyEffects[As<int>(PoliciesType::policy_front_asket)]) },
    { PoliciesType::policy_front_bank, std::get<0>(g_policyEffects[As<int>(PoliciesType::policy_front_bank)]), std::get<1>(g_policyEffects[As<int>(PoliciesType::policy_front_bank)]) },
    { PoliciesType::policy_front_central_government, std::get<0>(g_policyEffects[As<int>(PoliciesType::policy_front_central_government)]), std::get<1>(g_policyEffects[As<int>(PoliciesType::policy_front_central_government)]) },
    { PoliciesType::policy_front_coloss, std::get<0>(g_policyEffects[As<int>(PoliciesType::policy_front_coloss)]), std::get<1>(g_policyEffects[As<int>(PoliciesType::policy_front_coloss)]) },
    { PoliciesType::policy_front_contribution, std::get<0>(g_policyEffects[As<int>(PoliciesType::policy_front_contribution)]), std::get<1>(g_policyEffects[As<int>(PoliciesType::policy_front_contribution)]) },
    { PoliciesType::policy_front_corinthian_order, std::get<0>(g_policyEffects[As<int>(PoliciesType::policy_front_corinthian_order)]), std::get<1>(g_policyEffects[As<int>(PoliciesType::policy_front_corinthian_order)]) },
    { PoliciesType::policy_front_diolk, std::get<0>(g_policyEffects[As<int>(PoliciesType::policy_front_diolk)]), std::get<1>(g_policyEffects[As<int>(PoliciesType::policy_front_diolk)]) },
    { PoliciesType::policy_front_diversification, std::get<0>(g_policyEffects[As<int>(PoliciesType::policy_front_diversification)]), std::get<1>(g_policyEffects[As<int>(PoliciesType::policy_front_diversification)]) },
    { PoliciesType::policy_front_evpalin_tunnel, std::get<0>(g_policyEffects[As<int>(PoliciesType::policy_front_evpalin_tunnel)]), std::get<1>(g_policyEffects[As<int>(PoliciesType::policy_front_evpalin_tunnel)]) },
    { PoliciesType::policy_front_gold_reserve, std::get<0>(g_policyEffects[As<int>(PoliciesType::policy_front_gold_reserve)]), std::get<1>(g_policyEffects[As<int>(PoliciesType::policy_front_gold_reserve)]) },
    { PoliciesType::policy_front_gradualism, std::get<0>(g_policyEffects[As<int>(PoliciesType::policy_front_gradualism)]), std::get<1>(g_policyEffects[As<int>(PoliciesType::policy_front_gradualism)]) },
    { PoliciesType::policy_front_greek_fire, std::get<0>(g_policyEffects[As<int>(PoliciesType::policy_front_greek_fire)]), std::get<1>(g_policyEffects[As<int>(PoliciesType::policy_front_greek_fire)]) },
    { PoliciesType::policy_front_helepolis, std::get<0>(g_policyEffects[As<int>(PoliciesType::policy_front_helepolis)]), std::get<1>(g_policyEffects[As<int>(PoliciesType::policy_front_helepolis)]) },
    { PoliciesType::policy_front_high_tax, std::get<0>(g_policyEffects[As<int>(PoliciesType::policy_front_high_tax)]), std::get<1>(g_policyEffects[As<int>(PoliciesType::policy_front_high_tax)]) },
    { PoliciesType::policy_front_hire_mercenay, std::get<0>(g_policyEffects[As<int>(PoliciesType::policy_front_hire_mercenay)]), std::get<1>(g_policyEffects[As<int>(PoliciesType::policy_front_hire_mercenay)]) },
    { PoliciesType::policy_front_lighthouse, std::get<0>(g_policyEffects[As<int>(PoliciesType::policy_front_lighthouse)]), std::get<1>(g_policyEffects[As<int>(PoliciesType::policy_front_lighthouse)]) },
    { PoliciesType::policy_front_lyceum_foundation, std::get<0>(g_policyEffects[As<int>(PoliciesType::policy_front_lyceum_foundation)]), std::get<1>(g_policyEffects[As<int>(PoliciesType::policy_front_lyceum_foundation)]) },
    { PoliciesType::policy_front_mint, std::get<0>(g_policyEffects[As<int>(PoliciesType::policy_front_mint)]), std::get<1>(g_policyEffects[As<int>(PoliciesType::policy_front_mint)]) },
    { PoliciesType::policy_front_oracle, std::get<0>(g_policyEffects[As<int>(PoliciesType::policy_front_oracle)]), std::get<1>(g_policyEffects[As<int>(PoliciesType::policy_front_oracle)]) },
    { PoliciesType::policy_front_ostracism, std::get<0>(g_policyEffects[As<int>(PoliciesType::policy_front_ostracism)]), std::get<1>(g_policyEffects[As<int>(PoliciesType::policy_front_ostracism)]) },
    { PoliciesType::policy_front_painter_standing, std::get<0>(g_policyEffects[As<int>(PoliciesType::policy_front_painter_standing)]), std::get<1>(g_policyEffects[As<int>(PoliciesType::policy_front_painter_standing)]) },
    { PoliciesType::policy_front_peripter, std::get<0>(g_policyEffects[As<int>(PoliciesType::policy_front_peripter)]), std::get<1>(g_policyEffects[As<int>(PoliciesType::policy_front_peripter)]) },
    { PoliciesType::policy_front_persia, std::get<0>(g_policyEffects[As<int>(PoliciesType::policy_front_persia)]), std::get<1>(g_policyEffects[As<int>(PoliciesType::policy_front_persia)]) },
    { PoliciesType::policy_front_power, std::get<0>(g_policyEffects[As<int>(PoliciesType::policy_front_power)]), std::get<1>(g_policyEffects[As<int>(PoliciesType::policy_front_power)]) },
    { PoliciesType::policy_front_proscenium, std::get<0>(g_policyEffects[As<int>(PoliciesType::policy_front_proscenium)]), std::get<1>(g_policyEffects[As<int>(PoliciesType::policy_front_proscenium)]) },
    { PoliciesType::policy_front_public_market, std::get<0>(g_policyEffects[As<int>(PoliciesType::policy_front_public_market)]), std::get<1>(g_policyEffects[As<int>(PoliciesType::policy_front_public_market)]) },
    { PoliciesType::policy_front_rare_collection, std::get<0>(g_policyEffects[As<int>(PoliciesType::policy_front_rare_collection)]), std::get<1>(g_policyEffects[As<int>(PoliciesType::policy_front_rare_collection)]) },
    { PoliciesType::policy_front_reform, std::get<0>(g_policyEffects[As<int>(PoliciesType::policy_front_reform)]), std::get<1>(g_policyEffects[As<int>(PoliciesType::policy_front_reform)]) },
    { PoliciesType::policy_front_rivalvary, std::get<0>(g_policyEffects[As<int>(PoliciesType::policy_front_rivalvary)]), std::get<1>(g_policyEffects[As<int>(PoliciesType::policy_front_rivalvary)]) },
    { PoliciesType::policy_front_science_respect, std::get<0>(g_policyEffects[As<int>(PoliciesType::policy_front_science_respect)]), std::get<1>(g_policyEffects[As<int>(PoliciesType::policy_front_science_respect)]) },
    { PoliciesType::policy_front_silver_mine, std::get<0>(g_policyEffects[As<int>(PoliciesType::policy_front_silver_mine)]), std::get<1>(g_policyEffects[As<int>(PoliciesType::policy_front_silver_mine)]) },
    { PoliciesType::policy_front_soviet, std::get<0>(g_policyEffects[As<int>(PoliciesType::policy_front_soviet)]), std::get<1>(g_policyEffects[As<int>(PoliciesType::policy_front_soviet)]) },
    { PoliciesType::policy_front_stadium, std::get<0>(g_policyEffects[As<int>(PoliciesType::policy_front_stadium)]), std::get<1>(g_policyEffects[As<int>(PoliciesType::policy_front_stadium)]) },
    { PoliciesType::policy_front_statue_hall, std::get<0>(g_policyEffects[As<int>(PoliciesType::policy_front_statue_hall)]), std::get<1>(g_policyEffects[As<int>(PoliciesType::policy_front_statue_hall)]) },
    { PoliciesType::policy_front_stone_mine, std::get<0>(g_policyEffects[As<int>(PoliciesType::policy_front_stone_mine)]), std::get<1>(g_policyEffects[As<int>(PoliciesType::policy_front_stone_mine)]) },
    { PoliciesType::policy_front_supplies_from_overseas, std::get<0>(g_policyEffects[As<int>(PoliciesType::policy_front_supplies_from_overseas)]), std::get<1>(g_policyEffects[As<int>(PoliciesType::policy_front_supplies_from_overseas)]) },
    { PoliciesType::policy_front_western_gifts, std::get<0>(g_policyEffects[As<int>(PoliciesType::policy_front_western_gifts)]), std::get<1>(g_policyEffects[As<int>(PoliciesType::policy_front_western_gifts)]) },
    { PoliciesType::policy_front_amnesty_for_socrat, std::get<0>(g_policyEffects[As<int>(PoliciesType::policy_front_amnesty_for_socrat)]), std::get<1>(g_policyEffects[As<int>(PoliciesType::policy_front_amnesty_for_socrat)]) }
};

std::string g_policyNames[]{
	"policy_front_old_guard",
	"policy_front_archives",
	"policy_front_asket",
	"policy_front_bank",
	"policy_front_central_government",
	"policy_front_coloss",
	"policy_front_contribution",
	"policy_front_corinthian_order",
	"policy_front_diolk",
	"policy_front_diversification",
	"policy_front_evpalin_tunnel",
	"policy_front_gold_reserve",
	"policy_front_gradualism",
	"policy_front_greek_fire",
	"policy_front_helepolis",
	"policy_front_high_tax",
	"policy_front_hire_mercenay",
	"policy_front_lighthouse",
	"policy_front_lyceum_foundation",
	"policy_front_mint",
	"policy_front_oracle",
	"policy_front_ostracism",
	"policy_front_painter_standing",
	"policy_front_peripter",
	"policy_front_persia",
	"policy_front_power",
	"policy_front_proscenium",
	"policy_front_public_market",
	"policy_front_rare_collection",
	"policy_front_reform",
	"policy_front_rivalvary",
	"policy_front_science_respect",
	"policy_front_silver_mine",
	"policy_front_soviet",
	"policy_front_stadium",
	"policy_front_statue_hall",
	"policy_front_stone_mine",
	"policy_front_supplies_from_overseas",
	"policy_front_western_gifts",
	"policy_front_amnesty_for_socrat"
};

std::string g_policyDescriptions[]{
	"policy_front_old_guard",
	"policy_front_archives",
	"policy_front_asket",
	"policy_front_bank",
	"policy_front_central_government",
	"policy_front_coloss",
	"policy_front_contribution",
	"policy_front_corinthian_order",
	"policy_front_diolk",
	"policy_front_diversification",
	"policy_front_evpalin_tunnel",
	"policy_front_gold_reserve",
	"policy_front_gradualism",
	"policy_front_greek_fire",
	"policy_front_helepolis",
	"policy_front_high_tax",
	"policy_front_hire_mercenay",
	"policy_front_lighthouse",
	"policy_front_lyceum_foundation",
	"policy_front_mint",
	"policy_front_oracle",
	"policy_front_ostracism",
	"policy_front_painter_standing",
	"policy_front_peripter",
	"policy_front_persia",
	"policy_front_power",
	"policy_front_proscenium",
	"policy_front_public_market",
	"policy_front_rare_collection",
	"policy_front_reform",
	"policy_front_rivalvary",
	"policy_front_science_respect",
	"policy_front_silver_mine",
	"policy_front_soviet",
	"policy_front_stadium",
	"policy_front_statue_hall",
	"policy_front_stone_mine",
	"policy_front_supplies_from_overseas",
	"policy_front_western_gifts",
	"policy_front_amnesty_for_socrat"
};

PolicyEffect g_nullEffect{ PoliciesType::policy_unknown, 0, 0, 0, 0, [](PlayerLogic&) {} };
PolicyTemplate g_unknown{ PoliciesType::policy_unknown, g_nullEffect, PolicyType::Single };

const PolicyTemplate& GetPolicyTemplate(PoliciesType policy) {
    if (policy == PoliciesType::policy_unknown)
		return g_unknown;

	auto& tmp = g_policyTemplates[(int)policy];
	assert(tmp.GetType() == policy);
	return tmp;
}

const std::string& PolicyTemplate::GetName() const {
	return tr(g_policyNames[(int)GetType()]);
}

const std::string& PolicyTemplate::GetDescription() const {
	return tr(g_policyDescriptions[(int)GetType()]);
}