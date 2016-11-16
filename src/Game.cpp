#include "Game.h"

namespace ar {

    Game::Game(sf::RenderWindow *p_window_pointer) {
        window_pointer = p_window_pointer;
        if(bg_music.openFromFile("./Sounds/bg_music.ogg")){
            bg_music.setVolume(33.f);
            bg_music.setLoop(true);
        }

        is_game_running = true;
        is_paused = false;
// TODO checking is musig exist
        frame_time = sf::seconds(1.f / 60.f);
        example_texture.loadFromFile("./test.png");
        example_object.setPosition(2.f,5.f);
        example_object.setTexture(&example_texture);

        this->run();
    }

    Game::~Game() {
        if(bg_music.getVolume() > 0.1f){
            bg_music.setVolume(0.f);
            bg_music.stop();
        }

    }

    void Game::handleEvents() {
        sf::Event event;
        while (window_pointer->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window_pointer->close();


            switch (event.key.code) {
                case sf::Keyboard::Escape:
                    is_game_running = false;
                    bg_music.stop();
                    window_pointer->close();
                    break;
                case sf::Keyboard::R:
                    is_game_running = false;
                    break;
                case sf::Keyboard::P:
                    is_paused = true;
                    break;
                default:
                    break;
            }
        }
    }


    void Game::run() {
        bg_music.play();


        sf::Clock clock;
        sf::Time elapsed_time_since_update = sf::Time::Zero;
        while (is_game_running) {

            sf::Time elapsed_time = clock.restart();
            elapsed_time_since_update += elapsed_time;
            if (elapsed_time_since_update > frame_time) {
                elapsed_time_since_update -= frame_time;
                this->handleEvents();
                this->update(frame_time);
                this->render();
            }
        }
    }

    void Game::update(sf::Time p_time_delta) {
        if (!is_paused) {
            // game logic
        }
    }

    void Game::render() {
        window_pointer->clear(sf::Color(75, 203, 208));
        // here draw objects
        example_object.draw(window_pointer);
        window_pointer->display();

    }
}