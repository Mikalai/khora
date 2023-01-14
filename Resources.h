#pragma once

#include <array>
#include <string>
#include <tuple>
#include <Platform/NumberConverter.h>
#include <GlobalEventType.h>
#include <DiscoveryType.h>
#include <ActionType.h>
#include <Policies.h>
#include <Assets/Names.h>

enum class PolicySelectionReasonType {
	Activate,
	Drop
};

const bool DefaultSelect = false;

enum Cities {
    city_unknown = -1,
    city_milet,
    city_thebes,
    city_sparta,
    city_olymp,
    city_corinth,
    city_athens,
    city_argos,
    cities_end,
    cities_count = cities_end
};

const std::string str_loc_city[]{
    str_loc_city_1,
    str_loc_city_2,
    str_loc_city_3,
    str_loc_city_4,
};

const std::string str_loc_economy[] = {
    str_loc_economy_1,
    str_loc_economy_2,
    str_loc_economy_3,
    str_loc_economy_4,
    str_loc_economy_5,
    str_loc_economy_6,
    str_loc_economy_7,
};

const std::string str_loc_culture[] = {
    str_loc_culture_1,
    str_loc_culture_2,
    str_loc_culture_3,
    str_loc_culture_4,
    str_loc_culture_5,
    str_loc_culture_6,
    str_loc_culture_7,
};

const std::string str_loc_army[] = {
    str_loc_army_1,
    str_loc_army_2,
    str_loc_army_3,
    str_loc_army_4,
    str_loc_army_5,
    str_loc_army_6,
    str_loc_army_7,
};

const std::string str_city_material[cities_count] = {
    str_city_material_milet,
    str_city_material_thebes,
    str_city_material_sparta,
    str_city_material_olymp,
    str_city_material_corinth,
    str_city_material_athens,
    str_city_material_argos
};

enum player_color {
    player_color_unknown = -1,
    red,
    green,
    black,
    blue,
    players_end,
    players_count = players_end
};

const std::string str_player_location[players_count] = {
    str_player_0_location,
    str_player_1_location,
    str_player_2_location,
    str_player_3_location
};

const std::string str_achieve_points_material[players_count] = {
    str_red_achieve_points,
    str_green_achieve_points,
    str_black_achieve_points,
    str_blue_achieve_points
};

const std::string str_achieve_population_material[players_count] = {
    str_red_achieve_population,
    str_green_achieve_population,
    str_black_achieve_population,
    str_blue_achieve_population
};

const std::string str_achieve_army_material[players_count] = {
    str_red_achieve_army,
    str_green_achieve_army,
    str_black_achieve_army,
    str_blue_achieve_army,
};

const std::string str_achieve_economy_material[players_count] = {
    str_red_achieve_economy,
    str_green_achieve_economy,
    str_black_achieve_economy,
    str_blue_achieve_economy,
};

const std::string str_achieve_policy_material[players_count] = {
    str_red_achieve_policy,
    str_green_achieve_policy,
    str_black_achieve_policy,
    str_blue_achieve_policy,
};

const std::string str_mark_90_material[players_count] = {
    str_red_mark_90,
    str_green_mark_90,
    str_black_mark_90,
    str_blue_mark_90,
};

const std::string str_dice_material[players_count] = {
    str_red_dice,
    str_green_dice,
    str_black_dice,
    str_blue_dice
};

const std::string str_city_level_material[players_count] = {
    str_red_city,
    str_green_city,
    str_black_city,
    str_blue_city,
};

const std::string str_economy_material[players_count] = {
    str_red_economy,
    str_green_economy,
    str_black_economy,
    str_blue_economy,
};

const std::string str_culture_material[players_count] = {
    str_red_culture,
    str_green_culture,
    str_black_culture,
    str_blue_culture,
};

const std::string str_military_material[players_count] = {
    str_red_military,
    str_green_military,
    str_black_military,
    str_blue_military,
};

const std::string str_population_material[players_count] = {
    str_red_population,
    str_green_population,
    str_black_population,
    str_blue_population,
};

const std::string str_army_material[players_count] = {
    str_red_army,
    str_green_army,
    str_black_army,
    str_blue_army,
};

const std::string str_glory_material[players_count] = {
    str_red_glory,
    str_green_glory,
    str_black_glory,
    str_blue_glory,
};

const std::string str_points_material[players_count] = {
    str_red_points,
    str_green_points,
    str_black_points,
    str_blue_points,
};

const std::string str_tax_material[players_count] = {
    str_red_tax,
    str_green_tax,
    str_black_tax,
    str_blue_tax,
};

const std::array<std::string, players_count> str_action_0_philosophy_material = {
    str_red_action_0_philosophy,
    str_green_action_0_philosophy,
    str_black_action_0_philosophy,
    str_blue_action_0_philosophy,
};

const std::array<std::string, players_count> str_action_1_law_material = {
    str_red_action_1_law,
    str_green_action_1_law,
    str_black_action_1_law,
    str_blue_action_1_law
};

const std::array<std::string, players_count> str_action_2_culture_material = {
    str_red_action_2_culture,
    str_green_action_2_culture,
    str_black_action_2_culture,
    str_blue_action_2_culture,
};

const std::array<std::string, players_count> str_action_3_trade_material = {
    str_red_action_3_trade,
    str_green_action_3_trade,
    str_black_action_3_trade,
    str_blue_action_3_trade,
};

const std::array<std::string, players_count> str_action_4_military_material = {
    str_red_action_4_military,
    str_green_action_4_military,
    str_black_action_4_military,
    str_blue_action_4_military,
};

const std::array<std::string, players_count> str_action_5_policy_material = {
    str_red_action_5_policy,
    str_green_action_5_policy,
    str_black_action_5_policy,
    str_blue_action_5_policy,
};

const std::array<std::string, players_count> str_action_6_development_material = {
    str_red_action_6_development,
    str_green_action_6_development,
    str_black_action_6_development,
    str_blue_action_6_development,
};

const std::string str_action_back_material[players_count] = {
    str_red_action_back,
    str_green_action_back,
    str_black_action_back,
    str_blue_action_back,
};

enum class PolicyType {
    Single,
    Multiple,
    EndGame,
    Count
};

const std::string str_policy_front_materials[As<int>(PolicyType::Count)] = {
    str_policy_single,
    str_policy_multiple,
    str_policy_end
};

const std::string str_policy_images[As<int>(Policies::policies_count)] = {
    str_policy_old_guard_image,
    str_policy_archives_image,
    str_policy_asket_image,
    str_policy_bank_image,
    str_policy_central_government_image,
    str_policy_coloss_image,
    str_policy_contribution_image,
    str_policy_corinth_order_image,
    str_policy_diolk_image,
    str_policy_diversification_image,
    str_policy_evpalin_tunnel_image,
    str_policy_gold_reserve_image,
    str_policy_gradualism_image,
    str_policy_greece_fire_image,
    str_policy_helepolis_image,
    str_policy_high_tax_image,
    str_policy_hire_mercenary_image,
    str_policy_lighthouse_image,
    str_policy_lyceum_foundation_image,
    str_policy_mint_image,
    str_policy_oracle_image,
    str_policy_ostracism_image,
    str_policy_painter_standing_image,
    str_policy_peripter_image,
    str_policy_persia_image,
    str_policy_power_image,
    str_policy_proscenuim_image,
    str_policy_public_market_image,
    str_policy_rare_collection_image,
    str_policy_reform_image,
    str_policy_rivalvary_image,
    str_policy_science_respect_image,
    str_policy_silver_mine_image,
    str_policy_soviet_image,
    str_policy_stadium_image,
    str_policy_statue_hall_image,
    str_policy_stone_mine_image,
    str_policy_supplies_from_overseas_image,
    str_policy_western_gifts_image,
    str_policy_amnesty_for_socrat_image,
};

const int max_points_locations = 90;
const int max_population_locations = 16;
const int max_army_locations = 16;
const int max_tax_locations = 11;
const int max_glory_locations = 11;
const int max_tax_level = 10;
const int max_population_level = 15;
const int max_glory_level = 10;
const int max_city_levels = 4;
const int max_city_track_level = 7;
const int max_city_track_upgrades = 6;
const int max_army_level = 15;

const std::tuple<discovery_type, std::string> str_cur_discovery[]{
    {discovery_type::red, str_cur_discovery_red_2_1},
    {discovery_type::red, str_cur_discovery_red_3_0},
    {discovery_type::red, str_cur_discovery_red_2_2},
    {discovery_type::red, str_cur_discovery_red_3_1},
    {discovery_type::red,str_cur_discovery_red_4_2},
    {discovery_type::red,str_cur_discovery_red_5_1},
    {discovery_type::epic_red, str_cur_discovery_red_5_4},
    {discovery_type::epic_red,str_cur_discovery_red_6_3},
    {discovery_type::epic_red,str_cur_discovery_red_7_5},
    {discovery_type::epic_red,str_cur_discovery_red_8_6},
    {discovery_type::epic_red,str_cur_discovery_red_9_8},
    {discovery_type::blue, str_cur_discovery_blue_2_2},
    {discovery_type::blue,str_cur_discovery_blue_3_1},
    {discovery_type::blue,str_cur_discovery_blue_3_3},
    {discovery_type::blue,str_cur_discovery_blue_4_2},
    {discovery_type::epic_blue,str_cur_discovery_blue_4_4},
    {discovery_type::epic_blue,str_cur_discovery_blue_5_3},
    {discovery_type::epic_blue,str_cur_discovery_blue_6_5},
    {discovery_type::epic_blue,str_cur_discovery_blue_6_5_b},
    {discovery_type::epic_blue,str_cur_discovery_blue_7_6},
    {discovery_type::epic_blue,str_cur_discovery_blue_8_7},
    {discovery_type::epic_blue,str_cur_discovery_blue_9_9},
    {discovery_type::green,str_cur_discovery_green_2_1},
    {discovery_type::green,str_cur_discovery_green_3_0},
    {discovery_type::green,str_cur_discovery_green_2_2},
    {discovery_type::green,str_cur_discovery_green_3_1},
    {discovery_type::green,str_cur_discovery_green_4_2},
    {discovery_type::green,str_cur_discovery_green_5_1},
    {discovery_type::epic_green,str_cur_discovery_green_5_4},
    {discovery_type::epic_green,str_cur_discovery_green_6_3},
    {discovery_type::epic_green,str_cur_discovery_green_7_5},
    {discovery_type::epic_green,str_cur_discovery_green_8_6},
    {discovery_type::epic_green,str_cur_discovery_green_9_8},
    {discovery_type::epic_red,str_cur_discovery_red_persipolis},
    {discovery_type::epic_blue,str_cur_discovery_blue_persipolis},
    {discovery_type::epic_green,str_cur_discovery_green_persipolis}
};

const int max_expedition_discoveries = sizeof(str_cur_discovery) / sizeof(str_cur_discovery[0]);

enum achieves {
    achieve_points,
    achieve_population,
    achieve_army,
    achieve_economy,
    achieve_policy,
    end,
    achieves_count = end
};

const std::string str_cur_achieve[] = {
    str_cur_achieve_points,
    str_cur_achieve_population,
    str_cur_achieve_army,
    str_cur_achieve_economy,
    str_cur_achieve_policy,
};

const std::string str_discovery_type[]{
    str_discovery_red,
    str_discovery_blue,
    str_discovery_green,
    str_discovery_red_epic,
    str_discovery_blue_epic,
    str_discovery_green_epic
};

enum class ProgressTrackType {
    Unknown = -1,
	Any = -1,
	Economy,
	Culture,
	Military,
    Count
};


const int POLICY_CORINTHIAN_ORDER_COST = 0;
const int POLICY_CORINTHIAN_ORDER_RED = 0;
const int POLICY_CORINTHIAN_ORDER_BLUE = 0;
const int POLICY_CORINTHIAN_ORDER_GREEN = 0;
const int POLICY_CORINTHIAN_ORDER_DISCOVERY_PRICE = 3;

const int POLICY_DIOLK_COST = 0;
const int POLICY_DIOLK_RED = 1;
const int POLICY_DIOLK_BLUE = 0;
const int POLICY_DIOLK_GREEN = 0;
const int POLICY_DIOLK_ADD_MONEY = 1;
const int POLICY_DIOLK_ADD_ARMY = 1;
const int POLICY_DIOLK_ADD_POINTS = 1;


const int POLICY_DIVERSIFICATION_COST = 6;
const int POLICY_DIVERSIFICATION_RED = 1;
const int POLICY_DIVERSIFICATION_BLUE = 1;
const int POLICY_DIVERSIFICATION_GREEN = 1;

const int POLICY_EVPALIN_TUNNEL_COST = 4;
const int POLICY_EVPALIN_TUNNEL_RED = 0;
const int POLICY_EVPALIN_TUNNEL_BLUE = 0;
const int POLICY_EVPALIN_TUNNEL_GREEN = 0;
const int POLICY_EVPALIN_TUNNEL_ADD_POINTS = 6;

const int POLICY_GOLD_RESERVE_COST = 8;
const int POLICY_GOLD_RESERVE_RED = 3;
const int POLICY_GOLD_RESERVE_BLUE = 0;
const int POLICY_GOLD_RESERVE_GREEN = 0;

const int POLICY_GRADUALISM_COST = 0;
const int POLICY_GRADUALISM_RED = 0;
const int POLICY_GRADUALISM_BLUE = 0;
const int POLICY_GRADUALISM_GREEN = 1;
const int POLICY_GRADUALISM_COST_DISCONT = 1;

const int POLICY_GREEK_FIRE_COST = 0;
const int POLICY_GREEK_FIRE_RED = 0;
const int POLICY_GREEK_FIRE_BLUE = 1;
const int POLICY_GREEK_FIRE_GREEN = 0;
const int POLICY_GREEK_FIRE_ADD_ARMY = 4;

const int POLICY_HELEPOLIS_COST = 1;
const int POLICY_HELEPOLIS_RED = 0;
const int POLICY_HELEPOLIS_BLUE = 1;
const int POLICY_HELEPOLIS_GREEN = 0;
const int POLICY_HELEPOLIS_EXPEDISION_LOSE_DISCONT = 1;

const int POLICY_HIGH_TAX_COST = 4;
const int POLICY_HIGH_TAX_RED = 2;
const int POLICY_HIGH_TAX_BLUE = 0;
const int POLICY_HIGH_TAX_GREEN = 2;

const int POLICY_HIRE_MERCENAY_COST = 0;
const int POLICY_HIRE_MERCENAY_RED = 1;
const int POLICY_HIRE_MERCENAY_BLUE = 0;
const int POLICY_HIRE_MERCENAY_GREEN = 0;

const int POLICY_LIGHTHOUSE_COST = 1;
const int POLICY_LIGHTHOUSE_RED = 1;
const int POLICY_LIGHTHOUSE_BLUE = 0;
const int POLICY_LIGHTHOUSE_GREEN = 0;
const int POLICY_LIGHTHOUSE_ADD_POINTS = 3;

const int POLICY_LYCEUM_FOUNDATION_COST = 3;
const int POLICY_LYCEUM_FOUNDATION_RED = 0;
const int POLICY_LYCEUM_FOUNDATION_BLUE = 0;
const int POLICY_LYCEUM_FOUNDATION_GREEN = 0;
const int POLICY_LYCEUM_FOUNDATION_ADD_PHILOSOPHY = 3;

const int POLICY_MINT_COST = 2;
const int POLICY_MINT_RED = 2;
const int POLICY_MINT_BLUE = 0;
const int POLICY_MINT_GREEN = 0;

const int POLICY_OLD_GUARD_COST = 0;
const int POLICY_OLD_GUARD_RED = 1;
const int POLICY_OLD_GUARD_BLUE = 0;
const int POLICY_OLD_GUARD_GREEN = 1;
const int POLICY_OLD_GUARD_ADD_POINTS = 4;

const int POLICY_ORACLE_COST = 3;
const int POLICY_ORACLE_RED = 1;
const int POLICY_ORACLE_BLUE = 1;
const int POLICY_ORACLE_GREEN = 1;
const int POLICY_ORACLE_ADD_POINTS = 4;

const int POLICY_OSTRACISM_COST = 3;
const int POLICY_OSTRACISM_RED = 0;
const int POLICY_OSTRACISM_BLUE = 0;
const int POLICY_OSTRACISM_GREEN = 0;

const int POLICY_PAINTER_STANDING_COST = 0;
const int POLICY_PAINTER_STANDING_RED = 0;
const int POLICY_PAINTER_STANDING_BLUE = 0;
const int POLICY_PAINTER_STANDING_GREEN = 1;
const int POLICY_PAINTER_STANDING_ADD_POINTS = 2;

const int POLICY_PERIPTER_COST = 1;
const int POLICY_PERIPTER_RED = 0;
const int POLICY_PERIPTER_BLUE = 0;
const int POLICY_PERIPTER_GREEN = 2;
const int POLICY_PERIPTER_ADD_CULTURE = 1;

const int POLICY_PERSIANS_COST = 0;
const int POLICY_PERSIANS_RED = 0;
const int POLICY_PERSIANS_BLUE = 1;
const int POLICY_PERSIANS_GREEN = 1;
const int POLICY_PERSIANS_ADD_ARMY = 2;

const int POLICY_POWER_COST = 0;
const int POLICY_POWER_RED = 1;
const int POLICY_POWER_BLUE = 1;
const int POLICY_POWER_GREEN = 0;
const int POLICY_POWER_ADD_POINTS = 4;

const int POLICY_PROSCENIUM_COST = 0;
const int POLICY_PROSCENIUM_RED = 0;
const int POLICY_PROSCENIUM_BLUE = 2;
const int POLICY_PROSCENIUM_GREEN = 0;

const int POLICY_PUBLIC_MARKET_COST = 3;
const int POLICY_PUBLIC_MARKET_RED = 1;
const int POLICY_PUBLIC_MARKET_BLUE = 0;
const int POLICY_PUBLIC_MARKET_GREEN = 0;
const int POLICY_PUBLIC_MARKET_ADD_POINTS = 3;

const int POLICY_RARE_COLLECTION_COST = 0;
const int POLICY_RARE_COLLECTION_RED = 1;
const int POLICY_RARE_COLLECTION_BLUE = 0;
const int POLICY_RARE_COLLECTION_GREEN = 0;
const int POLICY_RARE_COLLECTION_ADD_MONEY = 2;

const int POLICY_REFORM_COST = 0;
const int POLICY_REFORM_RED = 1;
const int POLICY_REFORM_BLUE = 1;
const int POLICY_REFORM_GREEN = 1;

const int POLICY_RIVALVARY_COST = 0;
const int POLICY_RIVALVARY_RED = 0;
const int POLICY_RIVALVARY_BLUE = 0;
const int POLICY_RIVALVARY_GREEN = 0;

const int POLICY_SCIENCE_RESPECT_COST = 2;
const int POLICY_SCIENCE_RESPECT_RED = 0;
const int POLICY_SCIENCE_RESPECT_BLUE = 0;
const int POLICY_SCIENCE_RESPECT_GREEN = 0;
const int POLICY_SCIENCE_RESPECT_ADD_DISCOVERY = 1;

const int POLICY_SILVER_MINE_COST = 3;
const int POLICY_SILVER_MINE_RED = 1;
const int POLICY_SILVER_MINE_BLUE = 0;
const int POLICY_SILVER_MINE_GREEN = 0;
const int POLICY_SILVER_MINE_ADD_TAX = 2;

const int POLICY_SOVIET_COST = 0;
const int POLICY_SOVIET_RED = 0;
const int POLICY_SOVIET_BLUE = 0;
const int POLICY_SOVIET_GREEN = 0;
const int POLICY_SOVIET_POLICIES_COUNT = 2;

const int POLICY_STADIUM_COST = 2;
const int POLICY_STADIUM_RED = 0;
const int POLICY_STADIUM_BLUE = 2;
const int POLICY_STADIUM_GREEN = 0;
const int POLICY_STADIUM_ADD_ARMY = 2;

const int POLICY_STATUE_HALL_COST = 2;
const int POLICY_STATUE_HALL_RED = 1;
const int POLICY_STATUE_HALL_BLUE = 1;
const int POLICY_STATUE_HALL_GREEN = 1;

const int POLICY_STONE_MINE_COST = 0;
const int POLICY_STONE_MINE_RED = 1;
const int POLICY_STONE_MINE_BLUE = 0;
const int POLICY_STONE_MINE_GREEN = 0;
const int POLICY_STONE_MINE_ADD_TAX = 1;

const int POLICY_SUPPLIES_FROM_OVERSEAS_COST = 2;
const int POLICY_SUPPLIES_FROM_OVERSEAS_RED = 0;
const int POLICY_SUPPLIES_FROM_OVERSEAS_BLUE = 0;
const int POLICY_SUPPLIES_FROM_OVERSEAS_GREEN = 0;
const int POLICY_SUPPLIES_FROM_OVERSEAS_ADD_ARMY = 2;

const int POLICY_AMNESTY_FOR_SOCRAT_COST = 2;
const int POLICY_AMNESTY_FOR_SOCRAT_RED = 0;
const int POLICY_AMNESTY_FOR_SOCRAT_BLUE = 0;
const int POLICY_AMNESTY_FOR_SOCRAT_GREEN = 0;
const int POLICY_AMNESTY_FOR_SOCRAT_ADD_PHILOSOPHY = 1;

const int POLICY_ARCHIVES_COST = 2;
const int POLICY_ARCHIVES_RED = 0;
const int POLICY_ARCHIVES_BLUE = 0;
const int POLICY_ARCHIVES_GREEN = 0;
const int POLICY_ARCHIVES_ADD_PHILOSOPHY = 3;


const int POLICY_ASKET_COST = 6;
const int POLICY_ASKET_RED = 0;
const int POLICY_ASKET_BLUE = 0;
const int POLICY_ASKET_GREEN = 3;

const int POLICY_BANK_COST = 0;
const int POLICY_BANK_RED = 2;
const int POLICY_BANK_BLUE = 0;
const int POLICY_BANK_GREEN = 0;

const int POLICY_CENTRAL_GOVERNMENT_COST = 4;
const int POLICY_CENTRAL_GOVERNMENT_RED = 0;
const int POLICY_CENTRAL_GOVERNMENT_BLUE = 0;
const int POLICY_CENTRAL_GOVERNMENT_GREEN = 2;

const int POLICY_COLOSS_COST = 6;
const int POLICY_COLOSS_RED = 1;
const int POLICY_COLOSS_BLUE = 1;
const int POLICY_COLOSS_GREEN = 1;
const int POLICY_COLOSS_ADD_POINTS = 10;

const int POLICY_CONTRIBUTION_COST = 0;
const int POLICY_CONTRIBUTION_RED = 0;
const int POLICY_CONTRIBUTION_BLUE = 1;
const int POLICY_CONTRIBUTION_GREEN = 0;

const std::string str_event_material[(int)GlobalEventType::Count]{
    str_event_population_growth,
    str_event_greece_savers,
    str_event_invent_trirema,
    str_event_military_call,
    str_event_military_superior,
    str_event_persia_prosper,
    str_event_prosperity,
    str_event_supply_from_india,
    str_event_war,
    str_event_30_tirans,
    str_event_athine_plague,
    str_event_delphi_oracle,
    str_event_drought,
    str_event_eleusinia_mystery,
    str_event_found_academy,
    str_event_persia_campaign,
};

enum class RoundStageType {
    NewEvent,
    CollectTax,
    ThrowDices,
    SelectActions,
    DoActions,
    DoProgress,
    DoEvents,
    DoAchievements
};

const double card_depth = 0.0004;
// const double card_depth = 0.1;


const int STARTUP_MONEY = 4;

const bool DEBUG_POINTS_LOCATION = false;
const bool DEBUG_TAX_LOCATION = false;
const bool DEBUG_POPULATION_LOCATION = false;
const bool DEBUG_GLORY_LOCATION = false;
const bool DEBUG_ARMY_LOCATION = false;
const bool DEBUG_POLICIES_DECK = false;
const bool DEBUG_CLOSE_EVENTS_DECK = false;
const bool DEBUG_OPEN_EVENTS_DECK = false;
const bool DEBUG_PLAYER_LOCATION = false;
const bool DEBUG_CITY_LOCATION = false;

const double TRACK_PLAYER_OFFSET = 0.014;
const double ANIMATION_SPEED = 0.1;
const double DICE_OFFSET = 0.06;
const double PHILOSOPHY_OFFSET = 0.01;
const double POLICY_CARD_OFFSET = 0.08;
const double POLICY_CARD_ACTIVE_OFFSET = 0.04;

const std::array<std::string, (int)ActionType::Count> ActionToString = {
    "Philosophy",
    "Law",
    "Culture",
    "Trade",
    "Military",
    "Policy",
    "Development",
};

const std::array<const std::array<std::string, 4>, (int)ActionType::Count> str_action_front_material{
    str_action_0_philosophy_material,
    str_action_1_law_material,
    str_action_2_culture_material,
    str_action_3_trade_material,
    str_action_4_military_material,
    str_action_5_policy_material,
    str_action_6_development_material
};

const int LAW_ACTION_POPULATION_GROWTH = 3;

const std::string str_cur_population_prefix = "cur_population_";