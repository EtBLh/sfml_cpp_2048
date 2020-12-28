#include "game.h"
#include <iostream>

namespace _2048 {

	bool game::check_mergability(int x, int y, int direction) {
		int** map = this->Dto.map;
		if (map[x][y] == 0) return false;
		vector next = {
			x + util::DIRECTION_UNIT_VECTOR[direction][0],
			y + util::DIRECTION_UNIT_VECTOR[direction][1]
		};
		if (next[0] < 0 || next[0] >=4) return false;
		if (next[1] < 0 || next[1] >=4) return false;
		return map[x][y] == map[next[0]][next[1]] || map[next[0]][next[1]] == 0;
	}

	void game::check_movability() {
		movable = false;
		for (int i = 0; i < 4; i++) {
			movability[i] = false;
		}
		for (int m = 0; m < 4; m++) {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (check_mergability(i, j, m)) {
						movability[m] = true;
						movable = true;
						break;
					}
				}
				if (movability[m])break;
			}
		}
	}

	void game::move(int direction) {
		if (!movability[direction]) return;
		int** map = this->Dto.map;
		this->Dto.step++;
		
		for (int i = 0; i < 5; i++) {
			if (util::move_commands[direction][i] != NULL)
				util::move_commands[direction][i](map);
		}

		int max = 0;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				max = max < map[i][j] ? map[i][j] : max;
			}
		}
		this->Dto.max = max;

		generate_random(-1);
		check_movability();
		if(check_win())win();
		if (!movable) game_over();
	}

	/**
	* generate a random number in a empty block.
	*/
	void game::generate_random(int number){
		int* map_1D = this->Dto.mem;
		int empty_blocks[16] = { 0 };
		int empty_count = 0;
		for (int i = 0; i < 16; i++) {
			if (map_1D[i] == 0)
				empty_blocks[empty_count++] = i;
		}
		if (empty_count == 0)return;
		int random_index = (int)(((double)rand() / (double)RAND_MAX) * empty_count);
		map_1D[empty_blocks[random_index]] = number != -1? number:((int)(((double)rand() / ((double)RAND_MAX + 1)) * 2)) * 2 + 2;
	}

	bool game::check_win() {
		int** map = Dto.map;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (map[i][j] == 2048) return true;
			}
		}
		return false;
	}

	void game::win() {
		Dto.won = true;
		std::cout << "won" << std::endl;
	}

	void game::game_over() {
		Dto.is_game_over = true;
		std::cout << "game over" << std::endl;
	}

	game::game() {
		srand(time(0));
		std::fill_n(this->movability, 4, true);
		generate_random(2);
		generate_random(2);
	};

}