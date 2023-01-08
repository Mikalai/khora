#pragma once

#include <cassert>
#include <UI/UI.h>
#include <WorldLogic.h>
#include "PlayerLogic.h"
#include <PolicyTemplate.h>
#include <ExpeditionTemplate.h>
#include <CityTemplate.h>
#include <Platform/NumberConverter.h>
#include <Messages/All.h>
#include "PoliciesManipulator.h"

PlayerLogic::PlayerLogic() {
}

const DiscoveryCollection& PlayerLogic::GetDiscoveries() const {
	return _discoveries;
}

void PlayerLogic::AddTaxLevel(int count) {

	if (count == 0)
		return;

	SetTax(_curTax + count);	
}

void PlayerLogic::AddTrackLevel(ProgressTrackType type, int count) {
	for (int i = 0; i < count; ++i) {

		auto oldValue = GetTrack(type);
		if (oldValue == max_city_track_level)
			return;

		auto newValue = oldValue + 1;
		SetTrack(type, newValue);

		GetTrackUpgradePerk(type, oldValue)(*this);
		
		_progressState.TrackIncreased();
	}
}

void PlayerLogic::AddEconomyLevel(int count) {
	assert(count >= 0);
	
	AddTrackLevel(ProgressTrackType::Economy, count);	
}

void PlayerLogic::AddCulture(int count) {
	assert(count >= 0);

	AddTrackLevel(ProgressTrackType::Culture, count);

	CultureChangedMessage msg(GetId(), GetCultureLevel());
	Notify(msg);
}

void PlayerLogic::AddMilitaryLevel(int count) {
	assert(count >= 0);

	AddTrackLevel(ProgressTrackType::Military, count);

	MilitaryChangedMessage msg(_id, GetMilitaryLevel());
	Notify(msg);

	_progressState.TrackIncreased();
}


void PlayerLogic::AddMoney(int count) {
	if (count == 0)
		return;

	_curMoney += count;

	{
		AddMoneyMessage msg{ GetId(), count };
		Notify(msg);
	}

	{
		MoneyChangedMessage evt{ _id, _curMoney };
		Notify(evt);
	}
}

player_color PlayerLogic::GetColor() const {
	return _color;
}

void PlayerLogic::SetColor(player_color color) {
	_color = color;
	PlayerColorSelectedMessage msg{ GetId(), color };
	Notify(msg);
}

Cities PlayerLogic::GetCity() const {
	return _city;
}

void PlayerLogic::SetCity(Cities value) {
	_city = value;
	CitySelectedMessage msg{ GetId(), _city };
	Notify(msg);
}

void PlayerLogic::UpgradeCity() {
	assert(CanUpgradeCity());

	++_curCityLevel;
	auto& effect = GetCityTemplate(_city).GetUpgradeEffect(_curCityLevel);	
	CityLevelChangedMessage msg{ _id, _curCityLevel };
	Notify(msg);

	effect.Apply(*this);	
}

bool  PlayerLogic::CanUpgradeCity() {
	if (_curCityLevel == -1)
		return true;

	if (_curCityLevel >= 4)
		return false;
	return GetCityTemplate(_city).GetUpgradeEffect(_curCityLevel).CanApply(*this);
}


void PlayerLogic::SetId(int id) {
	_id = id;
}

int PlayerLogic::GetDiscoveryCount(discovery_type type) const {
	auto& d = GetDiscoveries();
	return std::count(d.begin(), d.end(), type);
}

bool PlayerLogic::HasRedDiscovery(int count) const {	
	return count <= GetRedDiscovery();
}

bool PlayerLogic::HasBlueDiscovery(int count) const {
	return count <= GetBlueDiscovery();
}

bool PlayerLogic::HasGreenDiscovery(int count) const {
	return count <= GetGreenDiscovery();
}


int PlayerLogic::GetRedDiscovery() const {
	return GetDiscoveryCount(discovery_type::red) +
		GetDiscoveryCount(discovery_type::epic_red);
}

int PlayerLogic::GetBlueDiscovery() const {
	return GetDiscoveryCount(discovery_type::blue) +
		GetDiscoveryCount(discovery_type::epic_blue);
}

int PlayerLogic::GetGreenDiscovery() const {
	return GetDiscoveryCount(discovery_type::green) +
		GetDiscoveryCount(discovery_type::epic_green);
}

bool PlayerLogic::HasMoney(int count) const {
	return _curMoney >= count;
}

int PlayerLogic::GetId() const {
	return _id;
}

void PlayerLogic::RemoveMoney(int count) {

	if (count == 0)
		return;
	
	_curMoney -= count;
	assert(_curMoney >= 0); 
	{
		RemoveMoneyMessage msg{ GetId(), count };
		Notify(msg);
	}
	{
		MoneyChangedMessage msg{ GetId(), _curMoney };
		Notify(msg);
	}
}

int PlayerLogic::GetPhilosophyCount() const {
	return _philosophyCount;
}

void PlayerLogic::AddPhilosophy(int count) {
	if (count == 0)
		return;

	_philosophyCount += count;
	PhilosophyAddedMessage msg{ GetId(), count };
	Notify(msg);
}

void PlayerLogic::RemovePhilosophy(int count) {
	if (count == 0)
		return;

	_philosophyCount -= count;
	assert(_philosophyCount >= 0);
	PhilosophyRemovedMessage msg{ GetId(), count };
	Notify(msg);
}

void PlayerLogic::AddTradePerk(PlayerPerk perk) {
	_tradePerks.push_back(perk);
}

void PlayerLogic::AddPolicyPerk(PlayerPerk perk) {
	_policyPerks.push_back(perk);
}

void PlayerLogic::AddPoints(int count) {
	if (count == 0)
		return;

	SetPoints(_curPoints + count);	
}

int PlayerLogic::GetPoints() const {
	return _curPoints;
}

void PlayerLogic::RemovePoints(int count) {	
	if (count == 0 || _curPoints == 0)
		return;

	_curPoints -= count;
	_curPoints = std::max(0, _curPoints);
	ScorePointsChangedMessage msg(GetId(), _curPoints);
	Notify(msg);
}

void PlayerLogic::AddArmy(int count, bool allowOverflow) {
	assert(count >= 0);

	if (count == 0)
		return;

	SetArmy(_curArmy + count, allowOverflow);		
}

void PlayerLogic::RemoveArmy(int count) {
	assert(count >= 0);

	if (count == 0)
		return;

	_curArmy -= count;
	_curArmy = std::max(0, std::min(max_army_level, _curArmy));
	ArmyChangedMessage msg(GetId(), _curArmy);
	Notify(msg);
}

void PlayerLogic::AddGlory(int count) {
	assert(count >= 0);

	if (count == 0)
		return;

	SetGlory(_curGlory + count);	
}

void PlayerLogic::RemoveGlory(int count) {
	assert(count >= 0);

	if (count == 0)
		return;

	_curGlory -= count;
	_curGlory = std::max(0, std::min(max_glory_level, _curGlory));
	GloryChangedMessage msg(GetId(), _curGlory);
	Notify(msg);
}

int PlayerLogic::GetPoliciesInActiveDeckCount() const {
	return static_cast<int>(_policiesInActiveDeck.size());
}

Policies PlayerLogic::GetPolicyInActiveDeck(int index) const {
	assert(index >= 0 && index < _policiesInActiveDeck.size());
	return _policiesInActiveDeck[index];
}

int PlayerLogic::GetPoliciesInHandCount() const {
	return static_cast<int>(_policiesInHands.size());
}

void PlayerLogic::AddEndGamePerk(PlayerPerk perk) {
	_endGamePerks.push_back(perk);
}

void PlayerLogic::AddProgressCostPerk(ProgressCostPerk perk) {
	_progressCostPerks.push_back(perk);
}

void PlayerLogic::AddAvailableProgress(int count) {
	_availableProgressCount += count;
}

void PlayerLogic::RemoveAvailableProgress(int count) {
	_availableProgressCount -= count;
	assert(_availableProgressCount >= 1);
}

void PlayerLogic::AddCulturePerk(PlayerPerk perk) {
	_culturePerks.push_back(perk);
}

void PlayerLogic::SetActionCallback(ActionType type, ActionCompleteCallback cb) {
	const auto index = As<int>(type);
	assert(_actionCallbacks[index] == nullptr);
	_actionCallbacks[index] = cb;
	
}

void PlayerLogic::DoPhilosophy(ActionCompleteCallback cb) {
	INFO("Player {}: DoPhilosophy", _id);

	SetActionCallback(ActionType::Philosophy, cb);

	AddPhilosophy(1);

	for (auto& perk : _philosophyPerks) {
		perk(*this);
	}

	InvokeActionCallback(ActionType::Philosophy);
}

void PlayerLogic::DoCulture(ActionCompleteCallback cb) {
	
	AddPoints(GetCultureLevel());

	for (auto& perk : _culturePerks) {
		perk(*this);
	}

	cb();
}

void PlayerLogic::DoTrade(ActionCompleteCallback cb) {
	AddMoney(GetEconomy() + 1);

	for (auto& perk : _tradePerks) {
		perk(*this);
	}	

	cb();
}

void PlayerLogic::BeginDoMilitary(ActionCompleteCallback cb) {
	BeginActiveTask("military");
	SetActionCallback(ActionType::Military, cb);

	AddArmy(GetMilitaryLevel(), true);

	BeginExpedition([this]() {
		EndDoMilitary();
		});
}

void PlayerLogic::EndDoMilitary() {
	
	for (auto& perk : _militaryPerks) {
		perk(*this);
	}

	InvokeActionCallback(ActionType::Military);
	EndActiveTask("military");
}

void PlayerLogic::BeginExpedition(ActionCompleteCallback cb) {

	if (cb) {
		assert(_expeditionCallback == nullptr);
		_expeditionCallback = cb;
	}

	BeginActiveTask("expedition");

	SelectExpeditionMessage msg{ _id };
	Notify(msg);
}

bool PlayerLogic::CanGoExpedition(int expeditionId) const {
	if (expeditionId < 0)
		return true;

	auto expedition = GetExpeditionTemplate(expeditionId);
	return GetArmySize() >= expedition.armyRequire;
}

void PlayerLogic::EndExpedition(int expeditionId) {
	
	if (expeditionId >= 0) {
		auto expedition = GetExpeditionTemplate(expeditionId);
		assert(GetArmySize() >= expedition.armyRequire);

		auto loses = GetLosses(expedition.armyLosses);

		RemoveArmy(loses);
		AddMoney(expedition.rewardMoney);
		AddPoints(expedition.rewardPoints);
		for (int i = 0; i < 3; ++i) {
			auto d = expedition.discoveries[i];
			if (d != discovery_type::no) {
				AddDiscovery(d, expeditionId, i, -1);
			}
		}

		_world->CompleteExpedition(_id, expeditionId);
	}

	if (_expeditionCallback) {
		_expeditionCallback();
		_expeditionCallback = nullptr;
	}

	EndActiveTask("expedition");
}

bool PlayerLogic::CanActivatePolicy(::Policies policy) const {
	if (policy == Policies::policy_unknown)
		return true;

	auto& p = GetPolicyTemplate(policy);
	return p.GetEffect().CanApply(*this);
}
//
//void PlayerLogic::BeginActivatePolicy(ActionCompleteCallback cb) {
//	INFO("Player {} begin policy activation", GetId());
//
//	BeginActiveTask();
//	SetActionCallback(ActionType::Policy, cb);
//
//	SelectPolicyFromHandsMessage msg{ GetId() };
//	Notify(msg);	
//}

void PlayerLogic::ActivatePolicy(::Policies policy) {

	if (policy == ::Policies::policy_unknown)
		return;

	auto& p = GetPolicyTemplate(policy);

	assert(p.GetEffect().CanApply(*this));
	p.GetEffect().Apply(*this);

	RemovePolicy(policy);

	{
		auto index = As<int>(_policiesInActiveDeck.size());
		_policiesInActiveDeck.push_back(policy);
		
		PolicyAddedToPlayedMessage msg{ GetId(), policy, index };
		Notify(msg);
	}

	{
		PolicyActivatedMessage msg{ GetId(), policy };
		Notify(msg);
	}

	for (auto& perk : _policyPerks) {
		perk(*this);
	}

	// InvokeActionCallback(ActionType::Policy);
	//EndActiveTask();
}

void PlayerLogic::DoExpand(ActionCompleteCallback cb) {
	if (CanUpgradeCity()) {
		UpgradeCity();
	}
	else {
		WARN("Player {} select city upgrade but can't do that", GetId());
	}
	cb();
}

int PlayerLogic::GetCultureLevel() const {
	return _cityTracks[(int)ProgressTrackType::Culture] + 1;
}

void PlayerLogic::AddMilitaryLossesPerk(MilitaryLossesPerk perk) {
	_militaryLossesPerks.push_back(perk);
}

void PlayerLogic::AddMilitaryPerk(PlayerPerk perk) {
	_militaryPerks.push_back(perk);
}

int PlayerLogic::GetMilitaryLevel() const {
	return _cityTracks[(int)ProgressTrackType::Military] + 1;
}

int PlayerLogic::GetLosses(int baseLosses) {
	for (auto& perk : _militaryLossesPerks) {
		baseLosses = perk(baseLosses);
	}
	return std::max(0, baseLosses);
}

int PlayerLogic::GetArmySize() const {
	return _curArmy;
}

void PlayerLogic::AddDiscovery(discovery_type type, int fromExpedition, int indexInExpedition, int selectionIndex) {
	auto index = As<int>(_discoveries.size());
	_discoveries.push_back(type);
	DiscoveryAddedMessage msg(GetId(), type, index, fromExpedition, indexInExpedition, selectionIndex);
	Notify(msg);
}

void PlayerLogic::RemoveDiscovery(discovery_type type) {
	auto it = std::find(_discoveries.begin(), _discoveries.end(), type);
	if (it != _discoveries.end()) {
		auto index = std::distance(_discoveries.begin(), it);
		_discoveries.erase(it);
		DiscoveryRemovedMessage msg(GetId(), type, index);
		Notify(msg);
	}
}

void PlayerLogic::AddAnyMomentPerk(PlayerPerk perk) {
	_anyMomentPerks.push_back(perk);
}

int PlayerLogic::GetGlory() const {
	return _curGlory;
}

int PlayerLogic::GetSmallDiscoveries() const {	
	return GetDiscoveryCount(discovery_type::blue) + GetDiscoveryCount(discovery_type::red) + GetDiscoveryCount(discovery_type::green);
}

void PlayerLogic::AddPopulation(int count) {
	assert(count >= 0);

	if (count == 0)
		return;

	SetPopulation(_curPopulation + count);	
}

void PlayerLogic::RemovePopulation(int count) {
	assert(count >= 0);

	if (count == 0)
		return;

	SetPopulation(_curPopulation - count);	
}

int PlayerLogic::GetPopulation() const {
	return _curPopulation;
}

int PlayerLogic::GetEconomy() const {
	return _cityTracks[(int)ProgressTrackType::Economy] + 1;
}

void PlayerLogic::AddLawPerk(PlayerPerk perk) {
	_lawPerks.push_back(perk);
}

int PlayerLogic::GetMoney() const {
	return _curMoney;
}

void PlayerLogic::AddDiscoveryCostTradePerk(DiscoveryCostPerk perk) {
	_discoveryCostPerks.push_back(perk);
}

int PlayerLogic::GetTax() const {
	return _curTax;
}

void PlayerLogic::AddPhilosophyPerk(PlayerPerk perk) {
	_philosophyPerks.push_back(perk);
}

void PlayerLogic::AddPostProgressPerk(PlayerPerk perk) {
	_postProgressPerks.push_back(perk);
}

bool PlayerLogic::HasUpgradedAnyTrack() const {
	return _progressState.HasUpgradedTracks();
}

void PlayerLogic::AddUpgradePerk(PlayerPerk perk) {
	_upgradePerks.push_back(perk);
}

void PlayerLogic::AddTaxPerk(PlayerPerk perk) {
	_taxPerks.push_back(perk);
}

void PlayerLogic::SetWorld(WorldLogic* logic) {
	_world = logic;
}

const WorldLogic& PlayerLogic::GetWorld() const {
	return *_world;
}

WorldLogic& PlayerLogic::GetWorld() {
	return *_world;
}

void PlayerLogic::AddProgressPerk(PlayerPerk perk) {
	_progressPerks.push_back(perk);
}

void PlayerLogic::UnlockDice() {
	assert(_dicesCount == 2);
	_dicesCount++;
	DiceUnlockedMessage msg{ GetId() };
	Notify(msg);
}

int PlayerLogic::GetTrackProgressCost(ProgressTrackType type, int discont, bool extraUpgrade) const {	
	assert(CanUpgradeTrack(type, discont, extraUpgrade));
	auto baseCost = std::max(0, GetTrackUpgradeBaseCost(type, GetTrack(type)) - discont);

	for (auto& perk : _progressCostPerks) {
		baseCost = perk(type, baseCost);
	}
	return baseCost;
}

void PlayerLogic::SetTrack(ProgressTrackType type, int value) {
	_cityTracks[(int)type] = value;

	if (type == ProgressTrackType::Economy) {
		EconomyChangedMessage msg(GetId(), value);
		Notify(msg);
	}
	else if (type == ProgressTrackType::Culture) {
		CultureChangedMessage msg(GetId(), value);
		Notify(msg);
	}
	else if (type == ProgressTrackType::Military) {
		MilitaryChangedMessage msg(GetId(), value);
		Notify(msg);
	}
}

int PlayerLogic::GetTrack(ProgressTrackType type) const {
	return _cityTracks[(int)type];
}


const PlayerPerk& PlayerLogic::GetTrackUpgradePerk(ProgressTrackType type, int level) const {
	auto& city = GetCityTemplate(_city);
	return city.GetTrackPerk(type, level);
}

int PlayerLogic::GetTrackUpgradeBaseCost(ProgressTrackType type, int level) const {
	auto& city = GetCityTemplate(_city);
	return city.GetTrackUpgradeCost(type, level);
}

bool PlayerLogic::CanUpgradeTrack(ProgressTrackType type, int discont, bool extraUpgrade) const {
	if (type == ProgressTrackType::Unknown) {
		// Upgrade was skipped
		return true;
	}

	auto level = GetTrack(type);
	if (level == max_city_track_upgrades)
		return false;

	if (!extraUpgrade) {
		if (_progressState.tracksLeft == 0) {
			// further upgrades require philosophies
			if (GetPhilosophyCount() == 0)
				return false;
		}
	}

	auto baseCost = std::max(0, GetTrackUpgradeBaseCost(type, level) - discont);

	for (auto& perk : _progressCostPerks) {
		baseCost = perk(type, baseCost);
	}

	if (baseCost > GetMoney())
		return false;

	return true;
}

void PlayerLogic::UpgradeTrack(ProgressTrackType type, int discont, bool extraUpgrade) {
	assert(CanUpgradeTrack(type, discont, extraUpgrade));

	if (type != ProgressTrackType::Unknown) {
		auto cost = GetTrackProgressCost(type, discont, extraUpgrade);
		RemoveMoney(cost);

		if (!extraUpgrade) {
			if (_progressState.tracksLeft == 0) {
				assert(GetPhilosophyCount() > 0);
				RemovePhilosophy(1);
			}
		}

		AddTrackLevel(type, 1);

		if (_progressState.tracksLeft > 0) {
			_progressState.tracksLeft--;
		}
		
	}
	else {
		if (!extraUpgrade) {
			CompleteProgressStep();
		}
	}
}

int PlayerLogic::GetDiceCount() const {
	return _dicesCount;
}

int PlayerLogic::GetDice(int index) const {
	return _currentDices[index];
}

void PlayerLogic::DropPolicy(int index) {
	INFO("Player {} is dropping policy at index {}", _id, index);

	assert(index >= 0 && index < _policiesInHands.size());
	auto it = _policiesInHands.begin();
	std::advance(it, index);
	auto policy = *it;

	RemovePolicy(policy);
	
	PolicyDroppedMessage msg(GetId(), policy);
	Notify(msg);
}
//
//void PlayerLogic::DropDiscovery(discovery_type discovery) {
//	auto it = std::find(_discoveries.begin(), _discoveries.end(), discovery);
//	assert(it != _discoveries.end());
//
//	_discoveries.erase(it);
//
//	DiscoveryDroppedMessage msg{ GetId(), discovery };
//	Notify(msg);
//}

void PlayerLogic::AddPolicy(::Policies policy, bool selectFlag) {
	_policiesInHands.push_back(policy);
	PolicyAddedInHandsMessage msg{ GetId(), policy, selectFlag };
	Notify(msg);
}

//void PlayerLogic::SetState(PlayerState state) {
//	assert(_state != state);
//	_state = state;
//}

bool PlayerLogic::IsIdle() const {
	return _activeTasks == 0; // _state == PlayerState::Idle;
}

//Policies* PlayerLogic::TakeLawPolicies(Policies a, Policies b) {
//	AddPolicy()
//	_lawPolicySlot[0] = a;
//	_lawPolicySlot[1] = b;
//
//	return &_lawPolicySlot[0];
//}

void PlayerLogic::InvokeActionCallback(ActionType type) {
	const auto index = As<int>(type);
	assert(_actionCallbacks[index] != nullptr);
	_actionCallbacks[index]();
	_actionCallbacks[index] = nullptr;
}

void PlayerLogic::EndDoLaw(::Policies selected, ::Policies dropped) {
	if (selected != Policies::policy_unknown) {
		AddPolicy(selected, false);
	}

	if (dropped != Policies::policy_unknown) {
		_world->Policies().Drop(dropped);
	}

	AddPopulation(LAW_ACTION_POPULATION_GROWTH);
	InvokeActionCallback(ActionType::Law);
	EndActiveTask("law");
}

void PlayerLogic::BeginDoLaw(ActionCompleteCallback cb) {
	// assert(IsIdle());
	// SetState(PlayerState::SelectPolicy);
	BeginActiveTask("law");

	auto a = Policies::policy_unknown;

	if (!World().Policies().CanTake()) {
		a = World().Policies().GetNextPolicy();
	}

	auto b = Policies::policy_unknown;

	if (!World().Policies().CanTake()) {
		b = World().Policies().GetNextPolicy();
	}
	
	assert(_actionCallbacks[As<int>(ActionType::Law)] == nullptr);
	_actionCallbacks[As<int>(ActionType::Law)] = cb;	
	
	SelectLawPolicyMessage msg{ _id, a, b };
	Notify(msg);

	/*ui().SelectPolicy(GetId(), TakeLawPolicies(a, b), 2,
		[cb](PlayerLogic& v, Policies* p, int count, int selected) {
			v.AddPolicy(p[selected]);
			v.SetState(PlayerState::Idle);
			cb();
		});*/
}

WorldLogic& PlayerLogic::World() {
	return *_world;
}

void PlayerLogic::BeginDraft() {	
	BeginActiveTask("draft");
	assert(_policiesInHands.size() == 5);	
	for (int i = 0; i < As<int>(_policiesInHands.size()); ++i) {		
		PolicyRemovedFromHandsMessage msg{ GetId(), _policiesInHands[i], 0};
		Notify(msg);
	}

	GiveDraft(std::move(_policiesInHands));	
	
	assert(_policiesInHands.empty());
	assert(_policiesInDraft.size() == 5);

	BeginDraftMessage msg{ GetId() };
	Notify(msg);
}

void PlayerLogic::EndDraft() {
	EndActiveTask("draft");
}

void PlayerLogic::TakePolicyFromDraft(::Policies policy) {
	auto it = std::find(_policiesInDraft.begin(), _policiesInDraft.end(), policy);
	assert(_policiesInDraft.end() != it);

	auto index = static_cast<int>(std::distance(_policiesInDraft.begin(), it));
	_policiesInDraft.erase(it);

	PolicyRemovedFromDraftMessage msg{ GetId(), policy, index };
	Notify(msg);

	AddPolicy(policy, false);	
}

std::vector<Policies> PlayerLogic::TakeDraft() {
	assert(!_policiesInDraft.empty());
	for (int i = 0; i < As<int>(_policiesInDraft.size()); ++i) {
		PolicyRemovedFromDraftMessage msg{ GetId(), _policiesInDraft[i], 0 };
		Notify(msg);
	}

	return std::move(_policiesInDraft);
}

void PlayerLogic::GiveDraft(std::vector<::Policies>&& deck) {
	assert(!deck.empty());

	if (deck.size() == 1) {
		AddPolicy(deck.front(), false);
	}
	else {
		for (auto p : deck) {
			_policiesInDraft.push_back(p);
			PolicyAddedToDraftMessage msg{ GetId(), p, static_cast<int>(_policiesInDraft.size() - 1) };
			Notify(msg);
		}
	}
	deck.clear();
}

Policies PlayerLogic::GetDraftPolicy(int index) const {
	assert(index >= 0 && index < GetDraftSize());
	return _policiesInDraft[index];
}

int PlayerLogic::GetDraftSize() const {
	return As<int>(_policiesInDraft.size());
}


void DraftManipulator::ForEach(std::function<void(Policies policy)> action) {
	for (int i = 0; i < _player.GetDraftSize(); ++i) {
		action(_player.GetDraftPolicy(i));
	}
}

DraftManipulator PlayerLogic::Draft() {
	return { *this };
}

DraftManipulatorConst PlayerLogic::Draft() const {
	return { *this };
}

void DraftManipulatorConst::ForEach(std::function<void(Policies policy)> action) {
	for (int i = 0; i < _player.GetDraftSize(); ++i) {
		action(_player.GetDraftPolicy(i));
	}
}

Policies DraftManipulatorConst::Select(int index) const {
	return _player.GetDraftPolicy(index);
}

Policies DraftManipulator::Select(int index) const {
	return _player.GetDraftPolicy(index);
}

int DraftManipulator::Size() const {
	return _player.GetDraftSize();
}

int DraftManipulatorConst::Size() const {
	return _player.GetDraftSize();
}

void DraftManipulator::Take(Policies policy) {
	_player.TakePolicyFromDraft(policy);
}

Policies DraftManipulator::Random() {
	auto index = rand() % Size();
	return _player.GetDraftPolicy(index);
}

Policies DraftManipulatorConst::Random() {
	auto index = rand() % Size();
	return _player.GetDraftPolicy(index);
}

void PlayerLogic::SetPoints(int level) {
	_curPoints = level;

	ScorePointsChangedMessage msg(GetId(), _curPoints);
	Notify(msg);

}
void PlayerLogic::SetPopulation(int level) {
	_curPopulation = level;
	_curPopulation = std::min(max_population_level, std::max(0, _curPopulation));

	PopulationChangedMessage msg(GetId(), _curPopulation);
	Notify(msg);
}

void PlayerLogic::SetTax(int level) {
	_curTax = level;
	_curTax = std::min(max_tax_level, std::max(0, _curTax));	
	TaxChangedMessage msg(_id, _curTax);
	Notify(msg);
}

void PlayerLogic::SetGlory(int level) {
	_curGlory = level;
	_curGlory = std::max(0, std::min(max_glory_level, _curGlory));
	GloryChangedMessage msg(GetId(), _curGlory);
	Notify(msg);
}

void PlayerLogic::SetArmy(int level, bool allowOverflow) {
	_curArmy = level;

	if (!allowOverflow) {
		_curArmy = std::max(0, std::min(max_army_level, _curArmy));
	}

	ArmyChangedMessage msg(GetId(), _curArmy);
	Notify(msg);
}

void PlayerLogic::SetEconomy(int level) {
	SetTrack(ProgressTrackType::Economy, level);
}

void PlayerLogic::SetCulture(int level) {
	SetTrack(ProgressTrackType::Culture, level);
}

void PlayerLogic::SetMilitary(int level) {
	SetTrack(ProgressTrackType::Military, level);
}

PlayerPerks PlayerLogic::Perks() {
	return { *this };
}

void PlayerLogic::ResetDices() {
	for (int i = 0; i < GetDiceCount(); ++i) {
		_currentDices[i] = -1;
	}
}

bool PlayerLogic::AreDicesThrown() const {
	for (int i = 0; i < GetDiceCount(); ++i) {
		if (_currentDices[i] == -1)
			return false;
	}
	return true;
}

void PlayerLogic::ThrowDices() {
	for (int i = 0; i < GetDiceCount(); ++i) {
		ThrowDiceMessage msg{ _id, i };
		Notify(msg);
	}
}

void PlayerLogic::SetDiceValue(int diceIndex, int diceValue) {
	assert(diceIndex >= 0 && diceIndex < GetDiceCount());	
	_currentDices[diceIndex] = diceValue;
	DiceValueChangedMessage msg{ _id, diceIndex, diceValue };
	Notify(msg);
}

void PlayerLogic::ResetActions() {
	for (int i = 0; i < GetDiceCount(); ++i) {
		ResetAction(i);		
	}
}

void PlayerLogic::ResetAction(int i) {
	if (_currentActions[i] != ActionType::Unknown) {
		ActionUnselectedMessage msg{ _id, i, _currentActions[i] };
		_currentActions[i] = ActionType::Unknown;
		Notify(msg);
	}
}

void PlayerLogic::SetAction(int index, ActionType action) {
	assert(_currentActions[index] == ActionType::Unknown || _currentActions[index] == ActionType::NotAvailable);
	_currentActions[index] = action;
	ActionSelectedMessage msg{ _id, index, action };
	Notify(msg);
}

ActionType PlayerLogic::GetAction(int index) const {
	assert(_currentActions[index] != ActionType::NotAvailable);
	return _currentActions[index];
}

bool PlayerLogic::AreActionsSelected() const {
	for (int i = 0; i < GetDiceCount(); ++i) {
		if (_currentActions[i] == ActionType::Unknown || _currentActions[i] == ActionType::NotAvailable)
			return false;
	}
	return true;
}

bool PlayerLogic::IsActionSelected(ActionType action) const {
	for (int i = 0; i < GetDiceCount(); ++i) {
		if (_currentActions[i] == action)
			return true;
	}
	return false;
}

void PlayerLogic::SortDices() {
	auto dices = _currentDices;
	std::sort(dices.begin(), dices.begin() + GetDiceCount());
	for (int i = 0; i < GetDiceCount(); ++i) {
		SetDiceValue(i, dices[i]);
	}
}

bool PlayerLogic::AreActionsDone() const {
	return _actionExecutionState.IsComplete();
}

void PlayerLogic::ActionExecutionState::Reset(const PlayerLogic& p) {
	actionsCount = p.GetDiceCount();
	nextAction = 0;	

	std::fill(actions.begin(), actions.end(), std::tuple<int, ActionType>{ 0, ActionType::Unknown });

	for (int i = 0; i < actionsCount; ++i) {
		actions[i] = { p.GetDice(i), p.GetAction(i) };
	}

	std::sort(actions.begin(), actions.begin() + actionsCount, [](auto& l, auto& r) {
		return std::get<1>(l) < std::get<1>(r);
		});
}

std::tuple<int, ActionType> PlayerLogic::ActionExecutionState::Current() const {
	return actions[nextAction];
}

void PlayerLogic::ActionExecutionState::Next() {
	assert(!IsComplete());
	nextAction++;
}

bool PlayerLogic::ActionExecutionState::IsComplete() const {
	return nextAction >= actionsCount;
}

void PlayerLogic::BeginExecuteActions() {
	_actionExecutionState.Reset(*this);
}

void PlayerLogic::ExecuteNextAction() {
	_actionExecutionState.Next();
}

int PlayerLogic::GetPolicyIndex(::Policies dropped) {
	auto it = std::find(_policiesInHands.begin(), _policiesInHands.end(), dropped);
	assert(it != _policiesInHands.end());
	return std::distance(_policiesInHands.begin(), it);
}

void PlayerLogic::BeginProgressStage() {
	_progressState.Reset(*this);
}

void PlayerLogic::ProgressState::Reset(const PlayerLogic& p) {	
	upgradedTracksCount = 0;
	tracksLeft = p._availableProgressCount;
	isComplete = false;
}

bool PlayerLogic::ProgressState::IsComplete(const PlayerLogic& p) const {
	return isComplete || !(
		p.CanUpgradeTrack(ProgressTrackType::Economy, 0, false)
		|| p.CanUpgradeTrack(ProgressTrackType::Culture, 0, false)
		|| p.CanUpgradeTrack(ProgressTrackType::Military, 0, false));
}

void PlayerLogic::ProgressState::Complete(const PlayerLogic& p) {
	isComplete = true;
}

void PlayerLogic::ProgressState::TrackIncreased() {
	upgradedTracksCount++;	
}

bool PlayerLogic::ProgressState::HasUpgradedTracks() const {
	return upgradedTracksCount != 0;
}

void PlayerLogic::CompleteProgressStep() {
	_progressState.Complete(*this);
}

bool PlayerLogic::IsProgressDone() const {
	return _progressState.IsComplete(*this);
}

int PlayerLogic::GetProgressSteps() const {
	return _availableProgressCount;
}

void PlayerLogic::EndProgressStage() {
	_progressState.Complete(*this);
}

void PlayerLogic::BeginActiveTask(std::string_view reason) {
	assert(_activeTasks >= 0);
	_activeTasks++;	
	INFO("Player {} starts active task due to '{}'. Total {}", GetId(), reason, _activeTasks);
}

void PlayerLogic::EndActiveTask(std::string_view reason) {
	_activeTasks--;
	assert(_activeTasks >= 0);
	INFO("Player {} ends active task due to '{}'. Total {}", GetId(), reason, _activeTasks);
}

void PlayerLogic::BeginExtraProgress(ProgressTrackType track, int discont, ExtraProgressCallback cb) {
	
	assert(_extraProgressCallback == nullptr);
	_extraProgressCallback = cb;

	BeginActiveTask("extra progress");

	BeginExtraProgressMessage msg{ GetId(), discont, track };
	Notify(msg);
}

void PlayerLogic::EndExtraProgress() {
	EndActiveTask("extra progress");

	ExtraProgressCallback cb;
	std::swap(cb, _extraProgressCallback);
	assert(cb != nullptr);
	cb(*this);
}

ConstPlayerPoliciesManipulator PlayerLogic::Policies() const {
	return ConstPlayerPoliciesManipulator{ *this };
}

//void PlayerLogic::BeginDropPolicy(PolicyDroppedCallback cb) {
//	assert(_dropPolicyCallback == nullptr);
//	_dropPolicyCallback = cb;
//
//	BeginActiveTask("drop policy");
//	BeginDropPolicyMessage msg{ GetId() };
//	Notify(msg);
//}
//
//void PlayerLogic::EndDropPolicy(::Policies policy) {
//
//	assert(_dropPolicyCallback != nullptr);
//	
//	RemovePolicy(policy);
//
//	auto cb = std::move(_dropPolicyCallback);
//	cb(policy);
//
//	EndActiveTask("drop policy");
//}

void PlayerLogic::RemovePolicy(::Policies policy) {
	INFO("Player {} removing policy {}", GetId(), (int)policy);

	auto it = std::find(_policiesInHands.begin(), _policiesInHands.end(), policy);
	assert(it != _policiesInHands.end());
	
	{
		auto index = As<int>(std::distance(_policiesInHands.begin(), it));
		_policiesInHands.erase(it);
		PolicyRemovedFromHandsMessage msg{ GetId(), policy, index };
		Notify(msg);
	}

	_world->Policies().Drop(policy);
}

//void PlayerLogic::BeginDropDiscovery(DiscoveryDroppedCallback cb) {
//
//	assert(_discoveryDroppedCallback == nullptr);
//	_discoveryDroppedCallback = cb;
//	
//	BeginActiveTask("drop discovery");
//
//	if (_discoveries.empty()) {
//		cb(0);
//		return;
//	}
//
//	BeginDropDiscoveryMessage msg{ GetId() };
//	Notify(msg);
//}

//void PlayerLogic::EndDropDiscovery(discovery_type discovery) {
//	assert(_discoveryDroppedCallback != nullptr);
//
//	if (discovery != discovery_type::no) {
//		RemoveDiscovery(discovery);
//		_discoveryDroppedCallback(1);
//	}
//	else {
//		_discoveryDroppedCallback(0);
//	}
//
//	EndActiveTask("drop discovery");
//}

void PlayerLogic::BeginSelectDiscoveryFromPool(DiscoverySelectedCallback cb) {
	assert(_discoverySelectedCallback == nullptr);
	_discoverySelectedCallback = cb;
	BeginActiveTask("select discovery from pool");

	SelectDiscoveryFromPoolMessage msg{ GetId() };
	Notify(msg);
}

void PlayerLogic::EndSelectDiscoveryFromPool(discovery_type discovery) {

	AddDiscovery(discovery, -1, -1, As<int>(discovery));

	EndActiveTask("select discovery from pool");
}

void PlayerLogic::BeginSelectDiscoveryFromHands(DiscoverySelectedCallback cb) {
	assert(_discoverySelectedCallback == nullptr);
	_discoverySelectedCallback = cb;
	BeginActiveTask("select discovery from pool");

	SelectDiscoveryFromHandsMessage msg{ GetId() };
	Notify(msg);
}

void PlayerLogic::EndSelectDiscoveryFromHands(discovery_type discovery) {

	DiscoverySelectedCallback cb = std::move(_discoverySelectedCallback);
	assert(cb != nullptr);
	cb(discovery);

	EndActiveTask("select discovery from pool");
}


void PlayerLogic::BeginSelectAction(int diceValue, bool allowMilitaty, SelectActionCallback cb) {
	assert(_selectActionCallback == nullptr);
	assert(cb != nullptr);
	_selectActionCallback = cb;

	BeginActiveTask("select action");

	SelectActionMessage msg{ GetId(), diceValue, allowMilitaty };
	Notify(msg);
}

void PlayerLogic::EndSelectionAction(ActionType action) {

	EndActiveTask("select action");

	SelectActionCallback cb;
	std::swap(cb, _selectActionCallback);
	assert(cb != nullptr);
	cb(action);
}

void PlayerLogic::BeginExecuteAction(int diceValue, ActionType action, ActionCompleteCallback cb) {
	assert(_executeActionCallback == nullptr);
	assert(cb != nullptr);
	_executeActionCallback = cb;

	BeginActiveTask("execute action");

	ExecuteActionMessage msg{ GetId(), diceValue, action };
	Notify(msg);
}

void PlayerLogic::EndExecuteAction() {
	
	EndActiveTask("execute action");

	ActionCompleteCallback cb;
	std::swap(_executeActionCallback, cb);
	assert(cb != nullptr);
	cb();
}

void PlayerLogic::BeginSelectPolicyFromActiveDeck(SelectPolicyCallback cb) {
	assert(_policySelected == nullptr);
	_policySelected = cb;

	SelectPolicyFromActiveDeckMessage msg{ GetId() };
	Notify(msg);
}

void PlayerLogic::EndSelectPolicyFromActiveDeck(::Policies policy) {

	EndActiveTask("select policy from active deck");

	SelectPolicyCallback cb;
	std::swap(cb, _policySelected);
	assert(cb != nullptr);
	cb(policy);
}

void PlayerLogic::BeginSelectBonus(int army, int money, int points, int population, ActionCompleteCallback cb) {
	assert(_selectBonusCallback == nullptr);
	_selectBonusCallback = cb;

	BeginActiveTask("select bonus");

	SelectBonusMessage msg{ GetId(), army, money, points, population };
	Notify(msg);
}

void PlayerLogic::EndSelectBonus(int army, int money, int points, int population) {

	AddArmy(army, true);
	AddMoney(money);
	AddPoints(points);
	AddPopulation(population);	

	ActionCompleteCallback cb;
	std::swap(cb, _selectBonusCallback);
	assert(cb != nullptr);
	cb();

	EndActiveTask("select bonus");
}

void PlayerLogic::BeginSelectPolicyFromHandsToActivate(SelectPolicyCallback cb) {
	BeginSelectPolicyFromHands(PolicySelectionReasonType::Activate, cb);
}

void PlayerLogic::BeginSelectPolicyFromHandsToDrop(SelectPolicyCallback cb) {
	BeginSelectPolicyFromHands(PolicySelectionReasonType::Drop, cb);
}

void PlayerLogic::BeginSelectPolicyFromHands(PolicySelectionReasonType reason, SelectPolicyCallback cb) {
	assert(_policySelected == nullptr);
	_policySelected = cb;
	BeginActiveTask("select policy from hands");

	SelectPolicyFromHandsMessage msg{ GetId(), reason };
	Notify(msg);
}

void PlayerLogic::EndSelectPolicyFromHands(::Policies policy) {

	SelectPolicyCallback cb = std::move(_policySelected);
	
	assert(cb != nullptr);
	cb(policy);

	EndActiveTask("select policy from hands");
}

void PlayerLogic::ExecuteEndGamePerks() {
	for (auto& perk : _endGamePerks) {
		perk(*this);
	}
}
