#include "WorldVisual.h"
#include "WorldVisualIdleMarker.h"

WorldVisualIdleMarker::WorldVisualIdleMarker(WorldVisual& visual)
	: _visual{ visual } {
}

bool WorldVisualIdleMarker::IsIdle() const {
	return _visual.IsIdle();
}
