#pragma once

#include <array>
#include <string>
#include <tuple>
#include <Platform/NumberConverter.h>
#include <GlobalEventType.h>
#include <DiscoveryType.h>
#include <ActionType.h>
#include <Policies.h>

enum class PolicySelectionReasonType {
	Activate,
	Drop
};

const bool DefaultSelect = false;
const std::string str_cur_points = "cur_points";
const std::string str_board = "board";
const std::string str_board_material = "board";
const std::string str_table_material = "table";
const std::string str_cur_board = "cur_board";
const std::string str_tablet = "tablet_material_black";
const std::string str_table = "table";
const std::string str_first_philosophy_offset = "first_philosophy_offset";
const std::string str_first_dice_location = "first_dice_location";
const std::string str_first_action_card = "first_action_card";
const std::string str_first_discovery_offset = "first_discovery_offset";
const std::string str_policies_activated_first_location = "policies_activated_first_location";
const std::string str_policies_in_hand_first_location = "policies_in_hand_first_location";
const std::string str_policies_deck = "policies_deck";
const std::string str_events_deck_close = "events_deck_close";
const std::string str_events_deck_open = "events_deck_open";
const std::string str_event_back_material = "event_back_material";
const std::string str_event_front = "event_front";
const std::string str_event_back = "event_back";
const std::string str_city_location = "loc_city";
const std::string str_coin_5 = "coin_5";
const std::string str_coin_1 = "coin_1";
const std::string str_coin_first_location = "coin_first_location";
const std::string str_philosophy = "philosophy";
const std::string str_coin_5_material = "coin_5";
const std::string str_coin_1_material = "coin_1";
const std::string str_philosophy_material = "philosophy";
const std::string str_policy_front = "policy_front_silver_mine";
const std::string str_policy_back = "policy_back";
const std::string str_policy_back_material = "policy_back_material";
const std::string str_city_card = "city_material_milet";
const std::string str_city_material_milet = "city_material_milet";
const std::string str_city_material_thebes = "city_material_thebes";
const std::string str_city_material_sparta = "city_material_sparta";
const std::string str_city_material_olymp = "city_material_olymp";
const std::string str_city_material_corinth = "city_material_corinth";
const std::string str_city_material_athens = "city_material_athens";
const std::string str_city_material_argos = "city_material_argos";

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

const std::string str_loc_city_1 = "loc_city_1";
const std::string str_loc_city_2 = "loc_city_2";
const std::string str_loc_city_3 = "loc_city_3";
const std::string str_loc_city_4 = "loc_city_4";

const std::string str_loc_city[]{
    str_loc_city_1,
    str_loc_city_2,
    str_loc_city_3,
    str_loc_city_4,
};

const std::string str_loc_dice_3 = "loc_dice_3";

const std::string str_loc_economy_1 = "loc_economy_1";
const std::string str_loc_economy_2 = "loc_economy_2";
const std::string str_loc_economy_3 = "loc_economy_3";
const std::string str_loc_economy_4 = "loc_economy_4";
const std::string str_loc_economy_5 = "loc_economy_5";
const std::string str_loc_economy_6 = "loc_economy_6";
const std::string str_loc_economy_7 = "loc_economy_7";

const std::string str_loc_economy[] = {
    str_loc_economy_1,
    str_loc_economy_2,
    str_loc_economy_3,
    str_loc_economy_4,
    str_loc_economy_5,
    str_loc_economy_6,
    str_loc_economy_7,
};

const std::string str_loc_culture_1 = "loc_culture_1";
const std::string str_loc_culture_2 = "loc_culture_2";
const std::string str_loc_culture_3 = "loc_culture_3";
const std::string str_loc_culture_4 = "loc_culture_4";
const std::string str_loc_culture_5 = "loc_culture_5";
const std::string str_loc_culture_6 = "loc_culture_6";
const std::string str_loc_culture_7 = "loc_culture_7";

const std::string str_loc_culture[] = {
    str_loc_culture_1,
    str_loc_culture_2,
    str_loc_culture_3,
    str_loc_culture_4,
    str_loc_culture_5,
    str_loc_culture_6,
    str_loc_culture_7,
};

const std::string str_loc_army_1 = "loc_army_1";
const std::string str_loc_army_2 = "loc_army_2";
const std::string str_loc_army_3 = "loc_army_3";
const std::string str_loc_army_4 = "loc_army_4";
const std::string str_loc_army_5 = "loc_army_5";
const std::string str_loc_army_6 = "loc_army_6";
const std::string str_loc_army_7 = "loc_army_7";

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

const std::string str_tablet_material_black = "tablet_material_black";
const std::string str_tablet_material_blue = "tablet_material_blue";
const std::string str_tablet_material_red = "tablet_material_red";
const std::string str_tablet_material_green = "tablet_material_green";

const std::string str_tablet_material[players_count] = {
    str_tablet_material_red,
    str_tablet_material_green,
    str_tablet_material_black,
    str_tablet_material_blue
};

const std::string str_player_0_location = "player_0_location";
const std::string str_player_1_location = "player_1_location";
const std::string str_player_2_location = "player_2_location";
const std::string str_player_3_location = "player_3_location";

const std::string str_player_location[players_count] = {
    str_player_0_location,
    str_player_1_location,
    str_player_2_location,
    str_player_3_location
};

const std::string str_red_achieve_points = "red_achieve_points";
const std::string str_green_achieve_points = "green_achieve_points";
const std::string str_black_achieve_points = "black_achieve_points";
const std::string str_blue_achieve_points = "blue_achieve_points";

const std::string str_achieve_points_material[players_count] = {
    str_red_achieve_points,
    str_green_achieve_points,
    str_black_achieve_points,
    str_blue_achieve_points
};

const std::string str_red_achieve_population = "red_achieve_population";
const std::string str_green_achieve_population = "green_achieve_population";
const std::string str_black_achieve_population = "black_achieve_population";
const std::string str_blue_achieve_population = "blue_achieve_population";

const std::string str_achieve_population_material[players_count] = {
    str_red_achieve_population,
    str_green_achieve_population,
    str_black_achieve_population,
    str_blue_achieve_population
};

const std::string str_red_achieve_army = "red_achieve_army";
const std::string str_green_achieve_army = "green_achieve_army";
const std::string str_black_achieve_army = "black_achieve_army";
const std::string str_blue_achieve_army = "blue_achieve_army";

const std::string str_achieve_army_material[players_count] = {
    str_red_achieve_army,
    str_green_achieve_army,
    str_black_achieve_army,
    str_blue_achieve_army,
};

const std::string str_red_achieve_economy = "red_achieve_economy";
const std::string str_green_achieve_economy = "green_achieve_economy";
const std::string str_black_achieve_economy = "black_achieve_economy";
const std::string str_blue_achieve_economy = "blue_achieve_economy";

const std::string str_achieve_economy_material[players_count] = {
    str_red_achieve_economy,
    str_green_achieve_economy,
    str_black_achieve_economy,
    str_blue_achieve_economy,
};

const std::string str_red_achieve_policy = "red_achieve_policy";
const std::string str_green_achieve_policy = "green_achieve_policy";
const std::string str_black_achieve_policy = "black_achieve_policy";
const std::string str_blue_achieve_policy = "blue_achieve_policy";

const std::string str_achieve_policy_material[players_count] = {
    str_red_achieve_policy,
    str_green_achieve_policy,
    str_black_achieve_policy,
    str_blue_achieve_policy,
};

const std::string str_red_mark_90 = "red_mark_90";
const std::string str_green_mark_90 = "green_mark_90";
const std::string str_black_mark_90 = "black_mark_90";
const std::string str_blue_mark_90 = "blue_mark_90";

const std::string str_mark_90_material[players_count] = {
    str_red_mark_90,
    str_green_mark_90,
    str_black_mark_90,
    str_blue_mark_90,
};

const std::string str_red_dice = "red_dice";
const std::string str_green_dice = "green_dice";
const std::string str_black_dice = "black_dice";
const std::string str_blue_dice = "blue_dice";

const std::string str_dice_material[players_count] = {
    str_red_dice,
    str_green_dice,
    str_black_dice,
    str_blue_dice
};

const std::string str_red_city = "red_city";
const std::string str_green_city = "green_city";
const std::string str_black_city = "black_city";
const std::string str_blue_city = "blue_city";

const std::string str_city_level_material[players_count] = {
    str_red_city,
    str_green_city,
    str_black_city,
    str_blue_city,
};

const std::string str_red_economy = "red_economy";
const std::string str_green_economy = "green_economy";
const std::string str_black_economy = "black_economy";
const std::string str_blue_economy = "blue_economy";

const std::string str_economy_material[players_count] = {
    str_red_economy,
    str_green_economy,
    str_black_economy,
    str_blue_economy,
};

const std::string str_red_culture = "red_culture";
const std::string str_green_culture = "green_culture";
const std::string str_black_culture = "black_culture";
const std::string str_blue_culture = "blue_culture";

const std::string str_culture_material[players_count] = {
    str_red_culture,
    str_green_culture,
    str_black_culture,
    str_blue_culture,
};

const std::string str_red_military = "red_military";
const std::string str_green_military = "green_military";
const std::string str_black_military = "black_military";
const std::string str_blue_military = "blue_military";

const std::string str_military_material[players_count] = {
    str_red_military,
    str_green_military,
    str_black_military,
    str_blue_military,
};

const std::string str_red_population = "red_population";
const std::string str_green_population = "green_population";
const std::string str_black_population = "black_population";
const std::string str_blue_population = "blue_population";

const std::string str_population_material[players_count] = {
    str_red_population,
    str_green_population,
    str_black_population,
    str_blue_population,
};

const std::string str_red_army = "red_army";
const std::string str_green_army = "green_army";
const std::string str_black_army = "black_army";
const std::string str_blue_army = "blue_army";

const std::string str_army_material[players_count] = {
    str_red_army,
    str_green_army,
    str_black_army,
    str_blue_army,
};

const std::string str_red_glory = "red_glory";
const std::string str_green_glory = "green_glory";
const std::string str_black_glory = "black_glory";
const std::string str_blue_glory = "blue_glory";

const std::string str_glory_material[players_count] = {
    str_red_glory,
    str_green_glory,
    str_black_glory,
    str_blue_glory,
};

const std::string str_red_points = "red_points";
const std::string str_green_points = "green_points";
const std::string str_black_points = "black_points";
const std::string str_blue_points = "blue_points";

const std::string str_points_material[players_count] = {
    str_red_points,
    str_green_points,
    str_black_points,
    str_blue_points,
};

const std::string str_red_tax = "red_tax";
const std::string str_green_tax = "green_tax";
const std::string str_black_tax = "black_tax";
const std::string str_blue_tax = "blue_tax";

const std::string str_tax_material[players_count] = {
    str_red_tax,
    str_green_tax,
    str_black_tax,
    str_blue_tax,
};

const std::string str_red_action_0_philosophy = "red_action_0_philosophy";
const std::string str_green_action_0_philosophy = "green_action_0_philosophy";
const std::string str_black_action_0_philosophy = "black_action_0_philosophy";
const std::string str_blue_action_0_philosophy = "blue_action_0_philosophy";

const std::array<std::string, players_count> str_action_0_philosophy_material = {
    str_red_action_0_philosophy,
    str_green_action_0_philosophy,
    str_black_action_0_philosophy,
    str_blue_action_0_philosophy,
};

const std::string str_red_action_1_law = "red_action_1_law";
const std::string str_green_action_1_law = "green_action_1_law";
const std::string str_black_action_1_law = "black_action_1_law";
const std::string str_blue_action_1_law = "blue_action_1_law";

const std::array<std::string, players_count> str_action_1_law_material = {
    str_red_action_1_law,
    str_green_action_1_law,
    str_black_action_1_law,
    str_blue_action_1_law
};

const std::string str_red_action_2_culture = "red_action_2_culture";
const std::string str_green_action_2_culture = "green_action_2_culture";
const std::string str_black_action_2_culture = "black_action_2_culture";
const std::string str_blue_action_2_culture = "blue_action_2_culture";

const std::array<std::string, players_count> str_action_2_culture_material = {
    str_red_action_2_culture,
    str_green_action_2_culture,
    str_black_action_2_culture,
    str_blue_action_2_culture,
};

const std::string str_red_action_3_trade = "red_action_3_trade";
const std::string str_green_action_3_trade = "green_action_3_trade";
const std::string str_black_action_3_trade = "black_action_3_trade";
const std::string str_blue_action_3_trade = "blue_action_3_trade";

const std::array<std::string, players_count> str_action_3_trade_material = {
    str_red_action_3_trade,
    str_green_action_3_trade,
    str_black_action_3_trade,
    str_blue_action_3_trade,
};

const std::string str_red_action_4_military = "red_action_4_military";
const std::string str_green_action_4_military = "green_action_4_military";
const std::string str_black_action_4_military = "black_action_4_military";
const std::string str_blue_action_4_military = "blue_action_4_military";

const std::array<std::string, players_count> str_action_4_military_material = {
    str_red_action_4_military,
    str_green_action_4_military,
    str_black_action_4_military,
    str_blue_action_4_military,
};

const std::string str_red_action_5_policy = "red_action_5_policy";
const std::string str_green_action_5_policy = "green_action_5_policy";
const std::string str_black_action_5_policy = "black_action_5_policy";
const std::string str_blue_action_5_policy = "blue_action_5_policy";

const std::array<std::string, players_count> str_action_5_policy_material = {
    str_red_action_5_policy,
    str_green_action_5_policy,
    str_black_action_5_policy,
    str_blue_action_5_policy,
};

const std::string str_red_action_6_development = "red_action_6_development";
const std::string str_green_action_6_development = "green_action_6_development";
const std::string str_black_action_6_development = "black_action_6_development";
const std::string str_blue_action_6_development = "blue_action_6_development";

const std::array<std::string, players_count> str_action_6_development_material = {
    str_red_action_6_development,
    str_green_action_6_development,
    str_black_action_6_development,
    str_blue_action_6_development,
};

const std::string str_red_action_back = "red_action_back";
const std::string str_green_action_back = "green_action_back";
const std::string str_black_action_back = "black_action_back";
const std::string str_blue_action_back = "blue_action_back";

const std::string str_action_back_material[players_count] = {
    str_red_action_back,
    str_green_action_back,
    str_black_action_back,
    str_blue_action_back,
};

enum class PolicyType {
    Single,
    Multiple,
    EndGame
};

const std::string str_policy_front_old_guard = "policy_front_old_guard";
const std::string str_policy_front_archives = "policy_front_archives";
const std::string str_policy_front_asket = "policy_front_asket";
const std::string str_policy_front_bank = "policy_front_bank";
const std::string str_policy_front_central_government = "policy_front_central_government";
const std::string str_policy_front_coloss = "policy_front_coloss";
const std::string str_policy_front_contribution = "policy_front_contribution";
const std::string str_policy_front_corinth_order = "policy_front_corinth_order";
const std::string str_policy_front_diolk = "policy_front_diolk";
const std::string str_policy_front_diversification = "policy_front_diversification";
const std::string str_policy_front_evpalin_tunnel = "policy_front_evpalin_tunnel";
const std::string str_policy_front_gold_reserve = "policy_front_gold_reserve";
const std::string str_policy_front_gradualism = "policy_front_gradualism";
const std::string str_policy_front_greece_fire = "policy_front_greece_fire";
const std::string str_policy_front_helepolis = "policy_front_helepolis";
const std::string str_policy_front_high_tax = "policy_front_high_tax";
const std::string str_policy_front_hire_mercenay = "policy_front_hire_mercenay";
const std::string str_policy_front_lighthouse = "policy_front_lighthouse";
const std::string str_policy_front_lyceum_foundation = "policy_front_lyceum_foundation";
const std::string str_policy_front_mint = "policy_front_mint";
const std::string str_policy_front_oracle = "policy_front_oracle";
const std::string str_policy_front_ostracism = "policy_front_ostracism";
const std::string str_policy_front_painter_standing = "policy_front_painter_standing";
const std::string str_policy_front_peripter = "policy_front_peripter";
const std::string str_policy_front_persia = "policy_front_persia";
const std::string str_policy_front_power = "policy_front_power";
const std::string str_policy_front_proscenium = "policy_front_proscenium";
const std::string str_policy_front_public_market = "policy_front_public_market";
const std::string str_policy_front_rare_collection = "policy_front_rare_collection";
const std::string str_policy_front_reform = "policy_front_reform";
const std::string str_policy_front_rivalvary = "policy_front_rivalvary";
const std::string str_policy_front_science_respect = "policy_front_science_respect";
const std::string str_policy_front_silver_mine = "policy_front_silver_mine";
const std::string str_policy_front_soviet = "policy_front_soviet";
const std::string str_policy_front_stadium = "policy_front_stadium";
const std::string str_policy_front_statue_hall = "policy_front_statue_hall";
const std::string str_policy_front_stone_mine = "policy_front_stone_mine";
const std::string str_policy_front_supplies_from_overseas = "policy_front_supplies_from_overseas";
const std::string str_policy_front_western_gifts = "policy_front_western_gifts";
const std::string str_policy_front_amnesty_for_socrat = "policy_front_amnesty_for_socrat";

const std::string str_policy[As<int>(Policies::policies_count)] = {
    str_policy_front_old_guard,
    str_policy_front_archives,
    str_policy_front_asket,
    str_policy_front_bank,
    str_policy_front_central_government,
    str_policy_front_coloss,
    str_policy_front_contribution,
    str_policy_front_corinth_order,
    str_policy_front_diolk,
    str_policy_front_diversification,
    str_policy_front_evpalin_tunnel,
    str_policy_front_gold_reserve,
    str_policy_front_gradualism,
    str_policy_front_greece_fire,
    str_policy_front_helepolis,
    str_policy_front_high_tax,
    str_policy_front_hire_mercenay,
    str_policy_front_lighthouse,
    str_policy_front_lyceum_foundation,
    str_policy_front_mint,
    str_policy_front_oracle,
    str_policy_front_ostracism,
    str_policy_front_painter_standing,
    str_policy_front_peripter,
    str_policy_front_persia,
    str_policy_front_power,
    str_policy_front_proscenium,
    str_policy_front_public_market,
    str_policy_front_rare_collection,
    str_policy_front_reform,
    str_policy_front_rivalvary,
    str_policy_front_science_respect,
    str_policy_front_silver_mine,
    str_policy_front_soviet,
    str_policy_front_stadium,
    str_policy_front_statue_hall,
    str_policy_front_stone_mine,
    str_policy_front_supplies_from_overseas,
    str_policy_front_western_gifts,
    str_policy_front_amnesty_for_socrat,
};

const std::string str_city_level = "black_city";
const std::string str_economy = "black_economy";
const std::string str_culture = "black_culture";
const std::string str_military = "black_military";
const std::string str_population = "black_population";
const std::string str_army = "black_army";
const std::string str_glory = "black_glory";
const std::string str_points = "black_points";
const std::string str_tax = "black_tax";
const std::string str_dice = "black_dice";
const std::string str_achieve = "black_achieve_points";
const std::string str_mark_90 = "black_mark_90";
const std::string str_action_front = "black_action_0_philosophy";
const std::string str_action_back = "black_action_back";

const std::string str_discovery = "discovery";

const std::string str_discovery_red = "discovery_red";
const std::string str_discovery_blue = "discovery_blue";
const std::string str_discovery_green = "discovery_green";

const std::string str_discovery_red_epic = "discovery_red_epic";
const std::string str_discovery_blue_epic = "discovery_blue_epic";
const std::string str_discovery_green_epic = "discovery_green_epic";

const std::string str_camera = "camera_object_Orientation";

const std::string str_cur_point_prefix = "cur_points.";
const std::string str_cur_population_prefix = "cur_population_";
const std::string str_cur_tax_prefix = "cur_tax_";
const std::string str_cur_glory_prefix = "cur_glory_";
const std::string str_cur_army_prefix = "cur_army_";

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

const std::string str_cur_discovery_red_2_1 = "cur_discovery_red_2_1";
const std::string str_cur_discovery_red_3_0 = "cur_discovery_red_3_0";
const std::string str_cur_discovery_red_2_2 = "cur_discovery_red_2_2";
const std::string str_cur_discovery_red_3_1 = "cur_discovery_red_3_1";
const std::string str_cur_discovery_red_4_2 = "cur_discovery_red_4_2";
const std::string str_cur_discovery_red_5_1 = "cur_discovery_red_5_1";
const std::string str_cur_discovery_red_5_4 = "cur_discovery_red_5_4";
const std::string str_cur_discovery_red_6_3 = "cur_discovery_red_6_3";
const std::string str_cur_discovery_red_7_5 = "cur_discovery_red_7_5";
const std::string str_cur_discovery_red_8_6 = "cur_discovery_red_8_6";
const std::string str_cur_discovery_red_9_8 = "cur_discovery_red_9_8";

const std::string str_cur_discovery_blue_2_2 = "cur_discovery_blue_2_2";
const std::string str_cur_discovery_blue_3_1 = "cur_discovery_blue_3_1";
const std::string str_cur_discovery_blue_3_3 = "cur_discovery_blue_3_3";
const std::string str_cur_discovery_blue_4_2 = "cur_discovery_blue_4_2";
const std::string str_cur_discovery_blue_4_4 = "cur_discovery_blue_4_4";
const std::string str_cur_discovery_blue_5_3 = "cur_discovery_blue_5_3";
const std::string str_cur_discovery_blue_6_5 = "cur_discovery_blue_6_5";
const std::string str_cur_discovery_blue_6_5_b = "cur_discovery_blue_6_5_b";
const std::string str_cur_discovery_blue_7_6 = "cur_discovery_blue_7_6";
const std::string str_cur_discovery_blue_8_7 = "cur_discovery_blue_8_7";
const std::string str_cur_discovery_blue_9_9 = "cur_discovery_blue_9_9";

const std::string str_cur_discovery_green_2_1 = "cur_discovery_green_2_1";
const std::string str_cur_discovery_green_3_0 = "cur_discovery_green_3_0";
const std::string str_cur_discovery_green_2_2 = "cur_discovery_green_2_2";
const std::string str_cur_discovery_green_3_1 = "cur_discovery_green_3_1";
const std::string str_cur_discovery_green_4_2 = "cur_discovery_green_4_2";
const std::string str_cur_discovery_green_5_1 = "cur_discovery_green_5_1";
const std::string str_cur_discovery_green_5_4 = "cur_discovery_green_5_4";
const std::string str_cur_discovery_green_6_3 = "cur_discovery_green_6_3";
const std::string str_cur_discovery_green_7_5 = "cur_discovery_green_7_5";
const std::string str_cur_discovery_green_8_6 = "cur_discovery_green_8_6";
const std::string str_cur_discovery_green_9_8 = "cur_discovery_green_9_8";

const std::string str_cur_discovery_red_persipolis = "cur_discovery_red_persipolis";
const std::string str_cur_discovery_blue_persipolis = "cur_discovery_blue_persipolis";
const std::string str_cur_discovery_green_persipolis = "cur_discovery_green_persipolis";

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

const std::string str_cur_achieve_points = "cur_achieve_points";
const std::string str_cur_achieve_population = "cur_achieve_population";
const std::string str_cur_achieve_army = "cur_achieve_army";
const std::string str_cur_achieve_economy = "cur_achieve_economy";
const std::string str_cur_achieve_policy = "cur_achieve_policy";

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

const std::string str_PopulationGrowth = "event_population_growth";
const std::string str_MilitaryCampaignAgainstPersia = "event_persia_campaign";
const std::string str_SaviorOfGreece = "event_greece_savers";
const std::string str_InventionOfTheTrireme = "event_invent_trirema";
const std::string str_Conscription = "event_military_call";
const std::string str_MilitarySuperiority = "event_military_superior";
const std::string str_RiseOfPersia = "event_persia_prosper";
const std::string str_Prosperity = "event_prosperity";
const std::string str_DeliveriesFromLydia = "event_supply_from_india";
const std::string str_Hostilities = "event_war";
const std::string str_ThirtyTyrants = "event_30_tirans";
const std::string str_PlagueOfAthens = "event_athine_plague";
const std::string str_DelphicOracle = "event_delphi_oracle";
const std::string str_Drought = "event_drought";
const std::string str_EleusinianMysteries = "event_eleusinia_mystery";
const std::string str_TheBirthOfTheAcademy = "event_found_academy";

const std::string str_event_material[(int)GlobalEventType::Count]{
    str_PopulationGrowth ,
    str_SaviorOfGreece ,
    str_InventionOfTheTrireme ,
    str_Conscription ,
    str_MilitarySuperiority ,
    str_RiseOfPersia ,
    str_Prosperity ,
    str_DeliveriesFromLydia ,
    str_Hostilities ,
    str_ThirtyTyrants ,
    str_PlagueOfAthens ,
    str_DelphicOracle ,
    str_Drought ,
    str_EleusinianMysteries ,
    str_TheBirthOfTheAcademy ,
    str_MilitaryCampaignAgainstPersia ,
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