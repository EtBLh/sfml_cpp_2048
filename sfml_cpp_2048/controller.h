#include <SFML/Graphics.hpp>
#include "game.h"
#pragma once

namespace _2048{
	using namespace sf;
	class controller {
	private:
		game* Game = NULL;
		dto& Dto = dto::get_instance();
	public:
		controller(game* Game) :Game(Game) {};
		void input(Keyboard::Key keycode);
	};
}
