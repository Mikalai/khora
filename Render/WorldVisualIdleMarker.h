#pragma once

#include <UI/IUserInputIdleMarker.h>

class WorldVisualIdleMarker : public IUserInputIdleMarker {
public:
    WorldVisualIdleMarker(WorldVisual& visual);
    bool IsIdle() const override;

private:
	WorldVisual& _visual;
};
