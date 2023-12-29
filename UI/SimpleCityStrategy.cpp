#include "SimpleCityStrategy.h"

#include <PlayerLogic.h>
#include <PoliciesManipulator.h>
#include <PolicyTemplate.h>
#include <WorldLogic.h>

#include <cassert>

#include "IUserInput.h"
#include "IUserInputHandler.h"

ActionType SimpleCityStrategy::SelectAction(const PlayerLogic& player,
                                            int diceValue) {
    auto action = (ActionType)diceValue;

    while ((int)action > 0) {
        if (player.IsActionSelected(action)) {
            action = (ActionType)((int)action - 1);
        } else {
            return action;
        }
    }

    action = (ActionType)(diceValue + 1);
    while ((int)action <= (int)ActionType::Development) {
        if (player.IsActionSelected(action)) {
            action = (ActionType)((int)action + 1);
        } else {
            return action;
        }
    }

    assert(false && "Should select anything");
    exit(-1);
}

void SimpleCityStrategy::ExecuteActionAsync(IUserInputHandler& user,
                                            ActionType action,
                                            std::function<void()> cb) {}

void SimpleCityStrategy::SelectLawPolicy(
    IUserInputHandler& user, PoliciesType a, PoliciesType b,
    std::function<void(PoliciesType selected, PoliciesType dropped)> cb) {
    cb(a, b);
}

void SimpleCityStrategy::SelectExpedition(IUserInputHandler& user,
                                          const WorldLogic& world,
                                          std::function<void(int)> cb) {
    auto& player = world.GetPlayer(user.PlayerId());
    auto army = player.GetArmySize();

    for (int i = GetExpeditionsCount() - 1; i >= 0; --i) {
        if (!world.IsExpeditionAvailable(i)) continue;

        auto& info = world.GetExpeditionInfo(i);
        if (army >= info.armyRequire) {
            cb(i);
            return;
        }
    }

    cb(-1);
}

void SimpleCityStrategy::MakeProgress(
    IUserInputHandler& user, const WorldLogic& world,
    std::function<void(ProgressTrackType)> cb) {
    auto& player = world.GetPlayer(user.PlayerId());
    auto money = player.GetMoney();

    bool upgraded = false;
    for (int j = 0; j < As<int>(ProgressTrackType::Count); ++j) {
        auto track = As<ProgressTrackType>(j);
        if (player.CanUpgradeTrack(track, 0, false)) {
            auto cost = player.GetTrackProgressCost(track, 0, false);
            if (money >= cost) {
                cb(track);
                money -= cost;
                upgraded = true;
                break;
            }
        }
    }

    if (!upgraded) {
        cb(ProgressTrackType::Unknown);
    }
}

void SimpleCityStrategy::SelectPolicy(IUserInputHandler& user,
                                      const WorldLogic& world,
                                      SelectPolicyCallback cb) {
    auto& player = world.GetPlayer(user.PlayerId());

    auto policy =
        player.GetPolicies()
            .InHands()
            .Where([](const PlayerLogic& player, const PolicyTemplate& policy) {
                return policy.GetEffect().CanApply(player);
            })
            .FirstOrNull();

    if (policy == nullptr) {
        cb(PoliciesType::policy_unknown);
        return;
    }

    cb(policy->GetType());
}

void SimpleCityStrategy::SelectPolicyToDrop(IUserInputHandler& user,
                                            const WorldLogic& world,
                                            SelectPolicyCallback cb) {
    auto& player = world.GetPlayer(user.PlayerId());

    auto policy = player.GetPolicies().InHands().FirstOrNull();
    if (policy != nullptr) {
        cb(policy->GetType());
    } else {
        cb(PoliciesType::policy_unknown);
    }
}

void SimpleCityStrategy::SelectDiscoveryFromHands(IUserInputHandler& user,
                                                  const WorldLogic& world,
                                                  SelectDiscoveryCallback cb) {
    auto& player = world.GetPlayer(user.PlayerId());

    if (player.GetDiscoveries().empty()) {
        cb(discovery_type::no);
        return;
    }

    cb(player.GetDiscoveries().front());
}

void SimpleCityStrategy::SelectDiscoveryFromPool(IUserInputHandler& user,
                                                 const WorldLogic& world,
                                                 SelectDiscoveryCallback cb) {
    auto& player = world.GetPlayer(user.PlayerId());

    auto i = rand() % 3;
    discovery_type t = discovery_type::no;
    switch (i) {
        case 0:
            t = discovery_type::red;
            break;
        case 1:
            t = discovery_type::blue;
            break;
        case 2:
            t = discovery_type::green;
            break;
    }

    assert(t != discovery_type::no);

    cb(t);
}

void SimpleCityStrategy::SelectPolicyFromActiveDeck(IUserInputHandler& user,
                                                    const WorldLogic& world,
                                                    SelectPolicyCallback cb) {
    auto& player = world.GetPlayer(user.PlayerId());

    if (player.GetPoliciesInActiveDeckCount() == 0) {
        cb(PoliciesType::policy_unknown);
        return;
    }

    auto policy = player.GetPolicyInActiveDeck(0);
    cb(policy);
}