/*
 * Environment.cpp
 *
 *  Created on: Jun 24, 2013
 *      Author: leo
 */

#include <fp_desktop/Environment.h>
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <fruitpunch/Common/Events.h>
#include <fruitpunch/Common/Event.h>
#include <fruitpunch/Common/Runtime.h>
#include <fruitpunch/Common/RuntimeError.h>
#include <fruitpunch/Graphics/OpenGl.h>
#include <fruitpunch/Graphics/Renderer.h>
#include <fp_desktop/Bridge.h>

namespace po = boost::program_options;
using namespace boost;
using namespace std;
using namespace fp_core::common;
using namespace fp_core;

namespace fp_desktop {

Environment::Environment() {
	// TODO Auto-generated constructor stub

}

Environment::~Environment() {
	// TODO Auto-generated destructor stub
}

bool Environment::createFromArgs(int ac, char* av[]) {
	po::options_description desc("Emulator options");

	// adds all the arguments available to be parsed from the command line
	desc.add_options()("help", "produce a help message")("width,w",
			po::value<int>(&(width))->default_value(100), "Canvas width")(
			"height,h", po::value<int>(&(height))->default_value(100),
			"Canvas height")("resource-path,r",
			po::value<vector<string> >()->composing(),
			"One or more paths to the locations of resource files")(
			"python-script,s", po::value<vector<string> >(),
			"Full path to the python script")("python-path,p",
			po::value<vector<string> >()->composing());

	po::positional_options_description p;
	p.add("python-script", 1);

	po::variables_map vm;

	// parses the config file
	if (boost::filesystem::exists("fp_emu.cfg")) {
		po::store(po::parse_config_file<char>("fp_emu.cfg", desc), vm);
	}

	// stores the command line params
	po::store(po::command_line_parser(ac, av).options(desc).positional(p).run(),
			vm);

	po::notify(vm);
	processVm(vm);

	if (vm.count("help")) {
		std::cout << desc << std::endl;
		return false;
	}

	return true;

}

boost::shared_ptr<Runtime> Environment::createRuntime() {
	// path to the user .py file
	filesystem::path userScript(pyfile);

	// path to the folder where this .exe is being executed
	filesystem::path current = boost::filesystem::current_path();

	// the current path also happens to be where we will locate libfruitpunch
	string libfruitpunch = current.generic_string();

	// the PythonDir
	current /= "python";

	// the renderer
	boost::shared_ptr<Renderer> renderer(new OpenGl());

	// creates a new runtime
	Runtime::create();
	boost::shared_ptr <Runtime > runtime = Runtime::getCurrent();

	// ---------------------------------------------------------------------------
	// Runtime parameters
	// ---------------------------------------------------------------------------
	runtime->setPathSeparator("/");

	// adds the user script path as a resource path
	runtime->getResourcePath().push_back(
			userScript.branch_path().generic_string());

	// adds the other resource paths
	vector<string>::iterator it = resourcePath.begin();
	for (; it != resourcePath.end(); it++) {
		runtime->getResourcePath().push_back(*it);
		printf("Adding %s", it->c_str());
	}

	//runtime->setPythonDir(current.generic_string());
	runtime->setPythonModule(pyfile);
	runtime->setPythonHome(pyhome);
	runtime->setRenderer(renderer);
	runtime->addPythonPath(libfruitpunch);
	runtime->addPythonPath(userScript.branch_path().generic_string());
	runtime->debug = true;

	// ---------------------------------------------------------------------------
	// Registers the PYTHON_PATH
	// ---------------------------------------------------------------------------
	it = pypath.begin();
	for (; it != pypath.end(); it++) {
		runtime->addPythonPath(*it);
	}

	// creates a bridge
	boost::shared_ptr<NativeBridge> bridge(new Bridge());

	// starts it up
	if (!runtime->init(width, height, bridge)) {
		printRuntimeErrors();
	}
	return runtime;
}

int Environment::getHeight() const {
	return height;
}

std::string Environment::getPyfile() const {
	return pyfile;
}

std::string Environment::getPyhome() const {
	return pyhome;
}

std::vector<std::string> Environment::getPypath() const {
	return pypath;
}

std::vector<std::string> Environment::getResourcePath() const {
	return resourcePath;
}

int Environment::getWidth() const {
	return width;
}

void Environment::printRuntimeErrors() {
	boost::shared_ptr<Runtime> runtime = Runtime::getCurrent();
	vector<boost::shared_ptr<RuntimeError> >::iterator it;
	vector<boost::shared_ptr<RuntimeError> > errors = runtime->getErrors();
	for (it = errors.begin(); it != errors.end(); it++) {
			fprintf(stderr, "[RUNTIME ERROR]");
			fprintf(stderr, (*it)->getDescription().c_str());
			runtime->flushErrors();
	}
}

void Environment::processVm(boost::program_options::variables_map& vm) {
	if (vm.count("python-script")) {
		pyfile = vm["python-script"].as<vector<string> >()[0];
	} else {
		pyfile = "";
	}

	if (vm.count("python-path")) {
		pypath = vm["python-path"].as<vector<string> >();
	}

	if (vm.count("resource-path")) {
		resourcePath = vm["resource-path"].as<vector<string> >();
	}
}

} /* namespace fp_desktop */
