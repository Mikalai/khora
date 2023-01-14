#pragma once

#include <vector>
#include <unordered_map>
#include <filesystem>
#include <functional>
#include <vsg/all.h>
#include <Assets/KhoraAssets.h>
#include <Assets/AssetsCompiler.h>

class WorldCompiler;
class KhoraAssets;
class Scene;

class SceneBuilder {
public:

	struct NewTransformRef {
		NewTransformRef(SceneBuilder& b);
		NewTransformRef& AddChild(vsg::ref_ptr<vsg::Node> node);
		void MoveToWorld();
	private:
		SceneBuilder& _b;
		vsg::ref_ptr<vsg::MatrixTransform> _newTransform;
	};

	SceneBuilder(vsg::ref_ptr<vsg::Options> options);
	virtual ~SceneBuilder();

	NewTransformRef NewTransform();

	vsg::ref_ptr<vsg::StateGroup> Clone(vsg::ref_ptr<vsg::StateGroup> original);

	std::unique_ptr<Scene> CreateScene(const Assets& assets);

protected:	
	vsg::ref_ptr<vsg::Node> CreateBox();

	virtual std::unique_ptr<Scene> OnCreateScene() = 0;
	virtual void OnBuildScene(Scene& scene, const Assets& assets) = 0;

	vsg::ref_ptr<vsg::Node> CreateText(vsg::ref_ptr<vsg::Font> font, const std::string& t, const vsg::dvec3& offset, const vsg::dvec4 color, double scale);

private:
	
protected:	
	vsg::StateInfo state;
	std::unique_ptr<Scene> scene;
	vsg::ref_ptr<vsg::Options> options;
	vsg::ref_ptr<vsg::Builder> builder;		
	vsg::ref_ptr<vsg::Node> _box;	
};
