#include "dto.h"
#include <cstddef>
#include <SFML/Graphics.hpp>

#pragma once

namespace _2048 {
	using namespace sf;
	class view
	{
	private:
		dto &Dto = dto::get_instance();
		RenderWindow* window;
		Font font;
	public:
		view(RenderWindow* window);
		void render();
	};
}
