#pragma once

#include <functional>

class PlayerLogic;
using PlayerPerk = std::function<void(PlayerLogic&)>;