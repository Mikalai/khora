#pragma once

#include <cassert>
#include <Render/WorldCompiler.h>
#include <vsg/all.h>
#include "Scene.h"
#include "SceneBuilder.h"

#ifdef vsgXchange_FOUND
#    include <vsgXchange/all.h>
#endif

SceneBuilder::SceneBuilder(vsg::ref_ptr<vsg::Options> options)
	: options{ options } {
	builder = vsg::Builder::create();
	builder->options = options;
}

SceneBuilder::~SceneBuilder() {

}

vsg::ref_ptr<vsg::Node> SceneBuilder::CreateBox() {

	if (_box)
		return _box;

	vsg::GeometryInfo geom;
	state.wireframe = false;
	state.blending = true;
	state.lighting = false;
	geom.color.set(0, 1, 0, 0.6);
	geom.position.set(0.0f, 0.005f, 0.0f);
	geom.dx.set(0.01f, 0.0f, 0.0f);
	geom.dy.set(0.0f, 0.01f, 0.0f);
	geom.dz.set(0.0f, 0.0f, 0.01f);

	return _box = builder->createBox(geom, state);
}

SceneBuilder::NewTransformRef SceneBuilder::NewTransform() {
	return { *this };
}

SceneBuilder::NewTransformRef::NewTransformRef(SceneBuilder& b)
	: _b{ b } 
	, _newTransform{ vsg::MatrixTransform::create() } {
}

SceneBuilder::NewTransformRef& SceneBuilder::NewTransformRef::AddChild(vsg::ref_ptr<vsg::Node> node) {
	_newTransform->addChild(node);
}

void SceneBuilder::NewTransformRef::MoveToWorld() {
	_b.scene->_worldRoot->addChild(_newTransform);
}

std::unique_ptr<Scene> SceneBuilder::CreateScene(const Assets& assets) {
	scene = OnCreateScene();
	OnBuildScene(*scene, assets);
	return std::move(scene);
}

vsg::ref_ptr<vsg::StateGroup> SceneBuilder::Clone(vsg::ref_ptr<vsg::StateGroup> original) {
	auto clone = vsg::StateGroup::create();
	for (auto& state : original->stateCommands) {
		clone->stateCommands.push_back(state);
	}

	clone->prototypeArrayState = original->prototypeArrayState;

	return clone;
}

vsg::ref_ptr<vsg::Node> SceneBuilder::CreateText(vsg::ref_ptr<vsg::Font> font, const std::string& t, const vsg::dvec3& offset, const vsg::dvec4 color, double scale) {
	auto transform = vsg::MatrixTransform::create();
	transform->matrix = vsg::scale(scale, scale, scale);

	auto layout = vsg::StandardLayout::create();
	layout->horizontalAlignment = vsg::StandardLayout::CENTER_ALIGNMENT;
	layout->verticalAlignment = vsg::StandardLayout::CENTER_ALIGNMENT;
	layout->position = offset;
	layout->horizontal = vsg::vec3(1.0, 0.0, 0.0);
	layout->vertical = vsg::vec3(0.0, 0.0, -1.0);
	layout->color = color;
	layout->outlineWidth = 0.0;
	layout->billboard = false;

	auto data = vsg::stringValue::create(t);

	auto text = vsg::Text::create();
	text->text = data;
	text->font = font;
	text->layout = layout;
	text->setup(0, options);

	transform->addChild(text);

	return transform;
}