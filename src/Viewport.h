/*
 * A class stored the windows data and some scene info of the application
 */

#ifndef _AGLRL_VIEWPORT_H
#define _AGLRL_VIEWPORT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

#include <string>

#include "IEventHandler.h"
#include "types.h"

namespace aglrl {
	class Viewport : public IEventHandler{
	private:
		int m_InitialWidth, m_InitialHeight;
		std::string m_Title;
		GLFWwindow* m_Window;

		static void resizeCallback(GLFWwindow* window, int width, int height)
		{
			glViewport(0, 0, width, height);
		}
	public:
		int getWidth() const { int width; glfwGetWindowSize(m_Window, &width, nullptr); return width; }
		int getHeight() const { int height; glfwGetWindowSize(m_Window, nullptr, &height); return height; }
		
		Color getBackgroundColor() const
		{
			glm::vec4 color;
			glGetFloatv(GL_COLOR_CLEAR_VALUE, glm::value_ptr(color));
			return color;
		}
		
		std::string getTitle() const { return m_Title; }
		bool shouldClose() const { return glfwWindowShouldClose(m_Window); }

		Viewport& setWidth(int width) { glfwSetWindowSize(m_Window, width, getHeight()); return *this; }
		Viewport& setHeight(int height) { glfwSetWindowSize(m_Window, getWidth(), height); return *this; }
		void setBackgroundColor(Color color) { glClearColor(color.r, color.g, color.b, color.a); }
		Viewport& setTitle(std::string title)
		{
			m_Title = title;
			glfwSetWindowTitle(m_Window, title.c_str());
			return *this;
		}

		Viewport(int width, int height, std::string title) :
			m_InitialWidth(width), m_InitialHeight(height), m_Title(title),
			m_Window(nullptr) {}

		void onInit() override 
		{
			m_Window = glfwCreateWindow(m_InitialWidth, m_InitialHeight, 
										m_Title.c_str(), nullptr, nullptr);
			glfwSetWindowSizeCallback(m_Window, resizeCallback);
		}
		
		void bind() { glfwMakeContextCurrent(m_Window); }
		void frame() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); }
		void update() { glfwSwapBuffers(m_Window); }
	};
}

#endif