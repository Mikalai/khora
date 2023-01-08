#include <vsg/all.h>
#include <UI/UI.h>
#include "GameLoop.h"
#include "WorldVisual.h"
#include <World.h>

GameLoop::GameLoop(World& logic, WorldVisual& visual)
	: _logic{ logic } 
	, _visual{ visual }
{
}

void GameLoop::apply(vsg::FrameEvent& frame) {
	if (frame.frameStamp->frameCount == 0) {
		_prevTime = frame.frameStamp->time;
	}

	ui().Update(_logic._logic);
	_visual.Update(_logic._logic);
	_logic.Update();	
	auto count = std::chrono::duration<double>(frame.frameStamp->time - _prevTime).count();
	_visual.Update(count);
	_prevTime = frame.frameStamp->time;
}
