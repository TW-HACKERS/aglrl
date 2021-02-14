#include <iostream>

#include <aglrl.h>

void aglrl::setting()
{
	setFlag(Flag::GL_VERSION_MAJOR, 4);
	setFlag(Flag::GL_VERSION_MINOR, 1);
	setFlag(Flag::GL_PROFILE, GLProfile::CORE);
}

void aglrl::start()
{
	viewport.setWidth(800)
			.setHeight(600)
			.setTitle("Test")
			.setBackgroundColor(Color(0.2f, 0.2f, 0.2f, 1.0f));

	Shader::addShader("triangle", "triangle.vert", "triangle.frag");
}

void aglrl::tick()
{
	Shader::getShader("triangle").bind();
	Drawable::getDrawable("triangle")->draw();
}