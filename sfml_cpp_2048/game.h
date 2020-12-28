#include "dto.h"
#include "util.h"

#pragma once

namespace _2048 {

	class game {
	private:
		dto &Dto = dto::get_instance();
		bool movability[4] = { 0 };
		bool movable = true;
		bool check_mergability(int x, int y, int direction);
		void game_over();
		void generate_random(int number);
		void check_movability();
		bool check_win();
		void win();

	public:
		game();

		void move(int direction);
	};

}