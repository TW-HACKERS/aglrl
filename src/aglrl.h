#ifndef _AGLRL_H
#define _AGLRL_H

#include <glm/glm.hpp>

#include "IEventHandler.h"
#include "Viewport.h"
#include "types.h"

namespace aglrl {
	extern Viewport viewport;

	void registerEventHandler(IEventHandler& eventHandler);

	//user-defined
	void start();
	void tick();
}

#endif