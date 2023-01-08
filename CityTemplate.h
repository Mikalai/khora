#pragma once

#include <Resources.h>
#include <array>
#include <Effects/CityEffect.h>

class CityTemplate {
public:
    CityTemplate(Cities city, CityEffect& l1, CityEffect& l2, CityEffect& l3, CityEffect& l4);

    const CityEffect& GetUpgradeEffect(int level) const;
    const PlayerPerk& GetTrackPerk(ProgressTrackType type, int level) const;
    int GetTrackUpgradeCost(ProgressTrackType type, int level) const;

private:
    Cities _type{ city_unknown };    
    std::array<CityEffect*, 4> _effects;
    static std::array<std::array<std::tuple<int, PlayerPerk>, max_city_track_upgrades>, 3> _trackPerks;
};

const CityTemplate& GetCityTemplate(Cities city);