#ifndef ENGINE_H
#define ENGINE_H

#define DEFAULT_GAME_STATE 1

#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Intro.h"

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
        unsigned int game_state = 0;
		bool show_intro = false;
    };
}
#endif // ENGINE_H
