#include "OrderedByDicesPlayers.h"

#include "PlayerLogic.h"
#include "WorldLogic.h"

OrderedByDicesPlayers::OrderedByDicesPlayers(WorldLogic& world)
    : _world{world} {
    for (int i = 0; i < _world.GetPlayersCount(); ++i) {
        auto sum = 0;
        for (int j = 0; j < _world.GetPlayer(i).GetDiceCount(); ++j) {
            sum += _world.GetPlayer(i).GetDice(j);
        }

        _players[i] = {i, sum};
    }

    std::sort(_players.begin(), _players.begin() + _world.GetPlayersCount(),
              [](auto l, auto r) { return std::get<1>(l) < std::get<1>(r); });
}

int OrderedByDicesPlayers::First() const { return std::get<0>(_players[0]); }

void OrderedByDicesPlayers::Apply(
    std::function<void(PlayerLogic& player)> action) {
    for (int i = 0; i < _world.GetPlayersCount(); ++i) {
        auto& player = _world.GetPlayer(std::get<0>(_players[i]));
        action(player);
    }
}

OrderedByPointsPlayers::OrderedByPointsPlayers(WorldLogic& world)
    : _world{world} {
    for (int i = 0; i < _world.GetPlayersCount(); ++i) {
        _players[i] = {i, _world.GetPlayer(i).GetPoints()};
    }

    std::sort(_players.begin(), _players.begin() + _world.GetPlayersCount(),
              [](auto l, auto r) { return std::get<1>(l) > std::get<1>(r); });
}

int OrderedByPointsPlayers::First() const { return std::get<0>(_players[0]); }

void OrderedByPointsPlayers::Apply(
    std::function<void(PlayerLogic& player)> action) {
    for (int i = 0; i < _world.GetPlayersCount(); ++i) {
        auto& player = _world.GetPlayer(std::get<0>(_players[i]));
        action(player);
    }
}
