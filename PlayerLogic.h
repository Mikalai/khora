#pragma once

#include <vector>
#include <array>
#include <string_view>
#include <functional>
#include <Observers.h>
#include <Resources.h>
#include <Platform/NumberConverter.h>
#include <PoliciesManipulator.h>
#include <PlayerPerks.h>
#include <DraftManipulator.h>
#include <DraftManipulatorConst.h>

using DiscoveryCollection = std::vector<discovery_type>;
using PolicyCollection = std::vector<PoliciesType>;

struct GameMessage;
class PlayerLogic;
class WorldLogic;

using ProgressCostPerk = std::function<int(ProgressTrackType, int)>;
using MilitaryLossesPerk = std::function<int(int)>;
using DiscoveryCostPerk = std::function<int(int)>;
using ActionCompleteCallback = std::function<void()>;
using DiscoveryDroppedCallback = std::function<void(int count)>;
using PolicyDroppedCallback = std::function<void(PoliciesType policy)>;
using DiscoverySelectedCallback = std::function<void(discovery_type discovery)>;
using ExtraProgressCallback = std::function<void(PlayerLogic& logic)>;
using SelectActionCallback = std::function<void(ActionType action)>;
using SelectPolicyCallback = std::function<void(PoliciesType policy)>;
//enum class PlayerState {
//	Idle,
//	SelectPolicy
//};

class PlayerPerks;

class PlayerLogic : public Observable<GameMessage> {
	friend class WorldLogic;
	friend class PlayerPerks;
	friend class ConstPlayerPoliciesManipulator;
	friend class ConstPlayerInActiveDeckPoliciesManipulator;
	friend class ConstPlayerInHandsPoliciesManipulator;
	friend class ConstPlayerFilteredInHandsPolicies;
	friend class ConstPlayerFilteredInActiveDeckPolicies;

public:

	PlayerLogic();

	PlayerLogic(const PlayerLogic&) = delete;
	PlayerLogic(PlayerLogic&&) = delete;
	PlayerLogic& operator = (const PlayerLogic&) = delete;
	PlayerLogic& operator = (PlayerLogic&&) = delete;

	PlayerPerks Perks();
	const DiscoveryCollection& GetDiscoveries() const;
	void UnlockDice();
	void ExecuteEndGamePerks();
	void AddTaxPerk(PlayerPerk perk);
	void AddCulturePerk(PlayerPerk perk);
	void AddTradePerk(PlayerPerk perk);
	void AddPolicyPerk(PlayerPerk perk);
	void AddEndGamePerk(PlayerPerk perk);
	void AddMilitaryPerk(PlayerPerk perk);
	void AddAnyMomentPerk(PlayerPerk perk);
	void AddPhilosophyPerk(PlayerPerk perk);
	void AddUpgradePerk(PlayerPerk perk);
	void AddLawPerk(PlayerPerk perk);
	void AddMilitaryLossesPerk(MilitaryLossesPerk perk);
	void AddDiscoveryCostTradePerk(DiscoveryCostPerk perk);
	void AddProgressCostPerk(ProgressCostPerk perk);
	void AddPostProgressPerk(PlayerPerk perk);
	void AddProgressPerk(PlayerPerk perk);
	void AddAvailableProgress(int count);
	void RemoveAvailableProgress(int count);
	void AddPoints(int count);
	void AddArmy(int count, bool allowOverflow);
	void RemoveArmy(int count);
	void RemovePoints(int count);
	int GetPoints() const;
	void AddTaxLevel(int count);
	void AddEconomyLevel(int count);
	void AddCulture(int count);
	void AddMilitaryLevel(int count);
	void AddMoney(int count);
	void AddGlory(int count);
	void AddDiscovery(discovery_type type, int fromExpedition, int indexInExpedition, int selectionIndex);
	void RemoveDiscovery(discovery_type type);
    void RemovePolicy(PoliciesType policy);
	void RemoveGlory(int count);
	void AddPhilosophy(int count);
	void RemovePhilosophy(int count);
	void AddPopulation(int count);
	void RemovePopulation(int count);
	player_color GetColor() const;
    void AddPolicy(PoliciesType policy, bool selectFlag);
	void SetColor(player_color color);
	Cities GetCity() const;
	void SetCity(Cities value);
	bool HasRedDiscovery(int count) const;
	bool HasBlueDiscovery(int count) const;
	bool HasGreenDiscovery(int count) const;
	int GetRedDiscovery() const;
	int GetBlueDiscovery() const;
	int GetGreenDiscovery() const;
	bool HasMoney(int count) const;
	void RemoveMoney(int count);
	int GetId() const;
	int GetPhilosophyCount() const;
	int GetPoliciesInActiveDeckCount() const;
    PoliciesType GetPolicyInActiveDeck(int index) const;
	int GetPoliciesInHandCount() const;
	int GetMilitaryLevel() const;
	int GetCultureLevel() const;
	int GetArmySize() const;
	int GetGlory() const;
	int GetSmallDiscoveries() const;

	void BeginSelectBonus(int army, int money, int points, int population, ActionCompleteCallback cb);
	void EndSelectBonus(int army, int money, int points, int population);

	void BeginSelectAction(int diceValue, bool allowMilitary, SelectActionCallback cb);
	void EndSelectionAction(ActionType action);

	/*void BeginDropPolicy(PolicyDroppedCallback cb);
	void EndDropPolicy(Policies policy);*/

	void BeginSelectDiscoveryFromPool(DiscoverySelectedCallback cb);
	void EndSelectDiscoveryFromPool(discovery_type discovery);

	void BeginSelectDiscoveryFromHands(DiscoverySelectedCallback cb);
	void EndSelectDiscoveryFromHands(discovery_type discovery);

	/*void BeginDropDiscovery(DiscoveryDroppedCallback cb);
	void EndDropDiscovery(discovery_type discovery);*/

	void BeginExtraProgress(ProgressTrackType track, int discont, ExtraProgressCallback cb);
	void EndExtraProgress();

	void DoPhilosophy(ActionCompleteCallback cb);

	void BeginDoLaw(ActionCompleteCallback cb);
    void EndDoLaw(PoliciesType selected, PoliciesType dropped);

	void DoCulture(ActionCompleteCallback cb);
	void DoTrade(ActionCompleteCallback cb);
	void BeginDoMilitary(ActionCompleteCallback cb);
	void EndDoMilitary();
	/*void BeginActivatePolicy(ActionCompleteCallback cb);*/
    void ActivatePolicy(PoliciesType policy);

    bool CanActivatePolicy(PoliciesType policy) const;
	void DoExpand(ActionCompleteCallback cb);
	void BeginExpedition(ActionCompleteCallback cb);
	void EndExpedition(int expedition);
	bool CanGoExpedition(int expedition) const;
	int GetLosses(int baseLosses);
	int GetPopulation() const;
	int GetEconomy() const;
	int GetMoney() const;
	int GetTax() const;
	bool HasUpgradedAnyTrack() const;
	const WorldLogic& GetWorld() const;
	WorldLogic& GetWorld();
	bool CanUpgradeTrack(ProgressTrackType type, int discont, bool extraUpgrade) const;
	void UpgradeTrack(ProgressTrackType type, int discont, bool extraUpgrade);
	int GetTrackProgressCost(ProgressTrackType type, int discont, bool extraUpgrade) const;

	int GetDiceCount() const;
	int GetDice(int index) const;
	void SortDices();

	void DropPolicy(int index);
    int GetPolicyIndex(PoliciesType dropped);

	//void DropDiscovery(discovery_type discovery);
	bool IsIdle() const;

	void BeginDraft();
	void EndDraft();
    void TakePolicyFromDraft(PoliciesType policy);
	int GetDraftSize() const;

    std::vector<PoliciesType> TakeDraft();
    void GiveDraft(std::vector<PoliciesType>&& deck);
    PoliciesType GetDraftPolicy(int index) const;

	DraftManipulator Draft();
	DraftManipulatorConst Draft() const;

	void SetPoints(int level);
	void SetPopulation(int level);
	void SetTax(int level);
	void SetGlory(int level);
	void SetArmy(int level, bool allowOverflow);
	void SetEconomy(int level);
	void SetCulture(int level);
	void SetMilitary(int level);
	void ResetDices();
	bool AreDicesThrown() const;
	void ThrowDices();
	void SetDiceValue(int diceIndex, int diceValue);

	void ResetActions();
	void ResetAction(int index);
	void SetAction(int index, ActionType action);
	ActionType GetAction(int index) const;
	bool IsActionSelected(ActionType action) const;
	bool AreActionsSelected() const;
	bool AreActionsDone() const;
	void BeginExecuteActions();
	void ExecuteNextAction();
	void BeginExecuteAction(int diceValue, ActionType action, ActionCompleteCallback cb);
	void EndExecuteAction();

	void BeginSelectPolicyFromActiveDeck(SelectPolicyCallback cb);
    void EndSelectPolicyFromActiveDeck(PoliciesType policy);

	void BeginSelectPolicyFromHandsToActivate(SelectPolicyCallback cb);
	void BeginSelectPolicyFromHandsToDrop(SelectPolicyCallback cb);
	void BeginSelectPolicyFromHands(PolicySelectionReasonType reason, SelectPolicyCallback cb);
    void EndSelectPolicyFromHands(PoliciesType policy);

	void BeginProgressStage();
	bool IsProgressDone() const;
	int GetProgressSteps() const;
	void CompleteProgressStep();
	void EndProgressStage();

    ConstPlayerPoliciesManipulator GetPolicies() const;
private:
	void SetId(int id);
	void SetWorld(WorldLogic* logic);
	void SetTrack(ProgressTrackType type, int value);
	int GetTrack(ProgressTrackType type) const;
	int GetDiscoveryCount(discovery_type type) const;
	const PlayerPerk& GetTrackUpgradePerk(ProgressTrackType type, int level) const;
	int GetTrackUpgradeBaseCost(ProgressTrackType type, int level) const;
	void AddTrackLevel(ProgressTrackType type, int count);
	// void SetState(PlayerState state);	
	WorldLogic& World();
	void UpgradeCity();
	bool CanUpgradeCity();
	void InvokeActionCallback(ActionType type);
	void SetActionCallback(ActionType type, ActionCompleteCallback cb);
	void BeginActiveTask(std::string_view reason);
	void EndActiveTask(std::string_view reason);

private:
	WorldLogic* _world{ nullptr };
	DiscoveryCollection _discoveries;
	PolicyCollection _policiesInHands;
	PolicyCollection _policiesInDraft;
	PolicyCollection _policiesInActiveDeck;
	Cities _city = city_unknown;
	player_color _color = player_color_unknown;
	int _curCityLevel = -1;
	// PlayerState _state{ PlayerState::Idle };
	int _activeTasks = 0;
	std::array<int, 3> _cityTracks{ 0 };


	int _curMoney = 0;
	int _curPoints = 0;
	int _curPopulation = 3;
	int _curTax = 0;
	int _curGlory = 0;
	int _curArmy = 0;
	int _philosophyCount = 0;
	int _availableProgressCount = 1;
	int _id = 0;
	int _dicesCount = 2;
	std::array<int, 3> _currentDices{ -1, -1, -1 };
	std::array<ActionType, 3> _currentActions{ ActionType::Unknown, ActionType::Unknown, ActionType::NotAvailable };
    std::vector<PlayerPerk> _tradePerks;
	std::vector<PlayerPerk> _policyPerks;
	std::vector<PlayerPerk> _endGamePerks;
	std::vector<PlayerPerk> _culturePerks;
	std::vector<PlayerPerk> _militaryPerks;
	std::vector<PlayerPerk> _lawPerks;
	std::vector<PlayerPerk> _anyMomentPerks;
	std::vector<PlayerPerk> _philosophyPerks;
	std::vector<PlayerPerk> _postProgressPerks;
	std::vector<PlayerPerk> _progressPerks;
	std::vector<PlayerPerk> _upgradePerks;
	std::vector<PlayerPerk> _taxPerks;
	std::vector<ProgressCostPerk> _progressCostPerks;
	std::vector<MilitaryLossesPerk> _militaryLossesPerks;
	std::vector<DiscoveryCostPerk> _discoveryCostPerks;    
	std::array<ActionCompleteCallback, As<int>(ActionType::Count)> _actionCallbacks;
	ActionCompleteCallback _expeditionCallback;
	DiscoveryDroppedCallback _discoveryDroppedCallback;
	PolicyDroppedCallback _dropPolicyCallback;
	DiscoverySelectedCallback _discoverySelectedCallback;
	ExtraProgressCallback _extraProgressCallback;
	SelectActionCallback _selectActionCallback;
	ActionCompleteCallback _executeActionCallback;
	SelectPolicyCallback _policySelected;
	ActionCompleteCallback _selectBonusCallback;

	struct ActionExecutionState {
		int actionsCount{0};
		int nextAction{0};

		std::array<std::tuple<int, ActionType>, 3> actions;

		void Reset(const PlayerLogic& p);
		std::tuple<int, ActionType> Current() const;
		void Next();
		bool IsComplete() const;
	};

	ActionExecutionState _actionExecutionState;

	struct ProgressState {
		int upgradedTracksCount{ 0 };
		int tracksLeft{ 0 };
		bool isComplete{ false };
		void Reset(const PlayerLogic& p);
		bool IsComplete(const PlayerLogic& p) const;
		void TrackIncreased();
		bool HasUpgradedTracks() const;
		void Complete(const PlayerLogic& p);
	};

	ProgressState _progressState;
};
