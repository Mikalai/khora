#pragma once

#include <Resources.h>
#include <vsg/all.h>
#ifdef vsgXchange_FOUND
#    include <vsgXchange/all.h>
#endif

class World;
class WorldVisual;

class GameLoop : public vsg::Inherit<vsg::Visitor, GameLoop> {
    World& _logic;
	WorldVisual& _visual;
	vsg::time_point _prevTime;
public:

    GameLoop(World& logic, WorldVisual& visual);
    void apply(vsg::FrameEvent& frame) override;
};
