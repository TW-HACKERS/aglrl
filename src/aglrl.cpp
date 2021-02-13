#include <list>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "aglrl.h"

using namespace aglrl;

Viewport aglrl::viewport(800, 600, "aglrl");

namespace {
	std::list<IEventHandler*> eventHandlers;
}

void init()
{
	glfwInit();
	
	//set GL context version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	auto i = eventHandlers.begin();
	while (i != eventHandlers.end()) {
		(*i)->onInit();
		++i;
	}

	viewport.bind();
	gladLoadGL();
	viewport.setBackgroundColor(Color(0.2f, 0.2f, 0.2f, 1.0f));

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void render()
{

}

void clean()
{
	glfwTerminate();
}

int main()
{
	registerEventHandler(viewport);

	init();

	start();

	while (!viewport.shouldClose()) {
		glfwPollEvents();

		viewport.frame();

		tick();

		render();

		viewport.update();
	}

	clean();
	return 0;
}

void aglrl::registerEventHandler(IEventHandler& eventHandler) { eventHandlers.push_back(&eventHandler); }