#pragma once

#include <filesystem>
#include <vsg/io/Options.h>
#include <unordered_map>
#include <array>
#include <string>
#include <vector>
#include <memory>
#include <vsg/all.h>
#include <Resources.h>
#include <Render/Animation.h>
#include <Assets/Scene.h>

class AssetsCompiler;

class KhoraScene : public Scene {
public:
	
	vsg::ref_ptr<vsg::MatrixTransform> policies_deck_location;
	vsg::ref_ptr<vsg::MatrixTransform> events_deck_close_location;
	vsg::ref_ptr<vsg::MatrixTransform> events_deck_open_location;
	std::array<vsg::ref_ptr<vsg::MatrixTransform>, max_points_locations> points_location;
	std::array<vsg::ref_ptr<vsg::MatrixTransform>, max_tax_locations> tax_location;
	std::array<vsg::ref_ptr<vsg::MatrixTransform>, max_population_locations> population_location;
	std::array<vsg::ref_ptr<vsg::MatrixTransform>, max_glory_locations> glory_location;
	std::array<vsg::ref_ptr<vsg::MatrixTransform>, max_army_locations> army_location;
	std::array<vsg::ref_ptr<vsg::MatrixTransform>, max_expedition_discoveries> expedition_discoveries;
	std::array<vsg::ref_ptr<vsg::StateGroup>, As<int>(discovery_type::discoveries_count)> discovery_materials;
	std::unordered_map<vsg::ref_ptr<vsg::MatrixTransform>, int> _discoveryTokenToExpedition;
	std::unordered_map<int, std::vector<vsg::ref_ptr<vsg::MatrixTransform>>> _expeditionToDiscoveryTokens;
	std::array<vsg::ref_ptr<vsg::MatrixTransform>, achieves_count> achieve_location;
	std::array<std::vector<vsg::ref_ptr<vsg::MatrixTransform>>, players_count> in_hand_policies;
	std::array<std::vector<vsg::ref_ptr<vsg::MatrixTransform>>, players_count> in_draft_policies;
	std::array<std::vector<vsg::ref_ptr<vsg::MatrixTransform>>, players_count> activated_policies;
	std::array<std::vector<std::tuple<discovery_type, vsg::ref_ptr<vsg::MatrixTransform>>>, players_count> in_hand_discoveries;
	std::array<std::tuple<discovery_type, vsg::ref_ptr<vsg::MatrixTransform>>, 3> select_discoveries;
	std::array<vsg::ref_ptr<vsg::MatrixTransform>, As<int>(Policies::policies_count)> policies;
	std::array<vsg::ref_ptr<vsg::StateGroup>, As<int>(PolicyType::Count)> policy_front_materials;	
	vsg::ref_ptr<vsg::StateGroup> policy_back_material;
	std::array<vsg::ref_ptr<vsg::StateGroup>, (int)GlobalEventType::Count> event_materials;
	vsg::ref_ptr<vsg::StateGroup> event_back_material;
	std::array<vsg::ref_ptr<vsg::MatrixTransform>, (int)GlobalEventType::Count> events;
	
	vsg::ref_ptr<vsg::MatrixTransform> persepolis_text_location;
	vsg::ref_ptr<vsg::MatrixTransform> troops_text_location;
	vsg::ref_ptr<vsg::MatrixTransform> glory_text_location;
	vsg::ref_ptr<vsg::MatrixTransform> tax_text_location;
	vsg::ref_ptr<vsg::MatrixTransform> population_text_location;


private:
	friend class KhoraSceneBuilder;

	std::array<vsg::dmat4, players_count> in_hand_policies_table_first_location;
};
