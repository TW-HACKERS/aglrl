#ifndef _AGLRL_SHADER_H
#define _AGLRL_SHADER_H

#include <string>
#include <unordered_map>

#include <glad/glad.h>

namespace aglrl {
	class Shader {
	private:
		static std::unordered_map<std::string, Shader> shaders;

		GLuint m_Id;
	public:
		static Shader getShader(std::string name) { return shaders[name]; }

		static void addShader(std::string name, std::string vertexPath, std::string fragmentPath, std::string geometryPath = "");
		void bind() const { glUseProgram(m_Id); }
	};
}

#endif