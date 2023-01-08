#include <cassert>
#include <tuple>
#include "ExpeditionTemplate.h"

ExpeditionTemplate g_expeditions[] = {
	{ 2, 1, 0, 0, {discovery_type::red, discovery_type::no, discovery_type::no } },
	{ 3, 0, 0, 0, {discovery_type::red, discovery_type::no, discovery_type::no } },
	{ 2, 2, 1, 0, {discovery_type::red, discovery_type::no, discovery_type::no } },
	{ 3, 1, 1, 0, {discovery_type::red, discovery_type::no, discovery_type::no } },
	{ 4, 2, 2, 0, {discovery_type::red, discovery_type::no, discovery_type::no } },
	{ 5, 1, 2, 0, {discovery_type::red, discovery_type::no, discovery_type::no } },	
	{ 5, 4, 2, 0, {discovery_type::epic_red, discovery_type::no, discovery_type::no } },
	{ 6, 3, 2, 0, {discovery_type::epic_red, discovery_type::no, discovery_type::no } },
	{ 7, 5, 3, 0, {discovery_type::epic_red, discovery_type::no, discovery_type::no } },
	{ 8, 6, 4, 0, {discovery_type::epic_red, discovery_type::no, discovery_type::no } },
	{ 9, 8, 6, 0, {discovery_type::epic_red, discovery_type::no, discovery_type::no } },
	{ 2, 2, 0, 0, {discovery_type::blue, discovery_type::no, discovery_type::no } },
	{ 3, 1, 0, 0, {discovery_type::blue, discovery_type::no, discovery_type::no } },
	{ 3, 3, 1, 1, {discovery_type::blue, discovery_type::no, discovery_type::no } },
	{ 4, 2, 1, 1, {discovery_type::blue, discovery_type::no, discovery_type::no } },
	{ 4, 4, 1, 1, {discovery_type::epic_blue, discovery_type::no, discovery_type::no } },
	{ 5, 3, 1, 1, {discovery_type::epic_blue, discovery_type::no, discovery_type::no } },
	{ 6, 5, 2, 1, {discovery_type::epic_blue, discovery_type::no, discovery_type::no } },
	{ 6, 5, 1, 2, {discovery_type::epic_blue, discovery_type::no, discovery_type::no } },
	{ 7, 6, 2, 2, {discovery_type::epic_blue, discovery_type::no, discovery_type::no } },
	{ 8, 7, 3, 3, {discovery_type::epic_blue, discovery_type::no, discovery_type::no } },
	{ 9, 9, 4, 4, {discovery_type::epic_blue, discovery_type::no, discovery_type::no } },
	{ 2, 1, 0, 0, {discovery_type::green, discovery_type::no, discovery_type::no } },
	{ 3, 0, 0, 0, {discovery_type::green, discovery_type::no, discovery_type::no } },		
	{ 2, 2, 0, 1, {discovery_type::green, discovery_type::no, discovery_type::no } },
	{ 3, 1, 0, 1, {discovery_type::green, discovery_type::no, discovery_type::no } },		
	{ 4, 2, 0, 2, {discovery_type::green, discovery_type::no, discovery_type::no } },
	{ 5, 1, 0, 2, {discovery_type::green, discovery_type::no, discovery_type::no } },		
	{ 5, 4, 0, 2, {discovery_type::epic_green, discovery_type::no, discovery_type::no } },
	{ 6, 3, 0, 2, {discovery_type::epic_green, discovery_type::no, discovery_type::no } },		
	{ 7, 5, 0, 3, {discovery_type::epic_green, discovery_type::no, discovery_type::no } },
	{ 8, 6, 0, 4, {discovery_type::epic_green, discovery_type::no, discovery_type::no } },		
	{ 9, 8, 0, 6, {discovery_type::epic_green, discovery_type::no, discovery_type::no } },
	{ 15, 15, 0, 0, {discovery_type::epic_red, discovery_type::epic_blue, discovery_type::epic_green } },
};

const ExpeditionTemplate& GetExpeditionTemplate(int expedition) {
	static_assert(sizeof(g_expeditions) / sizeof(g_expeditions[0]) == 34);
	return g_expeditions[expedition];
}

int GetExpeditionByDiscovery(int discovery) {
	assert(discovery >= 0 && discovery < max_expedition_discoveries);
	return std::max(0, std::min(GetExpeditionsCount() - 1, discovery));
}

discovery_type GetDiscoveryType(int discovery) {
	assert(discovery >= 0 && discovery < max_expedition_discoveries);
	return std::get<0>(str_cur_discovery[discovery]);
}
