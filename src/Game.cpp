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
        fps_text.setOutlineColor(sf::Color::Black);
        fps_text.setFillColor(sf::Color::White);
        fps_text.setOutlineThickness(2.2f);
        fps_text.setCharacterSize(15);
        fps_text.setPosition(sf::Vector2f(5.f,5.f));

        is_game_running = true;
        is_paused = false;
        frame_time = sf::seconds(1.f / 60.f);
        tilemap_texture.loadFromFile("./gfx/tilemap_smaller.png");
        player_texture.loadFromFile("./gfx/player.png");

        tilemap.setTileMapTex(&tilemap_texture);
        player.setTexture(&player_texture);

        player.setTilePosition(tilemap.getPlayerStartPos());



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

            if(!player.isMoving()){
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                    player.move(M_LEFT);
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                    player.move(M_UP);
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                    player.move(M_RIGHT);
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                    player.move(M_DOWN);



            }


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
                float fps_current = 1.f / (delta_time.asSeconds() - last_time);
                if(fps_current > 0){
                    fps_string = std::to_string(fps_current);
                    fps_string += " FPS";
                    last_time = delta_time.asSeconds();
                    fps_text.setString(fps_string);
                }
            }
        }
    }

    void Game::update(sf::Time p_time_delta) {
        if (!is_paused) {
            if(player.isMoving())
                std::clog << "PLAYER UPDATE " << player.getPosition().x << ", " << player.getPosition().y << "\n";
            if(player.isMoving()){
                sf::Vector2i destination_index = player.getDestinationTile();
                if(!tilemap.isTilePassable(destination_index.x,destination_index.y)){
                    player.canMove(false);
                }
            }
            player.update(p_time_delta);
        }
    }

    void Game::render() {
        window_pointer->clear(sf::Color(75, 203, 208));
        // here draw objects
        tilemap.draw(window_pointer);
        player.draw(window_pointer);

        //interface last
        if(show_fps){
            window_pointer->draw(fps_text);
        }
        window_pointer->display();

    }
}