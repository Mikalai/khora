
#pragma once

#include <algorithm>
#include <vsg/all.h>
#ifdef vsgXchange_FOUND
#    include <vsgXchange/all.h>
#endif

#include "IntersectionHandler.h"


IntersectionHandler::IntersectionHandler(vsg::ref_ptr<vsg::Builder> in_builder, vsg::ref_ptr<vsg::Camera> in_camera, vsg::ref_ptr<vsg::Group> in_scenegraph, vsg::ref_ptr<vsg::EllipsoidModel> in_ellipsoidModel, double in_scale, vsg::ref_ptr<vsg::Options> in_options) :
	builder(in_builder),
	options(in_options),
	camera(in_camera),
	scenegraph(in_scenegraph),
	ellipsoidModel(in_ellipsoidModel),
	scale(in_scale)
{
	builder->verbose = verbose;
	if (scale > 10.0) scale = 10.0;
}

void IntersectionHandler::apply(vsg::KeyPressEvent& keyPress) 
{
	if (keyPress.keyBase == vsg::KeySymbol::KEY_Space)
	{
		NextActionMessage msg;
		Notify(msg);
	}
	else {
		if (lastPointerEvent)
		{
			intersection(*lastPointerEvent);
			if (!lastIntersection) return;

			geom.position = vsg::vec3(lastIntersection->worldIntersection);
			geom.dx.set(scale, 0.0f, 0.0f);
			geom.dy.set(0.0f, scale, 0.0f);
			geom.dz.set(0.0f, 0.0f, scale);

			if (keyPress.keyBase == 'b')
			{
				scenegraph->addChild(builder->createBox(geom, state));
			}
			else if (keyPress.keyBase == 'q')
			{
				scenegraph->addChild(builder->createQuad(geom, state));
			}
			else if (keyPress.keyBase == 'c')
			{
				scenegraph->addChild(builder->createCylinder(geom, state));
			}
			else if (keyPress.keyBase == 'p')
			{
				scenegraph->addChild(builder->createCapsule(geom, state));
			}
			else if (keyPress.keyBase == 's')
			{
				scenegraph->addChild(builder->createSphere(geom, state));
			}
			else if (keyPress.keyBase == 'n')
			{
				scenegraph->addChild(builder->createCone(geom, state));
			}
			else if (keyPress.keyBase == 'o')
			{
				vsg::write(scenegraph, "builder.vsgt");
			}
		}
	}
}

void IntersectionHandler::apply(vsg::ButtonPressEvent& buttonPressEvent) 
{
	lastPointerEvent = &buttonPressEvent;

	if (buttonPressEvent.button == 1)
	{
		intersection(buttonPressEvent);
	}
}

void IntersectionHandler::apply(vsg::PointerEvent& pointerEvent) 
{
	lastPointerEvent = &pointerEvent;
}

void IntersectionHandler::intersection(vsg::PointerEvent& pointerEvent)
{
	auto intersector = vsg::LineSegmentIntersector::create(*camera, pointerEvent.x, pointerEvent.y);
	scenegraph->accept(*intersector);

	if (verbose) std::cout << "intersection(" << pointerEvent.x << ", " << pointerEvent.y << ") " << intersector->intersections.size() << ")" << std::endl;

	if (intersector->intersections.empty()) return;

	// sort the intersectors front to back
	std::sort(intersector->intersections.begin(), intersector->intersections.end(), [](auto& lhs, auto& rhs) { return lhs->ratio < rhs->ratio; });

	for (auto& intersection : intersector->intersections)
	{	
		for (auto node : intersection->nodePath) {	
			if (node->type_info() != typeid(vsg::MatrixTransform))
				continue;

			ObjectActivatedMessage msg(node->cast<vsg::MatrixTransform>());
			Notify(msg);			
		}

		return;

		if (verbose) std::cout << "intersection = world(" << intersection->worldIntersection << "), instanceIndex " << intersection->instanceIndex;

		if (ellipsoidModel)
		{
			std::cout.precision(10);
			auto location = ellipsoidModel->convertECEFToLatLongAltitude(intersection->worldIntersection);
			if (verbose) std::cout << " lat = " << location[0] << ", long = " << location[1] << ", height = " << location[2];
		}

		if (lastIntersection)
		{
			if (verbose) std::cout << ", distance from previous intersection = " << vsg::length(intersection->worldIntersection - lastIntersection->worldIntersection);
		}

		if (verbose)
		{
			for (auto& node : intersection->nodePath)
			{
				std::cout << ", " << node->className();
			}

			std::cout << ", Arrays[ ";
			for (auto& array : intersection->arrays)
			{
				std::cout << array << " ";
			}
			std::cout << "] [";
			for (auto& ir : intersection->indexRatios)
			{
				std::cout << "{" << ir.index << ", " << ir.ratio << "} ";
			}
			std::cout << "]";

			std::cout << std::endl;
		}
	}

	lastIntersection = intersector->intersections.front();
}

