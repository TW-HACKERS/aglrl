#ifndef _AGLRL_DRAWABLE_H
#define _AGLRL_DRAWABLE_H

#include <string>
#include <unordered_map>

namespace aglrl {
	class Drawable {
	private:
		static std::unordered_map<std::string, Drawable*> drawables;
		
	public:
		static void addDrawable(std::string name, Drawable* drawable)
		{
			drawables[name] = drawable;
		}

		static Drawable* getDrawable(std::string name)
		{
			return drawables[name];
		}

		virtual void draw() = 0;
	};
}

#endif