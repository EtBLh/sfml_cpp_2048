#include <SFML/Graphics.hpp>
#include <functional>
#pragma once

using namespace sf;

typedef int vector[2];
typedef std::function<void(int**)> command;

namespace _2048 {
	// utility functions of _2048
	namespace util {

		enum DIRECTION { UP = 0, LEFT = 1, DOWN = 2, RIGHT = 3 };
		const vector DIRECTION_UNIT_VECTOR[4] = {
			{0,-1},	//UP
			{-1,0},	//LEFT
			{0,1},	//DOWN
			{1,0}	//RIGHT
		};

		const Color	BG_COLOR = Color(0xfa, 0xf8, 0xef),
					FRAME_COLOR = Color(0xbb, 0xad, 0xa0),
					BLOCK_COLOR = Color(238, 228, 218, 0.35 * 255),
					FONT_COLOR = Color(0x77, 0x6e, 0x65),
					NUMBER_COLOR[11] = {
						Color(0xee,0xe4,0xda),
						Color(0xee, 0xe1, 0xc9),
						Color(0xf3, 0xb2, 0x7a),
						Color(0xf6, 0x96, 0x64),
						Color(0xf7, 0x7c, 0x5f),
						Color(0xf7, 0x5f, 0x3b),
						Color(0xed, 0xd0, 0x73),
						Color(0xed, 0xcc, 0x62),
						Color(0xed, 0xc9, 0x50),
						Color(0xed, 0xc5, 0x3f),
						Color(0xed, 0xc2, 0x2e)
					};
		const float	WINDOW_WIDTH = 600,
					WINDOW_HEIGHT = 900,
					FRAME_LENGTH = 500,
					FRAME_POS_X = 50,
					FRAME_POS_Y = 200,
					BLOCK_LENGTH = 100,
					BLOCK_GAP = 20;
		const float	STEP_VIEW_POS_X = 50,
					STEP_VIEW_POS_Y = 750,
					MAX_VIEW_POS_X = 50,
					MAX_VIEW_POS_Y = 800;
		const int	FONT_SIZE = 36;

		const auto rotate_matrix = [=](int** mat) -> void {
			for (int x = 0; x < 4 / 2; x++) {
				for (int y = x; y < 4 - x - 1; y++) {
					int temp = mat[x][y];

					mat[x][y] = mat[y][4 - 1 - x];

					mat[y][4 - 1 - x]
						= mat[4 - 1 - x][4 - 1 - y];

					mat[4 - 1 - x][4 - 1 - y]
						= mat[4 - 1 - y][x];

					mat[4 - 1 - y][x] = temp;
				}
			}
		};

		const auto transpose = [=](int** arr) -> void {
			for (int i = 0; i < 4 - 1; i++) {
				for (int j = i + 1; j < 4; j++) {
					//swap arr[i][j], arr[j][i]
					int temp = arr[i][j];
					arr[i][j] = arr[j][i];
					arr[j][i] = temp;
				}
			}
		};

		const auto rotate_right = [=](int** arr) -> void {
			for (int i = 0; i < 3; i++)
				rotate_matrix(arr);
		};

		const auto rotate_left = rotate_matrix;

		const auto merge = [=](int** map, int x, int y, int direction) -> void {

			if (map[x][y] == 0) return;

			vector next = { 
				x + DIRECTION_UNIT_VECTOR[direction][0],
				y + DIRECTION_UNIT_VECTOR[direction][1]
			};

			if (next[0] < 0 || next[0] >= 4) return;
			if (next[1] < 0 || next[1] >= 4) return;
			
			do {

				if (map[next[0]][next[1]] == 0 || map[next[0]][next[1]] == map[x][y]) {
					map[next[0]][next[1]] += map[x][y];
					map[x][y] = 0;
					x = next[0];
					y = next[1];
					next[0] += DIRECTION_UNIT_VECTOR[direction][0];
					next[1] += DIRECTION_UNIT_VECTOR[direction][1];
				}

				if (next[0] < 0 || next[0] >= 4) return;
				if (next[1] < 0 || next[1] >= 4) return;

			} while (map[next[0]][next[1]] == 0 || map[x][y] == map[next[0]][next[1]]);
		};

		const auto move_right = [=](int** arr) -> void{
			for (int i = 3; i >= 0; i--) {
				for (int j = 0; j < 4; j++) {
					merge(arr, i, j, DIRECTION::RIGHT);
				}
			}
		};

		const command move_commands[4][5] = {
			{ rotate_left,		move_right,		rotate_right,		NULL, NULL },
			{ transpose,		rotate_left,	move_right,		rotate_right,	transpose },
			{ transpose,		move_right,		transpose,		NULL,NULL },
			{ move_right,		NULL,NULL,NULL,NULL }
		};
	}
}