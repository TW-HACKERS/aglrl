#ifndef _AGLRL_TRIANGLE_H
#define _AGLRL_TRIANGLE_H

#include <glad/glad.h>

#include "Drawable.h"
#include "EventHandler.h"

namespace aglrl {
	class Triangle : public Drawable, public EventHandler
	{
	private:
		GLuint m_Vao;
	public:
		void onGLLoaded() override
		{
			const GLfloat vertices[] = {
				 0.0f,  0.5f, 0.0f,
				-0.5f, -0.5f, 0.0f, 
				 0.5f, -0.5f, 0.0f   
			};

			glGenVertexArrays(1, &m_Vao);
			glBindVertexArray(m_Vao);

			GLuint vbo;
			glGenBuffers(1, &vbo);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, reinterpret_cast<void*>(0));

			glEnableVertexAttribArray(0);

			addDrawable("triangle", this);
		}

		void draw() override
		{
			glBindVertexArray(m_Vao);
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
	};
}

#endif