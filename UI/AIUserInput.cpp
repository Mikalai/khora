#include <WorldLogic.h>
#include "SimpleCityStrategy.h"
#include "AIUserInput.h"

AIUserInput::AIUserInput(int playerId, WorldLogic& world)
	: GeneralUserInput{ playerId, world } {

}

void AIUserInput::SelectPlayersCountAsync(std::function<void(int count)> cb) {

}

void AIUserInput::SelectActionAsync(int diceValue, bool allowMilitary, SelectActionsCallback cb) {
	assert(_strategy != nullptr);
	auto v = _strategy->SelectAction(GetPlayer(), diceValue);
	cb(v);
}

void AIUserInput::SelectCityColorAsync(std::function<void(player_color color)> cb) {	
	for (int i = 0; i < PlayerId(); ++i) {
		if (GetWorld().GetPlayer(i).GetColor() == player_color_unknown) {
			PostWorldUpdateAction([cb, this](WorldLogic& world) {
				this->SelectCityColorAsync(cb);
				});
			return;
		}
	}

	for (int i = 0; i < players_count; ++i) {
		bool freeColor = true;
		for (int j = 0; j < PlayerId(); ++j) {
			auto& p = GetWorld().GetPlayer(j);
			if (p.GetColor() == i) {
				freeColor = false;
				break;
			}
		}

		if (freeColor) {
			cb((player_color)i);
			return;
		}
	}

	assert(false && "At least one color should be free");
}

void AIUserInput::ThrowDiceAsync(int diceIndex, std::function<void(int diceIndex, int diceValue)> cb) {
	cb(diceIndex, NextRandomDiceValue());
}

void AIUserInput::SelectPolicyFromDraftAsync(std::function<void(Policies policy)> cb) {
	cb(GetWorld().GetPlayer(PlayerId()).Draft().Random());
}

void AIUserInput::SelectCityAsync(std::function<void(Cities city)> cb) {

	for (int i = 0; i < PlayerId(); ++i) {
		if (GetWorld().GetPlayer(i).GetCity() == city_unknown) {
			PostWorldUpdateAction([cb, this](WorldLogic& world) {
				this->SelectCityAsync(cb);
				});
			return;
		}
	}

	for (int i = 0; i < cities_count; ++i) {
		bool freeCity = true;
		for (int j = 0; j < PlayerId(); ++j) {
			auto& p = GetWorld().GetPlayer(j);
			if (p.GetCity() == i) {
				freeCity = false;
				break;
			}			
		}

		if (freeCity) {
			auto city = (Cities)i;
			_strategy = CreateCityStrategy(city);
			cb(city);
			return;
		}
	}

	assert(false && "At least one city should be free");
}


std::unique_ptr<ICityStrategy> AIUserInput::CreateCityStrategy(Cities city) {
	return std::make_unique<SimpleCityStrategy>();
}

void AIUserInput::SelectLawPolicyAsync(Policies a, Policies b, std::function<void(Policies selected, Policies dropped)> cb) {
	assert(_strategy != nullptr);
	
	if (a == Policies::policy_unknown || b == Policies::policy_unknown) {
		if (a != Policies::policy_unknown) {
			cb(a, b);
		}
		else {
			cb(b, a);
		}
		return;
	}

	_strategy->SelectLawPolicy(*this, a, b, cb);
}

void AIUserInput::SelectExpeditionAsync(std::function<void(int expedition)> cb) {
	assert(_strategy != nullptr);
	_strategy->SelectExpedition(*this, GetWorld(), cb);
}

void AIUserInput::MakeProgressAsync(std::function<void(ProgressTrackType)> cb) {
	_strategy->MakeProgress(*this, GetWorld(), cb);
}

void AIUserInput::SelectPolicyFromHandsAsync(PolicySelectionReasonType reason, SelectPolicyCallback cb) {
	if (reason == PolicySelectionReasonType::Activate)
		_strategy->SelectPolicy(*this, GetWorld(), cb);
	else if (reason == PolicySelectionReasonType::Drop) {
		_strategy->SelectPolicyToDrop(*this, GetWorld(), cb);
	}
	else {
		assert(false && "Unexpected policy selection reason");
	}
}

void AIUserInput::SelectDiscoveryFromHandsAsync(SelectDiscoveryCallback cb) {
	_strategy->SelectDiscoveryFromHands(*this, GetWorld(), cb);
}

void AIUserInput::SelectDiscoveryFromPoolAsync(SelectDiscoveryCallback cb) {
	_strategy->SelectDiscoveryFromPool(*this, GetWorld(), cb);
}

void AIUserInput::SelectPolicyFromActiveDeckAsync(SelectPolicyCallback cb) {
	_strategy->SelectPolicyFromActiveDeck(*this, GetWorld(), cb);
}