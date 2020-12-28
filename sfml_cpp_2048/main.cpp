#include "dto.h"
#include "game.h"
#include "view.h"
#include "controller.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace _2048;
using namespace sf;

int main() {
    RenderWindow* window = new RenderWindow(VideoMode(util::WINDOW_WIDTH, util::WINDOW_HEIGHT), "2048");

	view View(window);
	game* Game = new game();
    controller Controller(Game);

    while (window->isOpen())
    {
        Event event;
        while (window->pollEvent(event))
        {
            if (event.type == Event::Closed)
                window->close();
            if (event.type == Event::KeyReleased)
                Controller.input(event.key.code);
        }

        View.render();
    }

    return 0;
}