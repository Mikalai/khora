#include <cassert>
#include <iostream>
#include <Render/WorldCompiler.h>
#include <Platform/WellKnownPaths.h>

std::string fixName(std::string name) {
	for (auto& c : name) {
		if (c == '.') {
			c = '_';
		}
	}
	return name;
}

int main(int argc, char** argv) {
	WellKnownPaths::Init();
	INIT_LOGGER();

	auto options = vsg::Options::create();
	options->sharedObjects = vsg::SharedObjects::create();

	WorldCompiler compiler;

	for (int i = 1; i < argc; ++i) {
		auto filename = argv[i];		

		auto model = vsg::read_cast<vsg::Node>(filename, options);
		if (!model) {
			ERROR("File '{}' is not loaded.", filename);
			continue;
		}

		model->accept(compiler);
	}

	std::cout << "#pragma once" << std::endl;
	std::cout << "#include <string>" << std::endl;

	std::cout << std::endl;

	for (auto& t : compiler.objects) {
		std::cout << "const std::string str_" << fixName(t.first) << " = \"" << t.first << "\";" << std::endl;
	}

	return 0;
}

