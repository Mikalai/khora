#include <iostream>
#include <Locale/Translate.h>
#include <PolicyTemplate.h>
#include <WorldLogic.h>
#include <PlayerLogic.h>
#include "ConsoleUserInput.h"

class WorldLogic;

ConsoleUserInput::ConsoleUserInput(int playerId, WorldLogic& world)
	: GeneralUserInput(playerId, world) {

	_thread = std::thread(&ConsoleUserInput::TerminalInput, this);	
}

ConsoleUserInput::~ConsoleUserInput() {
	_terminate = true;
	_cv.notify_all();

	if (_thread.joinable()) {
		_thread.join();
	}
}

void ConsoleUserInput::TerminalInput() {

	while (!_terminate) {

		CallbackFunction cb;
		{
			if (_callbacks.empty()) {
				std::unique_lock<std::mutex> lock{ _cs };
				_cv.wait(lock);
			}

			if (_callbacks.empty())
				continue;

			cb = _callbacks.front();
		}

		while (!_terminate) {
			if (cb(std::cin))
				break;
		}

		{
			std::unique_lock<std::mutex> lock{ _cs };
			_callbacks.pop_front();
		}
	}
}

//
//void ConsoleUserInput::SelectArgosLevel2() {
//	int code = 0;
//	while (code < 1 || code > 4) {
//		std::cout << tr("Select 2 %ARMY%, or 3 %COIN%, or 4 %POINT%, or 5 %POPULATION% [1 - army, 2 - coin, 3 - point, 4 - population]:") << std::endl;
//		std::cin >> code;
//	}
//
//	ActivateArgosLevel2Perk(code);
//}
//
//void ConsoleUserInput::SelectThebesLevel2() {
//	auto& player = GetPlayer();
//
//	if (player.GetGlory() == 0)
//		return;
//
//	std::cout << tr("Spend 1 %GLORY% to get 2 %COIN% and 4 %POINT% [0 - no, 1 - yes]:") << std::endl;
//	int code;
//	std::cin >> code;
//	if (code == 0)
//		return;
//
//	ActivateThebesLevel2Perk();
//}
//
//void ConsoleUserInput::SelectExpedition(SelectExpeditionCallback cb) {
//	auto& world = GetWorld();
//	auto& player = GetPlayer();
//
//	while (true) {
//		std::cout << tr("Select expedition:") << std::endl;
//
//		for (int i = 0; i < GetExpeditionsCount(); ++i) {
//			auto& e = GetExpeditionTemplate(i);
//			std::cout << i << ": ";
//
//			if (world.IsExpeditionAvailable(i)) {
//				for (int j = 0; j < 3; ++j) {
//					if (e.discoveries[j] != discovery_type::no) {
//						switch (e.discoveries[j])
//						{
//						case discovery_type::red:
//							std::cout << "(r)";
//							break;
//						case discovery_type::blue:
//							std::cout << "(b)";
//							break;
//						case discovery_type::green:
//							std::cout << "(g)";
//							break;
//						case discovery_type::epic_red:
//							std::cout << "<<r>>";
//							break;
//						case discovery_type::epic_blue:
//							std::cout << "<<b>>";
//							break;
//						case discovery_type::epic_green:
//							std::cout << "<<g>>";
//							break;
//						default:
//							break;
//						}
//					}
//					std::cout << ' ';
//				}
//
//				std::cout << e.armyRequire << "|" << e.armyLosses << " m" << e.rewardMoney << "_p" << e.rewardPoints;
//			}
//			else {
//				std::cout << "======";
//			}
//
//			std::cout << std::endl;
//		}
//
//		int code;
//		std::cin >> code;
//
//		if (code < 0 || code >= GetExpeditionsCount())
//			continue;
//
//		auto& e = GetExpeditionTemplate(code);
//		if (world.IsExpeditionAvailable(code) && player.GetArmySize() >= e.armyRequire) {
//			ActivateExpedition(code, cb);
//		}
//		else {
//			std::cout << tr("Player can't go to expedition") << std::endl;
//		}
//	}
//}
//
//void ConsoleUserInput::AdvanceAnyTrack(int discont)
//{
//	auto& player = GetPlayer();
//
//	while (true) {
//		auto money = player.GetMoney();
//		std::array<bool, 3> canUpgrade;
//		for (int i = 0; i < 3; ++i) {
//			auto track = (ProgressTrackType)i;
//			canUpgrade[i] = player.CanUpgradeTrack(track, discont) ? money >= player.GetTrackProgressCost(track, discont) : false;
//		}
//		
//		std::cout << tr("You can advance");
//		
//		if (canUpgrade[0])
//			std::cout << tr("1 - economy for ") << player.GetTrackProgressCost(ProgressTrackType::Economy, discont);
//		
//		if (canUpgrade[1])
//			std::cout << tr("2 - culture for ") << player.GetTrackProgressCost(ProgressTrackType::Culture, discont);
//		
//		if (canUpgrade[2])
//			std::cout << tr("3 - military for ") << player.GetTrackProgressCost(ProgressTrackType::Military, discont);
//
//		int code = 0;
//		std::cin >> code;
//
//		if (code <= 0 || code >= 3)
//			return;
//
//		auto track = (ProgressTrackType)code;
//
//		DoTrackAdvance(track, discont);
//	}
//}
//
//void ConsoleUserInput::PlayOstracism()
//{
//}
//
//void ConsoleUserInput::TakeDiscovery(int count)
//{
//}
//
//void ConsoleUserInput::TakePolicies(int count)
//{
//}
//
//void ConsoleUserInput::AdvanceAnyTrackForFree() {
//	auto& player = GetPlayer();
//
//	while (true) {
//		std::cout << tr("You can advance any track for free. Select track [1 - economy, 2 - culture, 3 - military, 0 - nothing]:") << std::endl;
//		int code = 0;
//		std::cin >> code;
//
//		if (code == 0)
//			return;
//
//		if (code == 1) {
//			if (player.GetEconomy() == max_city_track_level) {
//				std::cout << tr("Selected track has maximum value. Are you sure? [0 - select again, 1 - sure]:") << std::endl;
//				std::cin >> code;
//				if (code == 0)
//					continue;
//				return;
//			}
//			else {
//				AdvanceEconomyForFree();
//			}
//		}
//		else if (code == 2) {
//			if (player.GetCultureLevel() == max_city_track_level) {
//				std::cout << tr("Selected track has maximum value. Are you sure? [0 - select again, 1 - sure]:") << std::endl;
//				std::cin >> code;
//				if (code == 0)
//					continue;
//				return;
//			}
//			else {
//				AdvanceCultureForFree();
//			}
//		}if (code == 3) {
//			if (player.GetMilitaryLevel() == max_city_track_level) {
//				std::cout << tr("Selected track has maximum value. Are you sure? [0 - select again, 1 - sure]:") << std::endl;
//				std::cin >> code;
//				if (code == 0)
//					continue;
//				return;
//			}
//			else {
//				AdvanceMilitaryForFree();
//			}
//		}
//	}
//}
//
//void ConsoleUserInput::AdvanceMilitaryTrack(int discont) {
//	auto& player = GetPlayer();
//
//	auto cost = player.GetTrackProgressCost(ProgressTrackType::Military, discont);
//	if (cost > player.GetMoney()) {
//		std::cout << tr("You can't advance military track because you don't have enough money. Need ") << cost << tr(", has ") << player.GetMoney() << std::endl;
//		return;
//	}
//	
//	int code = 0;
//	while (true) {
//		std::cout << tr("Do you want upgrade military track for ") << cost << tr(" drahmas? [1 - yes, 2 - no]") << std::endl;
//		std::cin >> code;
//
//		if (code == 1) {
//			DoTrackAdvance(ProgressTrackType::Military, discont);
//			return;
//		}
//		else if (code == 2) {
//			std::cout << tr("No upgrade.") << std::endl;
//			return;
//		}
//	}	
//}
//
//void ConsoleUserInput::DropPolicies(int count) {
//	auto& player = GetPlayer();
//
//	auto hasCount = player.GetPoliciesInHandCount();
//	if (hasCount <= count) {
//		DoDropPolicies(count);
//	}
//	else {
//
//	}
//}
//
//void ConsoleUserInput::DropDiscovery(DropDiscoveryCallback cb) {
//	auto& player = GetPlayer();
//	
//	if (player.GetDiscoveries().empty())
//		return;
//
//	while (true) {
//		std::cout << tr("Selelct discovery to drop: ") << std::endl;
//		for (int i = 0; i < player.GetDiscoveries().size(); ++i) {
//			auto d = player.GetDiscoveries()[i];
//			std::cout << i << " - ";
//			switch (d)
//			{
//			case discovery_type::red:
//				std::cout << tr("red");
//				break;
//			case discovery_type::blue:
//				std::cout << tr("blue");
//				break;
//			case discovery_type::green:
//				std::cout << tr("green");
//				break;
//			case discovery_type::epic_red:
//				std::cout << tr("epic red");
//				break;
//			case discovery_type::epic_blue:
//				std::cout << tr("epic blue");
//				break;
//			case discovery_type::epic_green:
//				std::cout << tr("epic green");
//				break;
//			}
//			std::cout << std::endl;
//		}
//
//		int code = 0;
//		std::cin >> code;
//
//		if (code >= 0 && code < player.GetDiscoveries().size()) {
//			DoDropDiscovery(player.GetDiscoveries()[code]);
//			return;
//		}
//	}
//}
//
//void ConsoleUserInput::PlayPersiaCampaign() {
//	DoPersiaCampaign();
//}
//
//void ConsoleUserInput::DoAnyActionExceptMilitary() {
//	int code = -1;
//	while (code < 0 || code == 4 || code > 6) {
//		std::cout << tr("Select any action except military. [0 - philosophy, 1 - law, 2 - culture, 3 - trade, 5 - policy, 6 - expand]:") << std::endl;
//		std::cin >> code;
//
//		if (code == 0) {
//			DoPhilosophyAction();
//		}
//		else if (code == 1) {
//			DoLawAction();
//		} 
//		else if (code == 2) {
//			DoCultureAction();
//		}
//		else if (code == 3) {
//			DoTradeAction();
//		}
//		else if (code == 5) {
//			DoPolicyAction();
//		}
//		else if (code == 6) {
//			DoExpandAction();
//		}
//	}
//}
//
//void ConsoleUserInput::DoPhilosophyAction() {
//	GeneralUserInput::DoPhilosophyAction();
//}
//
//void ConsoleUserInput::DoLawAction() {
//	GeneralUserInput::DoLawAction();
//}
//
//void ConsoleUserInput::DoCultureAction() {
//	GeneralUserInput::DoCultureAction();
//}
//
//void ConsoleUserInput::DoTradeAction() {
//
//}
//
//void ConsoleUserInput::DoMilitaryAction() {
//
//}
//
//void ConsoleUserInput::DoPolicyAction() {
//
//}
//void ConsoleUserInput::DoExpandAction() {
//
//}

//void ConsoleUserInput::SelectPolicy(Policies* a, int count, SelectPolicyCallback cb) {
//	std::array<const PolicyTemplate*, 40> policies;
//	for (int i = 0; i < count; ++i) {
//		policies[i] = &GetPolicyTemplate(a[i]);
//	}
//
//	while (true) {		
//				
//		std::cout << tr("Select policy: ");
//		for (int i = 0; i < count; ++i) {
//			std::cout << i << " - " << policies[i]->GetName() << tr(" or 2 - ") << policies[i]->GetName() << std::endl;
//		}
//		int code = 0;
//		std::cin >> code;
//
//		if (code >= 0 && code < count) {
//			ActivatePolicy(a, count, code, cb);
//			return;
//		}
//	}
//}

//void ConsoleUserInput::DoDraft() 
//{}

//void ConsoleUserInput::Complete() {
//	GeneralUserInput::Complete();
//	_terminate = true;
//}

void ConsoleUserInput::AddCallback(ConsoleUserInput::CallbackFunction cb) {
	{
		std::unique_lock<std::mutex> lock{ _cs };
		_callbacks.push_back(cb);
	}
	_cv.notify_all();
}

void ConsoleUserInput::SelectPlayersCountAsync(std::function<void(int count)> cb) {
	std::cout << tr("Select players count [2-4]: ") << std::endl;

	AddCallback([cb](std::istream& stream) {

		if (DefaultSelect) {
			cb(4);
			return true;
		}

		int count = 0;
		stream >> count;
		if (count >= 2 && count <= 4) {
			cb(count);
			return true;
		}

		std::cout << tr("Khora can be played with 2 to 4 players") << std::endl;
		return false;

	});
}

void ConsoleUserInput::SelectCityColorAsync(std::function<void(player_color color)> cb) {
	std::cout << tr("Select color [") << tr("red") << ", " << tr("black") << ", " << tr("blue") << ", " << tr("green") << "]: " << std::endl;

	AddCallback([this, cb](std::istream& stream) {
		
		if (DefaultSelect) {
			cb(red);
			return true;
		}

		std::string color;
		std::cin >> color;
		if (color != tr("red") && color != tr("black") && color != tr("blue") && color != tr("green")) {
			std::cout << tr("Sorry, but at the moment only ") << tr("red") << ", " << tr("black") << ", " << tr("blue") << ", " << tr("green") << " are available." << std::endl;
			return false;
		}
		else {
			cb(GetColor(color));
			return true;
		}
	});
}

void ConsoleUserInput::SelectCityAsync(std::function<void(Cities city)> cb) {

	std::cout << tr("Select city [") << tr("Miles") << ", " << tr("Thebes") << ", "
		<< tr("Athens") << ", " << tr("Sparta") << ", " << tr("Argos") << ", " << tr("Olympia")
		<< ", " << tr("Corinth") << "]:" << std::endl;

	AddCallback([this,cb](std::istream& stream) {
		
		if (DefaultSelect) {
			cb(city_milet);
			return true;
		}

		std::string city;
		stream >> city;
		if (city != tr("Miles")
			&& city != tr("Thebes")
			&& city != tr("Athens")
			&& city != tr("Sparta")
			&& city != tr("Argos")
			&& city != tr("Olympia")
			&& city != tr("Corinth")) {
			std::cout << tr("Sorry, but Khora has only ") << tr("Miles") << ", " << tr("Thebes") << ", "
				<< tr("Athens") << ", " << tr("Sparta") << ", " << tr("Argos") << ", " << tr("Olympia")
				<< ", " << tr("Corinth") << " are available." << std::endl;
			return false;
		}
		else {
			cb(GetCity(city));
			return true;
		}
	});
}

void ConsoleUserInput::SelectPolicyFromDraftAsync(std::function<void(Policies policy)> cb) {
	std::cout << tr("Select one policy and rest give to the next player. [");
	int index = 0;

	GetPlayer().Draft().ForEach([&index](Policies policy) {
		auto& tmp = GetPolicyTemplate(policy);
		std::cout << index << " - " << tr(tmp.GetName()) << std::endl;
		});

	AddCallback([this, cb](std::istream& stream) {

		if (DefaultSelect) {
			cb(GetPlayer().Draft().Random());
			return true;
		}

		int code = -1;
		stream >> code;

		if (code >= 0 && code < GetPlayer().Draft().Size()) {
			cb(GetPlayer().Draft().Select(code));
			return true;
		}

		return false;
	});
}