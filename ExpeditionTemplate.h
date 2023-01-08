#pragma once

#include <array>
#include <Resources.h>

class ExpeditionTemplate {
public:
	int armyRequire;
	int armyLosses;
	int rewardMoney;
	int rewardPoints;
	std::array<discovery_type, 3> discoveries;
};

constexpr int GetExpeditionsCount() { return 34; }
const ExpeditionTemplate& GetExpeditionTemplate(int expedition);

int GetExpeditionByDiscovery(int discovery);
discovery_type GetDiscoveryType(int discovery);
