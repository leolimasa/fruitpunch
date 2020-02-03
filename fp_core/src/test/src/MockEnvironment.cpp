/*
 * MockEnvironment.cpp
 *
 *  Created on: Sep 8, 2012
 *      Author: steven
 */

#include <MockEnvironment.h>
#include <MockRenderer.h>
#include <fruitpunch/Common/Runtime.h>
#include <boost/shared_ptr.hpp>
#include <boost/filesystem.hpp>
#include <string>

using namespace fp_core;
using namespace boost;
using namespace std;
using namespace fp_core::common;

MockEnvironment::MockEnvironment() {
    Runtime::create();
    Runtime::getCurrent()->setPathSeparator("/");
    Runtime::getCurrent()->debug = true;
    boost::shared_ptr<Window> win(new Window());
    Runtime::getCurrent()->setWindow(win);
    mCurrentPath = boost::filesystem::current_path();
	#ifdef WIN32
		mFullResourcePath = boost::filesystem::canonical("..\\..\\..\\src\\test\\resources", mCurrentPath).generic_string();
		mRoot = boost::filesystem::canonical("..\\..\\..\\", mCurrentPath).generic_string();
	#else
		mFullResourcePath = mCurrentPath.generic_string() + "/src/test/resources/";
		mRoot = mCurrentPath.generic_string();
	#endif

	Runtime::getCurrent()->setRuntimeRoot(mRoot);
    Runtime::getCurrent()->getResourcePath().push_back(mFullResourcePath);
    win->init(800,600, boost::shared_ptr<Renderer>(new MockRenderer()));
}

MockEnvironment::~MockEnvironment() {
	// TODO Auto-generated destructor stub
}

