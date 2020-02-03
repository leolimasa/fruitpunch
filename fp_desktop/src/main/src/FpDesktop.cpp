/*
 * FpDesktop.cpp
 *
 *  Created on: Jun 27, 2013
 *      Author: leo
 */

#include <fp_desktop/FpDesktop.h>
#include <fp_desktop/Environment.h>
#include <fruitpunch/Common/Event.h>
#include <fruitpunch/Common/Events.h>
#include <fruitpunch/Graphics/Vertex.h>
#include <GLFW/glfw3.h>

using namespace fp_core::common;
using namespace fp_core;

namespace fp_desktop {

FpDesktop::FpDesktop() {
	pointerReleased = true;

}

FpDesktop::~FpDesktop() {
	// TODO Auto-generated destructor stub
}

void FpDesktop::createOpenGLWindow() {
	if (!glfwInit()) {
		fprintf(stderr, "GLFW initialization failed");
		return;
	}

	window = glfwCreateWindow(env->getWidth(),
			env->getHeight(),
			"Fruitpunch Desktop Client",
			NULL,
			NULL);

	if (!window) {
		glfwTerminate();
		fprintf(stderr, "GLFW window initialization failed");
	}

	glfwMakeContextCurrent(window);
}

void FpDesktop::mainLoop() {
	// ------------------------------------------------------------------------
	// Pointer Click
	// ------------------------------------------------------------------------
	glfwPollEvents();
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		pointerReleased = false;
		getRuntime()->getWindow()->notify(
				Event::ref(new Event(EV_POINTER_DOWN)));
	} else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE
			&& !pointerReleased) {
		pointerReleased = true;
		getRuntime()->getWindow()->notify(Event::ref(new Event(EV_POINTER_UP)));
	}

	// ------------------------------------------------------------------------
	// Pointer Position
	// ------------------------------------------------------------------------
	point p;
	double x, y;
	glfwGetCursorPos(window, &x, &y);
	p.x = (float) x;
	p.y = (float) y;
	getRuntime()->getWindow()->setPointer(p);

	// ------------------------------------------------------------------------
	// Render runtime frame
	// ------------------------------------------------------------------------
	if (!getRuntime()->renderFrame()) {
		env->printRuntimeErrors();
	}

	// ------------------------------------------------------------------------
	// Swap front and back buffers and process events
	// ------------------------------------------------------------------------
	glfwSwapBuffers(window);
}

const Environment& FpDesktop::getEnv() const {
	return *this->env;
}

void FpDesktop::setEnv(Environment& env) {
	this->env = &env;
}

const boost::shared_ptr<fp_core::common::Runtime> FpDesktop::getRuntime() const {
	return this->runtime;
}

void FpDesktop::start() {
	runtime = env->createRuntime();
	if (!runtime) {
		env->printRuntimeErrors();
		return;
	}

	while (!glfwWindowShouldClose(window)) {
		mainLoop();
	}
}

void FpDesktop::setRuntime(boost::shared_ptr<fp_core::common::Runtime> runtime) {
	this->runtime = runtime;
}

} /* namespace fp_desktop */
