#pragma once

#include <functional>

class PlayerLogic;

using PlayerPredicate = std::function<bool(const PlayerLogic&)>;