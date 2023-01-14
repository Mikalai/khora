#pragma once

#include <sstream>
#include "KhoraAssets.h"
#include "AssetsCompiler.h"

void KhoraAssets::FillSerializationTables(AssetsCompiler& compiler) {	
	compiler.Add(str_cur_board, &root);
	compiler.Add(str_coin_first_location, &coin_first_location_offset);
	compiler.Add(str_loc_dice_3, &loc_dice_3_offset);
	compiler.Add(str_first_dice_location, &first_dice_location);
	compiler.Add(str_first_action_card, &first_action_card);
	compiler.Add(str_first_philosophy_offset, &first_philosophy_offset);
	compiler.Add(str_first_discovery_offset, &first_discovery_offset);
	compiler.Add(str_persepolis_location, &persepolis_text_location);
	compiler.Add(str_glory_location, &glory_text_location);
	compiler.Add(str_tax_location, &tax_text_location);
	compiler.Add(str_troops_location, &troops_text_location);
	compiler.Add(str_population_location, &population_text_location);
	compiler.Add(str_dice_icon_culture_location, &dice_icon_culture_location);

	compiler.Add(str_economy_text_location, &economy_text_location);
	compiler.Add(str_culture_text_location, &culture_text_location);
	compiler.Add(str_military_text_location, &military_text_location);

	compiler.Add(str_economy_icon_location, &economy_icon_location);
	compiler.Add(str_culture_icon_location, &culture_icon_location);
	compiler.Add(str_military_power_icon_location, &military_power_icon_location);

	compiler.Add(str_board, &board_geometry);
	compiler.Add(str_coin_5, &coin_geometry);
	compiler.Add(str_policy_image, &policy_image_geometry);
	compiler.Add(str_philosophy, &philosophy_geometry);
	compiler.Add(str_economy_icon, &economy_icon_geometry);
	compiler.Add(str_culture_icon, &culture_icon_geometry);
	compiler.Add(str_military_icon, &military_icon_geometry);
	compiler.Add(str_dice_icon, &dice_icon_geometry);

	compiler.Add(str_board, &board_material);
	compiler.Add(str_table, &table_material);
	compiler.Add(str_event_back_material, &event_back_material);

	for (int i = 0; i < players_count; ++i) {
		compiler.Add(str_action_back_material[i], &action_back_materials[i]);

		for (int j = 0; j < As<int>(ActionType::Count); ++j) {
			compiler.Add(str_action_front_material[j][i], &action_front_materials[i][j]);
		}
	}

	for (int i = 0; i < max_city_track_level; ++i) {
		compiler.Add(str_loc_economy[i], &ecomony_track_offset[i]);
		compiler.Add(str_loc_culture[i], &culture_track_offset[i]);
		compiler.Add(str_loc_army[i], &military_track_offset[i]);
	}

	for (int i = 0; i < max_city_levels; ++i) {
		compiler.Add(str_loc_city[i], &city_track_offset[i]);
	}

	for (int i = 0; i < (int)GlobalEventType::Count; ++i) {
		compiler.Add(str_event_material[i], &events_materials[i]);
	}

	//for (int i = 0; i < players_count; ++i) {
	compiler.Add(str_tablet, &tablet_materials);
	//}

	for (int i = 0; i < players_count; ++i) {
		compiler.Add(str_player_location[i], &players_tablet_matrix[i]);
	}

	compiler.Add(str_city_location, &city_location);

	compiler.Add(str_policies_deck, &policies_deck_location);
	compiler.Add(str_events_deck_close, &events_deck_close_location);
	compiler.Add(str_events_deck_open, &events_deck_open_location);
	compiler.Add(str_policy_front, &policy_front_offset);
	compiler.Add(str_policy_back, &policy_back_offset);
	compiler.Add(str_policy_image, &policy_image_offset);

	compiler.Add(str_event_front, &events_front_offset);		
	compiler.Add(str_event_back, &events_back_offset);
	compiler.Add(str_policies_activated_first_location, &policies_activated_first_location_offset);
	compiler.Add(str_policies_in_hand_first_location, &policies_in_hand_first_location_offset);
	compiler.Add(str_black_action_0_philosophy, &action_front_offset);
	compiler.Add(str_black_action_back, &action_back_offset);

	compiler.Add(str_coin_5, &coin_5_material);
	compiler.Add(str_coin_1, &coin_1_material);
	compiler.Add(str_philosophy, &philosophy_material);

	compiler.Add(str_policy_front_silver_mine, &policy_front_geometry);
	compiler.Add(str_policy_back, &policy_back_geometry);

	compiler.Add(str_policy_back, &policy_back_material);
	for (int i = 0; i < As<int>(PolicyType::Count); ++i) {
		compiler.Add(str_policy_front_materials[i], &policy_front_materials[i]);
	}

	for (int i = 0; i < As<int>(Policies::policies_count); ++i) {
		compiler.Add(str_policy_images[i], &policy_materials[i]);
	}

	compiler.Add(str_card_front, &card_front_geometry);
	compiler.Add(str_card_back, &card_back_geometry);
	compiler.Add(str_front_image, &front_image_geometry);
	compiler.Add(str_back_image, &back_image_geometry);

	for (int i = 0; i < cities_count; ++i) {
		compiler.Add(str_city_material[i], &cities_materials[i]);
	}

	compiler.Add(str_black_city, &city_level_geometry);
	compiler.Add(str_black_economy, &economy_level_geometry);
	compiler.Add(str_black_culture, &culture_level_geometry);
	compiler.Add(str_black_military, &military_level_geometry);
	compiler.Add(str_black_points, &board_cursor_geometry);
	compiler.Add(str_achieve, &achieve_geometry);
	compiler.Add(str_mark_90, &mark_90_geometry);
	compiler.Add(str_dice, &dice_geometry);
	compiler.Add(str_black_action_0_philosophy, &action_front_geometry);
	compiler.Add(str_black_action_back, &action_back_geometry);
	compiler.Add(str_tablet, &tablet_geometry);
	compiler.Add(str_table, &table_geometry);
	compiler.Add(str_policy_front, &policy_front_geometry);
	compiler.Add(str_policy_image, &policy_image_geometry);	
	compiler.Add(str_policy_back, &policy_back_geometry);

	compiler.Add(str_event_front, &event_front_geometry);
	compiler.Add(str_event_back, &event_back_geometry);

	for (int i = 0; i < players_count; ++i) {
		compiler.Add(str_city_level_material[i], &city_level_materials[i]);
	}

	for (int i = 0; i < players_count; ++i) {
		compiler.Add(str_economy_material[i], &economy_materials[i]);
	}

	for (int i = 0; i < players_count; ++i) {
		compiler.Add(str_culture_material[i], &culture_materials[i]);
	}

	for (int i = 0; i < players_count; ++i) {
		compiler.Add(str_military_material[i], &military_materials[i]);
	}

	for (int i = 0; i < players_count; ++i) {
		compiler.Add(str_population_material[i], &population_materials[i]);
	}

	for (int i = 0; i < players_count; ++i) {
		compiler.Add(str_army_material[i], &army_materials[i]);
	}

	for (int i = 0; i < players_count; ++i) {
		compiler.Add(str_glory_material[i], &glory_materials[i]);
	}

	for (int i = 0; i < players_count; ++i) {
		compiler.Add(str_points_material[i], &points_materials[i]);
	}

	for (int i = 0; i < players_count; ++i) {
		compiler.Add(str_tax_material[i], &tax_materials[i]);
	}

	for (int i = 0; i < players_count; ++i) {
		compiler.Add(str_achieve_points_material[i], &achieve_points_materials[i]);
	}

	for (int i = 0; i < players_count; ++i) {
		compiler.Add(str_achieve_population_material[i], &achieve_population_materials[i]);
	}

	for (int i = 0; i < players_count; ++i) {
		compiler.Add(str_achieve_army_material[i], &achieve_army_materials[i]);
	}

	for (int i = 0; i < players_count; ++i) {
		compiler.Add(str_achieve_economy_material[i], &achieve_economy_materials[i]);
	}

	for (int i = 0; i < players_count; ++i) {
		compiler.Add(str_achieve_policy_material[i], &achieve_policy_materials[i]);
	}

	for (int i = 0; i < players_count; ++i) {
		compiler.Add(str_mark_90_material[i], &achieve_mark_90_materials[i]);
	}

	for (int i = 0; i < players_count; ++i) {
		compiler.Add(str_dice_material[i], &dice_materials[i]);
	}

	compiler.Add(str_discovery, &discovery_geometry);

	for (int i = 0; i < As<int>(discovery_type::discoveries_count); ++i)
	{
		compiler.Add(str_discovery_type[i], &discovery_materials[i]);
	}

	// camera_serialization_table[str_camera, &camera);

	for (int i = 0; i < max_points_locations; ++i) {
		std::stringstream stream;
		stream << str_cur_point_prefix << std::setfill('0') << std::setw(3) << i;
		auto name = stream.str();

		compiler.Add(name, &points_location[i]);
	}

	for (int i = 0; i < max_tax_locations; ++i) {
		std::stringstream stream;
		stream << str_cur_tax_prefix << i;
		auto name = stream.str();

		compiler.Add(name, &tax_location[i]);
	}

	for (int i = 0; i < max_population_locations; ++i) {
		std::stringstream stream;
		stream << str_cur_population_prefix << i;
		auto name = stream.str();

		compiler.Add(name, &population_location[i]);
	}

	for (int i = 0; i < max_glory_locations; ++i) {
		std::stringstream stream;
		stream << str_cur_glory_prefix << i;
		auto name = stream.str();

		compiler.Add(name, &glory_location[i]);
	}

	for (int i = 0; i < max_army_locations; ++i) {
		std::stringstream stream;
		stream << str_cur_army_prefix << i;
		auto name = stream.str();

		compiler.Add(name, &army_location[i]);
	}

	for (int i = 0; i < max_expedition_discoveries; ++i) {
		compiler.Add(std::get<1>(str_cur_discovery[i]), &expedition_discoveries_offsets[i]);
	}

	for (int i = 0; i < achieves_count; ++i) {
		compiler.Add(str_cur_achieve[i], &achieve_location[i]);
	}
}
