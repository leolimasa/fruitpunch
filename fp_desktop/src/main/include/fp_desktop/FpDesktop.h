/*
 * FpDesktop.h
 *
 *  Created on: Jun 27, 2013
 *      Author: leo
 */

#ifndef FPDESKTOP_H_
#define FPDESKTOP_H_

#include <fruitpunch/Common/Runtime.h>
#include <GLFW/glfw3.h>

namespace fp_desktop {

class Environment;

class FpDesktop {
public:
	FpDesktop();
	void createOpenGLWindow();
	void mainLoop();
	void start();
	virtual ~FpDesktop();
	const Environment& getEnv() const;
	void setEnv(Environment& env);
	const boost::shared_ptr<fp_core::common::Runtime> getRuntime() const;
	void setRuntime(boost::shared_ptr<fp_core::common::Runtime> runtime);

private:
	Environment * env;
	boost::shared_ptr<fp_core::common::Runtime> runtime;
	bool pointerReleased;
	GLFWwindow * window;
};

} /* namespace fp_desktop */
#endif /* FPDESKTOP_H_ */
