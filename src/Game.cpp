#include "Game.h"

namespace ar {

    Game::Game(sf::RenderWindow *p_window_pointer) :
        tilemap("/home/piotr/Projekty/Sokoban/build/maps/1.txt") {
        window_pointer = p_window_pointer;
        if(bg_music.openFromFile("./Sounds/bg_music.ogg")){
            bg_music.setVolume(33.f);
            bg_music.setLoop(true);
        }

        basic_font.loadFromFile("./gfx/font.ttf");

        fps_text.setFont(basic_font);
        fps_text.setFillColor(sf::Color::Black);
        fps_text.setCharacterSize(15);
        fps_text.setPosition(sf::Vector2f(window_pointer->getSize().x-100.f,10.f));

        is_game_running = true;
        is_paused = false;
        frame_time = sf::seconds(1.f / 60.f);
        tilemap_texture.loadFromFile("./gfx/tilemap_smaller.png");

        tilemap.setTileMapTex(&tilemap_texture);

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


        sf::Clock delta_clock;
        sf::Time delta_time;
        float last_time = 0;
        std::string fps_string = "none";
        while (is_game_running) {
            this->handleEvents();
            this->update(delta_time);
            this->render();
            delta_time = delta_clock.restart();
            if(show_fps){
                fps_string = std::to_string(1.f / (delta_time.asSeconds() - last_time));
                fps_string = fps_string.substr(0,4);
                fps_string += " FPS";
                last_time = delta_time.asSeconds();
                fps_text.setString(fps_string);
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
        tilemap.draw(window_pointer);

        //interface last
        if(show_fps){
            window_pointer->draw(fps_text);
        }
        window_pointer->display();

    }
}