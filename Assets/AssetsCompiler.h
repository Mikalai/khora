#pragma once
#include <functional>
#include <vsg/io/Options.h>

void Compile(vsg::ref_ptr<vsg::Options> options);

class WorldCompiler;
class Assets;

class AssetsCompiler {
public:
	AssetsCompiler();
	virtual ~AssetsCompiler();

	void Add(std::string_view name, vsg::ref_ptr<vsg::StateGroup>* dst);
	void Add(std::string_view name, vsg::ref_ptr<vsg::VertexIndexDraw>* dst);
	void Add(std::string_view name, vsg::ref_ptr<vsg::MatrixTransform>* dst);
	void Add(std::string_view name, vsg::dmat4* dst);
	void Add(std::string_view name, vsg::ref_ptr<vsg::Camera>* dst);
	
	void AddInputFile(std::filesystem::path path);
	void Compile(Assets& assets, vsg::ref_ptr<vsg::Options> options);

	void Load();

private:
	std::vector<std::function<void(WorldCompiler&)>> deserialization_steps;
	std::unordered_map<std::string, vsg::ref_ptr<vsg::StateGroup>*> materials_serialization_table;
	std::unordered_map<std::string, vsg::ref_ptr<vsg::VertexIndexDraw>*> geometry_serialization_table;
	std::unordered_map<std::string, vsg::ref_ptr<vsg::MatrixTransform>*> transform_serialization_table;
	std::unordered_map<std::string, vsg::dmat4*> matrix_serialization_table;
	std::unordered_map<std::string, vsg::ref_ptr<vsg::Camera>*> camera_serialization_table;
	std::vector<std::filesystem::path> _paths;
};