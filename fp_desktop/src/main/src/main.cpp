#include <fp_desktop/Environment.h>
#include <fp_desktop/FpDesktop.h>

int main(int ac, char* av[])
{
	// ------------------------------------------------------------------------
	// Initialize the environment
	// ------------------------------------------------------------------------
	fp_desktop::Environment env;
	if (!env.createFromArgs(ac, av)) {
		return 1;
	}

	// ------------------------------------------------------------------------
	// Initialize the window
	// ------------------------------------------------------------------------
	fp_desktop::FpDesktop program;
	program.setEnv(env);
	program.createOpenGLWindow();
	program.start();

	return 0;
}
