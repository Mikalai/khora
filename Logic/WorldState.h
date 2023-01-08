#pragma once

#include <functional>
#include <vector>

using Predicate = std::function<bool(const class WorldLogic&)>;

class WorldState {
public:

    WorldState(WorldLogic& logic);
    virtual WorldState* Update();
    virtual void Transition(std::function<bool(const WorldLogic&)> predicate, WorldState* next);
    virtual void SetEnter(std::function<void(WorldLogic&)> action);
    virtual void SetExit(std::function<void(WorldLogic&)> action);
    virtual void SetUpdate(std::function<void(WorldLogic&)> action);
	virtual void Exit();
	virtual void Enter();
	virtual void Reset();

    WorldLogic& _logic;

    struct Record {
        std::function<bool(WorldLogic&)> predicate;
        WorldState* next{ nullptr };
    };

    std::vector<Record> transition_table;
    std::function<void(WorldLogic&)> _enter;
    std::function<void(WorldLogic&)> _exit;
    std::function<void(WorldLogic&)> _update;
};
