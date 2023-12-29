#include "WorldLogicPrepare.h"

#include <Messages/All.h>

#include <algorithm>
#include <cassert>
#include <chrono>
#include <random>

#include "EventsManipulator.h"
#include "PoliciesManipulator.h"
#include "WorldLogic.h"

WorldLogicPrepare::WorldLogicPrepare(WorldLogic& logic) : _world{logic} {}

void WorldLogicPrepare::UpgradeCitiesToFirstLevel() {
    for (int i = 0; i < _world.GetPlayersCount(); ++i) {
        auto& player = _world.GetPlayer(i);
        player.DoExpand([]() {});
    }
}

void WorldLogicPrepare::ShufflePolicies() { _world.Policies().Shuffle(); }

void WorldLogicPrepare::ShuffleEvents() { _world.Events().Shuffle(); }

void WorldLogicPrepare::GivePolicies() {
    for (int i = 0; i < 5; ++i) {
        _world.GetPlayers().ForEach([this](PlayerLogic& player) {
            player.AddPolicy(_world.Policies().GetNextPolicy(), false);
        });
    }
}

void WorldLogicPrepare::ChangeDraft() {
    assert(_world.GetPlayers().All([](const PlayerLogic& player) {
        return player.GetPoliciesInHandCount() <= 5;
    }));

    auto cur = _world.GetPlayer(0).TakeDraft();
    for (int i = 1; i < _world.GetPlayersCount(); ++i) {
        auto& player = _world.GetPlayer(i);
        auto tmp = player.TakeDraft();
        player.GiveDraft(std::move(cur));
        cur = std::move(tmp);
    }

    bool needDraft = cur.size() > 1;

    _world.GetPlayer(0).GiveDraft(std::move(cur));

    if (needDraft) {
        _world.GetPlayers().ForEach([](PlayerLogic& logic) {
            BeginDraftMessage msg{logic.GetId()};
            logic.Notify(msg);
        });
    }
}

void WorldLogicPrepare::EndDraft() { _world.CompleteDraft(); }

void WorldLogicPrepare::BeginDraft() {
    _world.GetPlayers().ForEach(
        [](PlayerLogic& player) { player.BeginDraft(); });
}

void WorldLogicPrepare::SelectPlayersCount() {
    BeginSelectPlayersCountMessage msg{};
    _world.Notify(msg);
}

void WorldLogicPrepare::SelectCityColor() {
    BeginSelectCityColorMessage msg{};
    _world.Notify(msg);
}

void WorldLogicPrepare::CreateExpeditions() {
    for (int i = 0; i < GetExpeditionsCount(); ++i) {
        _world._expeditions[i] = true;
        ExpeditionAddedMessage msg{i};
        _world.Notify(msg);
    }
}

void WorldLogicPrepare::SelectCities() {
    BeginCitySelectionMessage msg{};
    _world.Notify(msg);
}
