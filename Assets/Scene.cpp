#pragma once

#include <filesystem>
#include <vsg/io/Options.h>
#include <unordered_map>
#include <string>
#include <vector>
#include <memory>
#include <vsg/all.h>
#include <Resources.h>
#include "Scene.h"

class AssetsCompiler;

bool Scene::MoveToWorld(vsg::ref_ptr<vsg::MatrixTransform> action) {

	auto t = _cameraAligned->matrix * action->matrix;

	auto it = std::find(_cameraAligned->children.begin(), _cameraAligned->children.end(), action);
	if (it == _cameraAligned->children.end())
		return false;

	_cameraAligned->children.erase(it);
	action->matrix = t;
	_worldRoot->addChild(action);

	return true;
}

bool Scene::MoveToView(vsg::ref_ptr<vsg::MatrixTransform> t) {

	auto it = std::find(_worldRoot->children.begin(), _worldRoot->children.end(), t);
	if (it == _worldRoot->children.end())
		return false;

	_worldRoot->children.erase(it);
	_cameraAligned->addChild(t);

	auto aligned = _cameraAligned->matrix;
	auto world = vsg::inverse(aligned) * t->matrix;
	t->matrix = world;
	return true;
}

void Scene::RemoveFromWorld(vsg::ref_ptr<vsg::MatrixTransform> t) {
	auto it = std::find(_worldRoot->children.begin(), _worldRoot->children.end(), t);
	if (it == _worldRoot->children.end())
		return;
	_worldRoot->children.erase(it);
}

vsg::ref_ptr<vsg::Group> Scene::GetRoot() {
	return _root;
}

void Scene::AddToWorld(vsg::ref_ptr<vsg::Node> node) {
	_worldRoot->addChild(node);
}
