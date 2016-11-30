#ifndef ENGINE_H
#define ENGINE_H

#define DEFAULT_GAME_STATE 1

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"
#include "Intro.h"
#include "StartMenu.h"

namespace ar {
    class Engine {
    public:
        Engine(int p_game_state = 0);

        ~Engine();

        void switchGameState(int p_state = -1);

        void run();

    private:
        sf::RenderWindow window;
        // 1 = Gameplay
        // 0 = Intro
        // 2 = Start menu
        unsigned int game_state = 0;
		bool show_intro = true;
    };
}
#endif // ENGINE_H
