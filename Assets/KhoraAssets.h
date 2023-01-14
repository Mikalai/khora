#pragma once

#include <filesystem>
#include <vsg/io/Options.h>
#include <unordered_map>
#include <string>
#include <vector>
#include <memory>
#include <vsg/all.h>
#include <Resources.h>
#include <Assets/Assets.h>

class AssetsCompiler;

class KhoraAssets : public Assets {
public:

    void FillSerializationTables(AssetsCompiler& compiler) override;    

    vsg::ref_ptr<vsg::Camera> _camera;
    vsg::ref_ptr<vsg::MatrixTransform> root;
    vsg::ref_ptr<vsg::MatrixTransform> economy_text_location;
    vsg::ref_ptr<vsg::MatrixTransform> culture_text_location;
    vsg::ref_ptr<vsg::MatrixTransform> military_text_location;
    vsg::ref_ptr<vsg::MatrixTransform> dice_icon_culture_location;

    vsg::ref_ptr<vsg::MatrixTransform> economy_icon_location;
    vsg::ref_ptr<vsg::MatrixTransform> culture_icon_location;
    vsg::ref_ptr<vsg::MatrixTransform> military_power_icon_location;
    vsg::ref_ptr<vsg::MatrixTransform> persepolis_text_location;
    vsg::ref_ptr<vsg::Font> font;
    vsg::ref_ptr<vsg::MatrixTransform> troops_text_location;
    vsg::ref_ptr<vsg::MatrixTransform> glory_text_location;
    vsg::ref_ptr<vsg::MatrixTransform> tax_text_location;
    vsg::ref_ptr<vsg::MatrixTransform> population_text_location;
    vsg::ref_ptr<vsg::MatrixTransform> coin_first_location_offset;
    vsg::ref_ptr<vsg::MatrixTransform> loc_dice_3_offset;
    vsg::ref_ptr<vsg::MatrixTransform> first_dice_location;
    vsg::ref_ptr<vsg::MatrixTransform> first_action_card;
    vsg::ref_ptr<vsg::MatrixTransform> first_philosophy_offset;
    vsg::ref_ptr<vsg::MatrixTransform> policies_deck_location;
    vsg::ref_ptr<vsg::MatrixTransform> events_deck_close_location;
    vsg::ref_ptr<vsg::MatrixTransform> events_deck_open_location;
    vsg::ref_ptr<vsg::MatrixTransform> events_front_offset;
    vsg::ref_ptr<vsg::MatrixTransform> events_back_offset;
    vsg::ref_ptr<vsg::MatrixTransform> policies_activated_first_location_offset;
    vsg::ref_ptr<vsg::MatrixTransform> policies_in_hand_first_location_offset;
    vsg::ref_ptr<vsg::MatrixTransform> first_discovery_offset;
    vsg::ref_ptr<vsg::VertexIndexDraw> event_front_geometry;
    vsg::ref_ptr<vsg::VertexIndexDraw> event_back_geometry;
    std::array<vsg::ref_ptr<vsg::StateGroup>, (int)GlobalEventType::Count> events_materials;

    vsg::ref_ptr<vsg::StateGroup> event_back_material;
    vsg::ref_ptr<vsg::StateGroup> board_material;
    vsg::ref_ptr<vsg::StateGroup> table_material;

    vsg::ref_ptr<vsg::VertexIndexDraw> economy_icon_geometry;
    vsg::ref_ptr<vsg::VertexIndexDraw> culture_icon_geometry;
    vsg::ref_ptr<vsg::VertexIndexDraw> military_icon_geometry;
    vsg::ref_ptr<vsg::VertexIndexDraw> dice_icon_geometry;
    vsg::ref_ptr<vsg::VertexIndexDraw> board_geometry;
    vsg::ref_ptr<vsg::VertexIndexDraw> card_front_geometry;
    vsg::ref_ptr<vsg::VertexIndexDraw> card_back_geometry;
    vsg::ref_ptr<vsg::VertexIndexDraw> coin_geometry;
    vsg::ref_ptr<vsg::VertexIndexDraw> front_image_geometry;
    vsg::ref_ptr<vsg::VertexIndexDraw> back_image_geometry;
    vsg::ref_ptr<vsg::VertexIndexDraw> philosophy_geometry;
    vsg::ref_ptr<vsg::StateGroup> coin_5_material;
    vsg::ref_ptr<vsg::StateGroup> coin_1_material;
    vsg::ref_ptr<vsg::StateGroup> philosophy_material;
    vsg::ref_ptr<vsg::VertexIndexDraw> policy_front_geometry;
    vsg::ref_ptr<vsg::VertexIndexDraw> policy_back_geometry;
    vsg::ref_ptr<vsg::VertexIndexDraw> policy_image_geometry;
    vsg::ref_ptr<vsg::MatrixTransform> policy_front_offset;
    vsg::ref_ptr<vsg::MatrixTransform> policy_back_offset;
    vsg::ref_ptr<vsg::MatrixTransform> policy_image_offset;
    std::array<vsg::ref_ptr<vsg::StateGroup>, As<int>(PolicyType::Count)> policy_front_materials;
    vsg::ref_ptr<vsg::StateGroup> policy_back_material;    
    vsg::ref_ptr<vsg::VertexIndexDraw> tablet_geometry;
    vsg::ref_ptr<vsg::VertexIndexDraw> city_level_geometry;
    vsg::ref_ptr<vsg::VertexIndexDraw> economy_level_geometry;
    vsg::ref_ptr<vsg::VertexIndexDraw> culture_level_geometry;
    vsg::ref_ptr<vsg::VertexIndexDraw> military_level_geometry;
    vsg::ref_ptr<vsg::VertexIndexDraw> board_cursor_geometry;
    vsg::ref_ptr<vsg::VertexIndexDraw> achieve_geometry;
    vsg::ref_ptr<vsg::VertexIndexDraw> mark_90_geometry;
    vsg::ref_ptr<vsg::VertexIndexDraw> dice_geometry;
    vsg::ref_ptr<vsg::VertexIndexDraw> action_front_geometry;
    vsg::ref_ptr<vsg::VertexIndexDraw> action_back_geometry;
    std::array<vsg::ref_ptr<vsg::StateGroup>, players_count> action_back_materials;
    std::array<std::array<vsg::ref_ptr<vsg::StateGroup>, (int)ActionType::Count>, players_count> action_front_materials;
    std::array<std::array<vsg::ref_ptr<vsg::MatrixTransform>, (int)ActionType::Count>, players_count> actions;
    vsg::ref_ptr<vsg::MatrixTransform> action_front_offset;
    vsg::ref_ptr<vsg::MatrixTransform> action_back_offset;
    vsg::ref_ptr<vsg::VertexIndexDraw> table_geometry;

    vsg::ref_ptr<vsg::VertexIndexDraw> discovery_geometry;
    std::array<vsg::ref_ptr<vsg::StateGroup>, As<int>(discovery_type::discoveries_count)> discovery_materials;
    std::array<vsg::ref_ptr<vsg::MatrixTransform>, max_expedition_discoveries> expedition_discoveries_offsets;
    //std::array<vsg::ref_ptr<vsg::MatrixTransform>, max_expedition_discoveries> expedition_discoveries;
    std::vector<vsg::ref_ptr<vsg::MatrixTransform>> discoveries;

    vsg::ref_ptr<vsg::StateGroup> tablet_materials;
    std::array<vsg::ref_ptr<vsg::StateGroup>, players_count> city_level_materials;
    std::array<vsg::ref_ptr<vsg::StateGroup>, players_count> economy_materials;
    std::array<vsg::ref_ptr<vsg::StateGroup>, players_count> culture_materials;
    std::array<vsg::ref_ptr<vsg::StateGroup>, players_count> military_materials;
    std::array<vsg::ref_ptr<vsg::StateGroup>, players_count> population_materials;
    std::array<vsg::ref_ptr<vsg::StateGroup>, players_count> army_materials;
    std::array<vsg::ref_ptr<vsg::StateGroup>, players_count> glory_materials;
    std::array<vsg::ref_ptr<vsg::StateGroup>, players_count> points_materials;
    std::array<vsg::ref_ptr<vsg::StateGroup>, players_count> tax_materials;
    std::array<vsg::ref_ptr<vsg::StateGroup>, players_count> achieve_points_materials;
    std::array<vsg::ref_ptr<vsg::StateGroup>, players_count> achieve_population_materials;
    std::array<vsg::ref_ptr<vsg::StateGroup>, players_count> achieve_army_materials;
    std::array<vsg::ref_ptr<vsg::StateGroup>, players_count> achieve_economy_materials;
    std::array<vsg::ref_ptr<vsg::StateGroup>, players_count> achieve_policy_materials;
    std::array<vsg::ref_ptr<vsg::StateGroup>, players_count> achieve_mark_90_materials;
    std::array<vsg::ref_ptr<vsg::StateGroup>, players_count> dice_materials;    

    std::array<vsg::ref_ptr<vsg::MatrixTransform>, players_count> cur_points;
    std::array<vsg::ref_ptr<vsg::MatrixTransform>, players_count> cur_population;
    std::array<vsg::ref_ptr<vsg::MatrixTransform>, players_count> cur_tax;
    std::array<vsg::ref_ptr<vsg::MatrixTransform>, players_count> cur_glory;
    std::array<vsg::ref_ptr<vsg::MatrixTransform>, players_count> cur_army;
    std::array<vsg::ref_ptr<vsg::MatrixTransform>, players_count> cur_city_level;
    std::array<vsg::ref_ptr<vsg::MatrixTransform>, players_count> cur_economy;
    std::array<vsg::ref_ptr<vsg::MatrixTransform>, players_count> cur_culture;
    std::array<vsg::ref_ptr<vsg::MatrixTransform>, players_count> cur_military;
    std::array<std::array<vsg::ref_ptr<vsg::MatrixTransform>, 3>, players_count> cur_dices;
    std::array<std::array<vsg::ref_ptr<vsg::MatrixTransform>, (int)ActionType::Count>, players_count> cur_action_cards;

    std::array<vsg::dmat4, players_count> activated_policies_table_first_location;
    std::array<vsg::dmat4, players_count> in_hand_policies_table_first_location;

    std::array<vsg::dmat4, players_count> players_tablet_matrix;
    std::array<vsg::ref_ptr<vsg::MatrixTransform>, players_count> players_tablet_locations;
    std::array<vsg::ref_ptr<vsg::MatrixTransform>, players_count> players_city_locations;
    vsg::ref_ptr<vsg::MatrixTransform> city_location;
    std::array<std::array<vsg::ref_ptr<vsg::StateGroup>, players_count>, 6> actions_materials;
    std::array<vsg::ref_ptr<vsg::StateGroup>, As<int>(Policies::policies_count)> policy_materials;    
    std::array<vsg::ref_ptr<vsg::StateGroup>, cities_count> cities_materials;
    std::array<vsg::ref_ptr<vsg::MatrixTransform>, max_points_locations> points_location;
    std::array<vsg::ref_ptr<vsg::MatrixTransform>, max_population_locations> population_location;
    std::array<vsg::ref_ptr<vsg::MatrixTransform>, max_tax_locations> tax_location;
    std::array<vsg::ref_ptr<vsg::MatrixTransform>, max_glory_locations> glory_location;
    std::array<vsg::ref_ptr<vsg::MatrixTransform>, max_army_locations> army_location;
    std::array<vsg::ref_ptr<vsg::MatrixTransform>, achieves_count> achieve_location;
    std::array<vsg::ref_ptr<vsg::MatrixTransform>, max_city_track_level> ecomony_track_offset;
    std::array<vsg::ref_ptr<vsg::MatrixTransform>, max_city_track_level> culture_track_offset;
    std::array<vsg::ref_ptr<vsg::MatrixTransform>, max_city_track_level> military_track_offset;
    std::array<vsg::ref_ptr<vsg::MatrixTransform>, max_city_levels> city_track_offset;
    std::array<std::vector<std::tuple<int, vsg::ref_ptr<vsg::MatrixTransform>>>, players_count> player_coins;
    std::array<std::vector<vsg::ref_ptr<vsg::MatrixTransform>>, players_count> philosophy;

    vsg::ref_ptr<vsg::Node> _box;
    vsg::ref_ptr<vsg::MatrixTransform> _root;
    vsg::ref_ptr<vsg::MatrixTransform> _worldRoot;
    vsg::ref_ptr<vsg::Viewer> _viewer;
    
    std::vector<vsg::ref_ptr<vsg::MatrixTransform>> _policies_deck;
    std::vector<vsg::ref_ptr<vsg::MatrixTransform>> _events_closed_deck;
    std::vector<vsg::ref_ptr<vsg::MatrixTransform>> _events_opened_deck;
    vsg::ref_ptr<vsg::MatrixTransform> _taken_event;
    std::array<player_color, 4> _player_to_color;    
};
