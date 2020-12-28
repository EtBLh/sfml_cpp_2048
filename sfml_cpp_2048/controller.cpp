#include "controller.h"
#include <iostream>

namespace _2048 {
	void controller::input(Keyboard::Key keycode) {
		if (this->Dto.is_game_over) return;
		if (this->Dto.won) return;
		bool key_pressed[4] = {
			keycode == Keyboard::Key::W, //0
			keycode == Keyboard::Key::A, //1
			keycode == Keyboard::Key::S, //2
			keycode == Keyboard::Key::D  //3
		};
		for (int i = 0; i < 4; i++) {
			if (!key_pressed[i]) continue;
			this->Game->move(i);
		}
	}
}