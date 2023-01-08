#pragma once

#include <Resources.h>
#include <Platform/NumberConverter.h>
#include <Render/Animation.h>
#include <ExpeditionTemplate.h>
#include <UI/GeneralUserInput.h>
#include <unordered_set>
#include <UI/IUserInput.h>
#include <vsg/all.h>
#include <Observers.h>
#include <Messages/All.h>
#include <Render/IntersectionHandler.h>
#include <Render/WorldVisualAnimator.h>
#include <Render/WorldVisualInput.h>
#ifdef vsgXchange_FOUND
#    include <vsgXchange/all.h>
#endif

class WorldLogic;
class WorldVisual;
class Animation;

template<>
struct std::hash<vsg::ref_ptr<vsg::MatrixTransform>> {
    std::size_t operator () (const vsg::ref_ptr<vsg::MatrixTransform>& v) const {
        return std::hash<const void*>()(v.get());
    }
};

class WorldVisual : public GeneralUserInput, public Observer<GameMessage>, public Observer<IntersectionMessage> {
public:  

    void CreateFromScene(vsg::ref_ptr<vsg::Node> scene);
    auto CreateBox();
    void CreateScene();
    vsg::StateInfo state;
    vsg::ref_ptr<vsg::Node> GetWorldRoot();
    vsg::ref_ptr<vsg::Node> GetRoot();
    //vsg::ref_ptr<vsg::Camera> GetCamera();
    WorldVisual(WorldVisualInput vi);
    void Update(float dt);
    using GeneralUserInput::Update;

    vsg::ref_ptr<vsg::Builder> builder;
    std::unordered_map<std::string, vsg::ref_ptr<vsg::StateGroup>*> materials_serialization_table;
    std::unordered_map<std::string, vsg::ref_ptr<vsg::VertexIndexDraw>*> geometry_serialization_table;
    std::unordered_map<std::string, vsg::ref_ptr<vsg::MatrixTransform>*> transform_serialization_table;
    std::unordered_map<std::string, vsg::ref_ptr<vsg::Camera>*> camera_serialization_table;

    vsg::ref_ptr<vsg::Camera> _camera;
    vsg::ref_ptr<vsg::MatrixTransform> root;
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
    std::array<vsg::ref_ptr<vsg::MatrixTransform>, (int)GlobalEventType::Count> events;
    vsg::ref_ptr<vsg::StateGroup> event_back_material;
    vsg::ref_ptr<vsg::StateGroup> board_material;
    vsg::ref_ptr<vsg::StateGroup> table_material;
    vsg::ref_ptr<vsg::VertexIndexDraw> board_geometry;
    vsg::ref_ptr<vsg::VertexIndexDraw> city_geometry;
    vsg::ref_ptr<vsg::VertexIndexDraw> coin_geometry;
    vsg::ref_ptr<vsg::VertexIndexDraw> philosophy_geometry;
    vsg::ref_ptr<vsg::StateGroup> coin_5_material;
    vsg::ref_ptr<vsg::StateGroup> coin_1_material;
    vsg::ref_ptr<vsg::StateGroup> philosophy_material;
    vsg::ref_ptr<vsg::VertexIndexDraw> policy_front_geometry;
    vsg::ref_ptr<vsg::VertexIndexDraw> policy_back_geometry;
    vsg::ref_ptr<vsg::MatrixTransform> policy_front_offset;
    vsg::ref_ptr<vsg::MatrixTransform> policy_back_offset;
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
    std::array<vsg::ref_ptr<vsg::MatrixTransform>, max_expedition_discoveries> expedition_discoveries;
    std::vector<vsg::ref_ptr<vsg::MatrixTransform>> discoveries;

    std::array<vsg::ref_ptr<vsg::StateGroup>, players_count> tablet_materials;
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

    std::array<std::vector<vsg::ref_ptr<vsg::MatrixTransform>>, players_count> in_hand_policies;
    std::array<std::vector<vsg::ref_ptr<vsg::MatrixTransform>>, players_count> in_draft_policies;
    std::array<std::vector<vsg::ref_ptr<vsg::MatrixTransform>>, players_count> activated_policies;    
    std::array<std::vector<std::tuple<discovery_type, vsg::ref_ptr<vsg::MatrixTransform>>>, players_count> in_hand_discoveries;
    std::array<std::tuple<discovery_type, vsg::ref_ptr<vsg::MatrixTransform>>, 3> select_discoveries;

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

    std::array<vsg::ref_ptr<vsg::MatrixTransform>, players_count> players_tablet_locations;
    std::array<vsg::ref_ptr<vsg::MatrixTransform>, players_count> players_city_locations;
    vsg::ref_ptr<vsg::MatrixTransform> city_location;
    std::array<std::array<vsg::ref_ptr<vsg::StateGroup>, players_count>, 6> actions_materials;    
    std::array<vsg::ref_ptr<vsg::StateGroup>, As<int>(Policies::policies_count)> policy_materials;	   
    std::array<vsg::ref_ptr<vsg::MatrixTransform>, As<int>(Policies::policies_count)> policies;
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
    WorldLogic& _world;

   std::vector<std::unique_ptr<Animation>> _animations;
   std::vector<std::unique_ptr<Animation>> _backgroundAnimations;
    std::vector<vsg::ref_ptr<vsg::MatrixTransform>> _policies_deck;
    std::vector<vsg::ref_ptr<vsg::MatrixTransform>> _events_closed_deck;
    std::vector<vsg::ref_ptr<vsg::MatrixTransform>> _events_opened_deck;
    vsg::ref_ptr<vsg::MatrixTransform> _taken_event;
    std::array<player_color, 4> _player_to_color;

    std::unordered_map<vsg::ref_ptr<vsg::MatrixTransform>, std::function<void(vsg::ref_ptr<vsg::MatrixTransform>)>> _onActivate;

	void AddAnimation(std::unique_ptr<Animation>&& animation) {
		_animations.push_back(std::move(animation));
	}

	bool IsIdle() const override {
		return _animations.empty();
	}

	WorldVisualAnimator Animator();    

    vsg::ref_ptr<vsg::Options> _options;
    vsg::ref_ptr<vsg::Font> _font;
    vsg::ref_ptr<vsg::Switch> _selectPlayersCountMessageBox;
    std::function<void(int count)> _selectPlayersCountMessageBoxCallback;
    vsg::ref_ptr<vsg::Switch> _selectColorMessageBox;
    std::function<void(player_color color)> _selectColorMessageBoxCallback;
    vsg::ref_ptr<vsg::Switch> _selectCityMessageBox;
    std::function<void(Cities city)> _selectCityMessageBoxCallback;
    std::function<void(Policies policy)> _selectPolicyFromDraftCallback;
    vsg::ref_ptr<vsg::MatrixTransform> _cameraAligned;
    std::array<std::function<void(int)>, 3> _diceCallbacks;
    std::function<void()> _curEconomyActivated;
    std::function<void()> _curCultureActivated;
    std::function<void()> _curMilitaryActivated;
	std::function<void()> _nextActionCallback;

    std::unordered_map<vsg::ref_ptr<vsg::MatrixTransform>, int> _discoveryTokenToExpedition;
    std::unordered_map<int, std::vector<vsg::ref_ptr<vsg::MatrixTransform>>> _expeditionToDiscoveryTokens;
private:
    void CreateSelectPlayersCountMessageBox();
    void CreateSelectColorMessageBox();
    void CreateSelectCityMessageBox();	

private:
	using TransformIterator = std::vector<vsg::ref_ptr<vsg::MatrixTransform>>::iterator;
    vsg::dmat4 GetRelativeToTableLocation(int playerId, vsg::dmat4 offset);
    vsg::dmat4 GetCityTrackLocation(int playerId, int level);
    vsg::dmat4 GetEconomyTrackLocation(int playerId, int level);
    vsg::dmat4 GetCultureTrackLocation(int playerId, int level);
    vsg::dmat4 GetMilitaryTrackLocation(int playerId, int level);
    vsg::dmat4 GetDiceTransform(int diceValue);

	void MoveToGridView(TransformIterator begin, TransformIterator end, double topY, double dx, double dy, double z);
	void MoveToLinearView(TransformIterator begin, TransformIterator end, vsg::dmat4 start, vsg::dvec3 offset, vsg::dmat4 invert);

    bool MoveToView(vsg::ref_ptr<vsg::MatrixTransform> t);
    bool MoveToWorld(vsg::ref_ptr<vsg::MatrixTransform> t);
    void RemoveFromWorld(vsg::ref_ptr<vsg::MatrixTransform> t);

    void OnLoadComplete();
    void CompilePolicies();
    void CompileActions();
    void CompileEvents();
    void CompilePoliciesLocations();
    void CompileInHandsPoliciesLocations();
    void CompileActivatedPoliciesLocations();
    void CompileMoney();    
    void CompilePhilosophy();
    void CompilePlayerMarkers();
    void CompileDiscoveries();

    void Next(IntersectionMessage& msg) override;
    void OnActivate(vsg::ref_ptr<vsg::MatrixTransform> sender, std::function<void(vsg::ref_ptr<vsg::MatrixTransform>)> action);
    void OnActivateClear(vsg::ref_ptr<vsg::MatrixTransform> sender);

    std::tuple<int, vsg::ref_ptr<vsg::MatrixTransform>> CreateCoin(int playerId, int value);
    void RemoveCoin(int playerId, int index);
    void AlignCoins(int playerId);

    void SelectPlayersCountAsync(std::function<void(int count)> cb) override;
    void SelectCityColorAsync(std::function<void(player_color color)> cb) override;
    void SelectCityAsync(std::function<void(Cities city)> cb) override;
    void SelectPolicyFromDraftAsync(std::function<void(Policies policy)> cb) override;
    void ThrowDiceAsync(int diceIndex, std::function<void(int diceIndex, int diceValue)> cb) override;
    void SelectActionAsync(int diceValue, bool allowMilitary, SelectActionsCallback cb) override;
    void SelectLawPolicyAsync(Policies a, Policies b, std::function<void(Policies selected, Policies dropped)> cb) override;
    void SelectExpeditionAsync(std::function<void(int expedition)> cb) override;
    void MakeProgressAsync(MakeProgressCallback cb) override;
    void SelectPolicyFromHandsAsync(PolicySelectionReasonType reason, SelectPolicyCallback cb) override;
    void SelectDiscoveryFromHandsAsync(SelectDiscoveryCallback cb) override;
	void SelectDiscoveryFromPoolAsync(SelectDiscoveryCallback cb) override;
	void SelectPolicyFromActiveDeckAsync(SelectPolicyCallback cb) override;

	vsg::dmat4 GetInvert(int playerId) const;

private:
    void Handle(PlayerCountSelectedMessage& msg);
    void Handle(CitySelectedMessage& msg);
    void Handle(PlayerColorSelectedMessage& msg);
    void Handle(PoliciesShuffledMessage& msg);
    void Handle(PolicyAddedToDeckMessage& msg);
    void Handle(EventAddedToDeckMessage& msg);
    void Handle(PolicyTakenFromDeckMessage& msg);
    void Handle(PolicyAddedInHandsMessage& msg);
    void Handle(PolicyActivatedMessage& msg);
    void Handle(PolicyAddedToDraftMessage& msg);
    void Handle(PolicyRemovedFromDraftMessage& msg);
    void Handle(PolicyRemovedFromHandsMessage& msg);
    void Handle(AddMoneyMessage& msg);
    void Handle(RemoveMoneyMessage& msg);
    void Handle(ScorePointsChangedMessage& msg);
    void Handle(PopulationChangedMessage& msg);
    void Handle(TaxChangedMessage& msg);
    void Handle(GloryChangedMessage& msg);
    void Handle(ArmyChangedMessage& msg);
    void Handle(CityLevelChangedMessage& msg);
    void Handle(EconomyChangedMessage& msg);
    void Handle(CultureChangedMessage& msg);
    void Handle(MilitaryChangedMessage& msg);
    void Handle(ExpeditionAddedMessage& msg);    
    void Handle(EventTakenFromDeckMessage& msg);
    void Handle(EventAddedToOpenDeckMessage& msg);
    void Handle(DiceValueChangedMessage& msg);
    void Handle(ActionSelectedMessage& msg);
    void Handle(ActionUnselectedMessage& msg);
    void Handle(PhilosophyAddedMessage& msg);
    void Handle(PhilosophyRemovedMessage& msg);
    void Handle(OpenSelectedActionsMessage& msg);
    void Handle(PolicyDroppedMessage& msg);
    void Handle(PolicyAddedToPlayedMessage& msg);
    void Handle(DiscoveryAddedMessage& msg);
    
    using Mapping = MessageMapping<GeneralUserInput,
        ALL_MESSAGES>;

    Mapping& Map() { return _mapping; }
    void Next(GameMessage& msg) override;

    template<typename U>
    void On(std::function<void(WorldVisual&, U& msg)> action)
    {
        Map().On([action](GeneralUserInput& self, U& msg) {
            action(static_cast<WorldVisual&>(self), msg);
            });
    }

    Mapping _mapping;
};
