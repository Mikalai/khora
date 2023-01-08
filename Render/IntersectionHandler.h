#pragma once

#include <iostream>
#include <Observers.h>
#include <vsg/all.h>
#ifdef vsgXchange_FOUND
#    include <vsgXchange/all.h>
#endif

enum class IntersectionMessageType {
	Activate,
	NextAction
};

struct IntersectionMessage {
	IntersectionMessage(IntersectionMessageType Type)
		: Type{ Type } {
	}

	IntersectionMessageType Type;
};

struct ObjectActivatedMessage : IntersectionMessage {
	ObjectActivatedMessage(const vsg::MatrixTransform* object)
		: IntersectionMessage{ IntersectionMessageType::Activate }
		, object{ object }
	{}

	const vsg::MatrixTransform* object;
};

struct NextActionMessage : IntersectionMessage {
	NextActionMessage()
		: IntersectionMessage{ IntersectionMessageType::NextAction }
	{}
};

class IntersectionHandler : public vsg::Inherit<vsg::Visitor, IntersectionHandler>, public Observable<IntersectionMessage>
{
public:
	vsg::GeometryInfo geom;
	vsg::StateInfo state;

	vsg::ref_ptr<vsg::Builder> builder;
	vsg::ref_ptr<vsg::Options> options;
	vsg::ref_ptr<vsg::Camera> camera;
	vsg::ref_ptr<vsg::Group> scenegraph;
	vsg::ref_ptr<vsg::EllipsoidModel> ellipsoidModel;
	double scale = 1.0;
	bool verbose = false;

	IntersectionHandler(vsg::ref_ptr<vsg::Builder> in_builder, vsg::ref_ptr<vsg::Camera> in_camera, vsg::ref_ptr<vsg::Group> in_scenegraph, vsg::ref_ptr<vsg::EllipsoidModel> in_ellipsoidModel, double in_scale, vsg::ref_ptr<vsg::Options> in_options);

	void apply(vsg::KeyPressEvent& keyPress) override;
	void apply(vsg::ButtonPressEvent& buttonPressEvent) override;
	void apply(vsg::PointerEvent& pointerEvent) override;
	void intersection(vsg::PointerEvent& pointerEvent);

protected:
	vsg::ref_ptr<vsg::PointerEvent> lastPointerEvent;
	vsg::ref_ptr<vsg::LineSegmentIntersector::Intersection> lastIntersection;
};
