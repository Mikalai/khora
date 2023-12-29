#pragma once

#include <array>
#include <functional>
#include <tuple>

class WorldLogic;
class PlayerLogic;

struct OrderedByDicesPlayers {
    OrderedByDicesPlayers(WorldLogic& world);
    void Apply(std::function<void(PlayerLogic& player)> action);
    int First() const;

   private:
    std::array<std::tuple<int, int>, 4> _players;
    WorldLogic& _world;
};

struct OrderedByPointsPlayers {
    OrderedByPointsPlayers(WorldLogic& world);
    void Apply(std::function<void(PlayerLogic& player)> action);
    int First() const;

   private:
    std::array<std::tuple<int, int>, 4> _players;
    WorldLogic& _world;
};