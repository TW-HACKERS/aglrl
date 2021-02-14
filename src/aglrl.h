#ifndef _AGLRL_H
#define _AGLRL_H

#include <glm/glm.hpp>

#include "EventHandler.h"
#include "Viewport.h"
#include "types.h"
#include "Drawable.h"
#include "Triangle.h"
#include "Shader.h"

namespace aglrl {
	enum class Flag {
		GL_VERSION_MAJOR,
		GL_VERSION_MINOR,
		GL_PROFILE
	};

	enum class GLProfile {
		CORE,
		COMPATIBILITY
	};

	extern Viewport viewport;

	template<typename T>
	void setFlag(Flag flag, T value);

	//user-defined
	void setting();
	void start();
	void tick();
}

#endif