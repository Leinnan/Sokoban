#include "Engine.h"
#include "Game.h"

namespace ar {
    Engine::Engine(int p_game_state) {
        this->game_state = p_game_state;
        window.create(sf::VideoMode(800, 600), "SFML Game");
        window.setFramerateLimit(60);
        window.setMouseCursorVisible(false);

    }


    Engine::~Engine() {
    }

    void Engine::run() {
        while (window.isOpen()) {
            if(game_state == 0){
				if(show_intro){
					Intro intro(&window);
					intro.run();
				}
                switchGameState(2);
			}
            else if(game_state == 2){
                std::clog  << "Start Menu- deklaracja \n";
                ar::StartMenu start_menu(&window);
                std::clog  << "Start Menu- Dodawanie opcji \n";
                start_menu.addOption("Start game");
                start_menu.addOption("Exit game");

                std::clog  << "Start Menu- uruchomienie \n";
                start_menu.run();

                switch(start_menu.getSelectedOption()){
                    case 0:
                        switchGameState(DEFAULT_GAME_STATE);
                        break;
                    default:
                        return;

                }
            }
			if (game_state == DEFAULT_GAME_STATE) {
                ar::Game game(&window);
                game.run();
                switchGameState(2);
            }
			

        }
    }

    void Engine::switchGameState(int p_state) {
        if (p_state == -1) {
            this->game_state = DEFAULT_GAME_STATE;
        } else {
            this->game_state = p_state;
        }
    }
}