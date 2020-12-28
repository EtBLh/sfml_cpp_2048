#include "view.h"
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "util.h"

namespace _2048 {
	using namespace sf;
	using namespace util;
	void view::render() {

		int** map = this->Dto.map;

		window->clear(BG_COLOR);
		
		if (this->Dto.is_game_over || this->Dto.won) {
			
			Text end_msg;
			end_msg.setFont(font);
			end_msg.setFillColor(FONT_COLOR);
			end_msg.setPosition(50, (WINDOW_HEIGHT-FONT_SIZE*3)/2);
			end_msg.setCharacterSize(this->Dto.won?FONT_SIZE:FONT_SIZE*3);
			end_msg.setString(this->Dto.won?"congratulation!":"game over");
			end_msg.setStyle(Text::Bold);

			window->draw(end_msg);
		}
		else {

			RectangleShape frame(Vector2f(FRAME_LENGTH, FRAME_LENGTH));
			frame.setPosition(FRAME_POS_X, FRAME_POS_Y);
			frame.setSize(Vector2f(FRAME_LENGTH, FRAME_LENGTH));
			frame.setFillColor(FRAME_COLOR);
			window->draw(frame);

			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					RectangleShape block(Vector2f(BLOCK_LENGTH, BLOCK_LENGTH));
					float	pos_x = FRAME_POS_X + (1 + i) * BLOCK_GAP + i * BLOCK_LENGTH,
						pos_y = FRAME_POS_Y + (1 + j) * BLOCK_GAP + j * BLOCK_LENGTH;
					block.setPosition(pos_x, pos_y);
					block.setFillColor(BLOCK_COLOR);

					window->draw(block);

					if (map[i][j] != 0) {
						RectangleShape number_block(Vector2f(BLOCK_LENGTH, BLOCK_LENGTH));
						number_block.setPosition(pos_x, pos_y);
						if (map[i][j] > 2048 || map[i][j] < 2) return;
						block.setFillColor(NUMBER_COLOR[(int)log2(map[i][j])]);

						Text number;
						number.setFont(font);
						number.setFillColor(FONT_COLOR);
						number.setPosition(pos_x + 5, pos_y);
						number.setCharacterSize(FONT_SIZE);
						number.setString(std::to_string(map[i][j]));
						number.setStyle(Text::Bold);

						window->draw(block);
						window->draw(number);
					}
				}
			}
		}

		Text step_view;
		step_view.setFont(font);
		step_view.setFillColor(FONT_COLOR);
		step_view.setPosition(STEP_VIEW_POS_X,STEP_VIEW_POS_Y);
		step_view.setCharacterSize(FONT_SIZE);
		step_view.setString("steps: " + std::to_string(this->Dto.step));
		step_view.setStyle(Text::Bold);

		Text max_view;
		max_view.setFont(font);
		max_view.setFillColor(FONT_COLOR);
		max_view.setPosition(MAX_VIEW_POS_X, MAX_VIEW_POS_Y);
		max_view.setCharacterSize(FONT_SIZE);
		max_view.setString("current max: " + std::to_string(this->Dto.max));
		max_view.setStyle(Text::Bold);

		window->draw(step_view);
		window->draw(max_view);

		window->display();
	}
	view::view(RenderWindow* window): window(window) {
		if (!font.loadFromFile("./clear-sans/ClearSans-Medium.ttf")) {
			std::cout << "can't load font" << std::endl;
		};
	};
}