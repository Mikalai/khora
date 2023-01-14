#include <Log/Log.h>
#include <cassert>
#include <Render/WorldCompiler.h>
#include "AssetsCompiler.h"
#include "Assets.h"
#include <Platform/WellKnownPaths.h>

void Compile(vsg::ref_ptr<vsg::Options> options) {
	/*KhoraCompiler compiler;
	
	compiler.AddFile(WellKnownPaths::GetDataFolder() / "raw/models/board.vsgb");
	compiler.AddFile(WellKnownPaths::GetDataFolder() / "raw/models/city_card.vsgb");

	compiler.Compile(WellKnownPaths::GetDataFolder() / "raw/models/khora.vsgb", options);*/
}

AssetsCompiler::AssetsCompiler() {
	deserialization_steps.push_back([this](WorldCompiler& compiler) {
		if (auto it = compiler.objects.find("camera_object_Orientation"); it != compiler.objects.end()) {
			auto camera = it->second;
		}
		});

	deserialization_steps.push_back([this](WorldCompiler& compiler) {
		if (auto it = compiler.objects.find("camera_settings"); it != compiler.objects.end()) {
			auto camera = it->second;
		}
		});

	deserialization_steps.push_back([this](WorldCompiler& compiler) {
		for (auto& camera : camera_serialization_table) {
			if (auto it = compiler.objects.find(camera.first); it != compiler.objects.end()) {
				auto m = vsg::cast<vsg::MatrixTransform>(std::get<0>(it->second));
				*camera.second = vsg::cast<vsg::Camera>(m->children[0]);

				if (!*camera.second) {
					ERROR("Object {} was found but this is not camera.", camera.first);
				}
			}
			else {
				ERROR("Can't load geometry {}", camera.first);
				exit(-1);
			}
		}
		});

	deserialization_steps.push_back([this](WorldCompiler& compiler) {
		for (auto& geometry : geometry_serialization_table) {
			INFO("Loading geometry {}", geometry.first);
			if (auto it = compiler.objects.find(geometry.first); it != compiler.objects.end()) {
				auto o = std::get<0>(it->second);
				INFO("Geometry {} found. Type {}", geometry.first, o->className());

				auto m = vsg::cast<vsg::MatrixTransform>(o);
				auto state = vsg::cast<vsg::StateGroup>(m->children[0]);
				*geometry.second = vsg::cast<vsg::VertexIndexDraw>(state->children[0]);


				assert(geometry.second != nullptr && "Asset not found");
			}
			else {
				ERROR("Can't load geometry {}", geometry.first);
				exit(-1);
			}
		}
		});

	deserialization_steps.push_back([this](WorldCompiler& compiler) {
		for (auto& material : materials_serialization_table) {
			if (auto it = compiler.objects.find(material.first); it != compiler.objects.end()) {
				auto o = std::get<0>(it->second);
				INFO("Object {} has class name {}", material.first, o->className());

				vsg::ref_ptr<vsg::StateGroup> state;

				if (auto t = vsg::cast<vsg::MatrixTransform>(o); t) {
					state = vsg::cast<vsg::StateGroup>(t->children.front());
				}
				else {
					state = vsg::cast<vsg::StateGroup>(o);
				}

				assert(state != nullptr);

				state->children.clear();
				*material.second = state;

				assert(state != nullptr);
				if (!*material.second) {
					ERROR("Object {} was found but this is not material.", material.first);
				}
			}
			else {
				ERROR("Can't load material {}", material.first);
				exit(-1);
			}
		}
		});

	deserialization_steps.push_back([this](WorldCompiler& compiler) {
		for (auto& transform : transform_serialization_table) {
			if (auto it = compiler.objects.find(transform.first); it != compiler.objects.end()) {
				auto o = std::get<0>(it->second);
				auto m = vsg::cast<vsg::MatrixTransform>(o);
				m->children.clear();
				*transform.second = m;

				if (!*transform.second) {
					ERROR("Object {} was found but this is not transform.", transform.first);
				}
			}
			else {
				ERROR("Can't load geometry {}.", transform.first);
				exit(-1);
			}
		}
		});

	deserialization_steps.push_back([this](WorldCompiler& compiler) {
		for (auto& transform : matrix_serialization_table) {
			if (auto it = compiler.objects.find(transform.first); it != compiler.objects.end()) {
				auto o = std::get<0>(it->second);
				auto m = vsg::cast<vsg::MatrixTransform>(o);
				m->children.clear();
				*transform.second = m->matrix;
			}
			else {
				ERROR("Can't load geometry {}", transform.first);
				exit(-1);
			}
		}
		});
}

void AssetsCompiler::Add(std::string_view name, vsg::ref_ptr<vsg::StateGroup>* dst) {
	materials_serialization_table[std::string(name)] = dst;
}

void AssetsCompiler::Add(std::string_view name, vsg::ref_ptr<vsg::VertexIndexDraw>* dst) {
	geometry_serialization_table[std::string(name)] = dst;
}

void AssetsCompiler::Add(std::string_view name, vsg::ref_ptr<vsg::MatrixTransform>* dst) {
	transform_serialization_table[std::string(name)] = dst;
}

void AssetsCompiler::Add(std::string_view name, vsg::dmat4* dst) {
	matrix_serialization_table[std::string(name)] = dst;
}

void AssetsCompiler::Add(std::string_view name, vsg::ref_ptr<vsg::Camera>* dst) {
	camera_serialization_table[std::string(name)] = dst;
}

void AssetsCompiler::AddInputFile(std::filesystem::path path) {
	_paths.emplace_back(path);
}

AssetsCompiler::~AssetsCompiler() {
}

void AssetsCompiler::Compile(Assets& assets, vsg::ref_ptr<vsg::Options> options) {
	WorldCompiler compiler;

	for (auto& filename : _paths) {
		auto model = vsg::read_cast<vsg::Node>(filename.c_str(), options);
		assert(model);
		model->accept(compiler);
	}

	assets.FillSerializationTables(*this);
}
