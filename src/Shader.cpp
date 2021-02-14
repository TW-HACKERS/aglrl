#include "Shader.h"
using namespace aglrl;

#include <iostream>
#include <fstream>
#include <sstream>

std::unordered_map<std::string, Shader> Shader::shaders;

enum class ShaderType {
	VERTEX,
	FRAGMENT,
	GEOMETRY,
	PROGRAM
};

GLuint compileShader(const char* vertexSrc, const char* fragmentSrc,
					 const char* geometrySrc, std::string name);
void checkError(GLuint id, ShaderType type, std::string name);

void aglrl::Shader::addShader(std::string name, std::string vertexPath, std::string fragmentPath, std::string geometryPath)
{
	Shader shader;

	std::ifstream vertexFile, fragmentFile, geometryFile;
	vertexFile.exceptions(std::ifstream::badbit | std::ifstream::failbit);
	fragmentFile.exceptions(std::ifstream::badbit | std::ifstream::failbit);
	geometryFile.exceptions(std::ifstream::badbit | std::ifstream::failbit);
	std::string vertexString, fragmentString, geometryString;

	try {
		std::ostringstream vertexStream, fragmentStream, geometryStream;
		
		vertexFile.open(vertexPath);
		fragmentFile.open(fragmentPath);
		vertexStream << vertexFile.rdbuf();
		fragmentStream << fragmentFile.rdbuf();
		vertexString = vertexStream.str();
		fragmentString = fragmentStream.str();
		if (!geometryPath.empty()) {
			geometryFile.open(geometryPath);
			geometryStream << geometryFile.rdbuf();
			geometryString = geometryStream.str();
		}
	}
	catch (std::ifstream::failure e) {
		std::cerr << "Failed to load shader\n";
	}
	shader.m_Id = compileShader(vertexString.c_str(), fragmentString.c_str(),
								geometryPath.empty() ? nullptr : geometryString.c_str(),
								name);
	shaders[name] = shader;
}

GLuint compileShader(const char* vertexSrc, const char* fragmentSrc,
					 const char* geometrySrc, std::string name)
{
	GLuint program = glCreateProgram();
	

	GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexSrc, nullptr);
	glCompileShader(vertex);
	checkError(vertex, ShaderType::VERTEX, name);
	glAttachShader(program, vertex);

	GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentSrc, nullptr);
	glCompileShader(fragment);
	checkError(fragment, ShaderType::FRAGMENT, name);
	glAttachShader(program, fragment);

	if (geometrySrc) {
		GLuint geometry = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geometry, 1, &geometrySrc, nullptr);
		glCompileShader(geometry);
		checkError(geometry, ShaderType::GEOMETRY, name);
		glAttachShader(program, geometry);
	}

	glLinkProgram(program);
	checkError(program, ShaderType::PROGRAM, name);
	return program;
}

void checkError(GLuint id, ShaderType type, std::string name)
{
	GLint status;
	GLchar infoLog[512];
	if (type == ShaderType::PROGRAM) {
		glGetProgramiv(id, GL_LINK_STATUS, &status);
		if (!status) {
			glGetProgramInfoLog(id, sizeof(infoLog), nullptr, infoLog);
			std::cerr << "[FATAL ERROR] Failed to link program of \"" << name 
					  << "\"\n" << infoLog << '\n';
		}
	}
	else {
		glGetShaderiv(id, GL_COMPILE_STATUS, &status);
		if (!status) {
			glGetShaderInfoLog(id, sizeof(infoLog), nullptr, infoLog);
			std::cerr << "[FATAL ERROR] Failed to compile ";
			switch (type) {
			case ShaderType::VERTEX:
				std::cerr << "vertex"; break;
			case ShaderType::FRAGMENT:
				std::cerr << "fragment"; break;
			case ShaderType::GEOMETRY:
				std::cerr << "geometry"; break;
			}
			std::cerr << " shader of \"" << name << "\"\n" << infoLog << '\n';;
		}
	}
}