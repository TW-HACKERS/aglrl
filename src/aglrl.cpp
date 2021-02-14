#include <vector>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "aglrl.h"

using namespace aglrl;

Viewport aglrl::viewport;

int main()
{
	Triangle* triangle = new Triangle;

	EventHandler::registerHandler(&viewport);
	EventHandler::registerHandler(triangle);

	Drawable::addDrawable("triangle", triangle);

	glfwInit();
	setting();
	EventHandler::triggerEvent("init");
	viewport.bind();
	viewport.loadGL();
	EventHandler::triggerEvent("GLLoaded");

	//user-defined, run one time
	start();
	
	while (!viewport.shouldClose()) {
		glfwPollEvents();
		viewport.frame();
		//user-defined, runs every frame
		tick();
		viewport.update();
	}

	glfwTerminate();
	return 0;
}

template<>
void aglrl::setFlag<int>(Flag flag, int value)
{
	switch (flag) {
	case Flag::GL_VERSION_MAJOR: glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, value); break;
	case Flag::GL_VERSION_MINOR: glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, value); break;
	}
}

template<>
void aglrl::setFlag<GLProfile>(Flag flag, GLProfile value)
{
	switch (flag) {
	case Flag::GL_PROFILE: 
		if (value == GLProfile::CORE) glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		if (value == GLProfile::COMPATIBILITY) glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	}
}