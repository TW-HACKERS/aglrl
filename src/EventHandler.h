#ifndef _AGLRL_IEVENT_HANDLER_H
#define _AGLRL_IEVENT_HANDLER_H

#include <vector>
#include <string>

namespace aglrl {
	class EventHandler {
	private:
		static std::vector<EventHandler*> eventHandlers;
	public:
		static void registerHandler(EventHandler* handler) { eventHandlers.push_back(handler); }
		static void triggerEvent(std::string event)
		{
			for (EventHandler* handler : eventHandlers) {
				if (event == "init") handler->onInit();
				if (event == "GLLoaded") handler->onGLLoaded();
			}
		}
		virtual void onInit() {}
		virtual void onGLLoaded() {}
	};
}

#endif