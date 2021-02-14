/*
 * A class stored the windows data and some scene info of the application
 */

#ifndef _AGLRL_VIEWPORT_H
#define _AGLRL_VIEWPORT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <iostream>

#include "EventHandler.h"
#include "types.h"

namespace aglrl {
	class Viewport : public EventHandler{
	private:
		std::string m_Title = "aglrl";
		GLFWwindow* m_Window;

		static void resizeCallback(GLFWwindow* window, int width, int height)
		{
			glViewport(0, 0, width, height);
		}

	public:
		void onInit() override
		{
			m_Window = glfwCreateWindow(1, 1,
										m_Title.c_str(), nullptr, nullptr);
			glfwSetWindowSizeCallback(m_Window, resizeCallback);
		}

		int getWidth() const { int width; glfwGetWindowSize(m_Window, &width, nullptr); return width; }
		int getHeight() const { int height; glfwGetWindowSize(m_Window, nullptr, &height); return height; }
		std::string getTitle() const { return m_Title; }
		Color getBackgroundColor() const
		{
			glm::vec4 color;
			glGetFloatv(GL_COLOR_CLEAR_VALUE, glm::value_ptr(color));
			return color;
		}

		Viewport& setWidth(int width) { glfwSetWindowSize(m_Window, width, getHeight()); return *this; }
		Viewport& setHeight(int height) { glfwSetWindowSize(m_Window, getWidth(), height); return *this; }
		void setBackgroundColor(Color color) { glClearColor(color.r, color.g, color.b, color.a); }
		Viewport& setTitle(std::string title)
		{
			m_Title = title;
			glfwSetWindowTitle(m_Window, title.c_str());
			return *this;
		}

		bool shouldClose() const { return glfwWindowShouldClose(m_Window); }
		
		void bind() { glfwMakeContextCurrent(m_Window); }
		void frame() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); }
		void update() { glfwSwapBuffers(m_Window); }
		void loadGL() { gladLoadGL(); }
	};
}

#endif