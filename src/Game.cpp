#include "Game.h"

namespace ar {

    Game::Game(sf::RenderWindow *p_window_pointer) :
        tilemap("maps/1.txt"){
        window_pointer = p_window_pointer;
		game_view.setSize(sf::Vector2f(800.f, 600.f));
		game_view.setCenter(sf::Vector2f(340.f, 280.f));
		window_pointer->setView(game_view);
        if(bg_music.openFromFile("./sfx/bg_music.ogg")){
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
			
		level_complete_bg.setFillColor(sf::Color(49,179,44,120));
		level_complete_bg.setSize(sf::Vector2f(2222, 2222));
		level_complete_bg.setPosition(sf::Vector2f(0, 0));
			
		level_complete_label.setFont(basic_font);
        level_complete_label.setOutlineColor(sf::Color::Black);
        level_complete_label.setFillColor(sf::Color::White);
        level_complete_label.setOutlineThickness(1.f);
        level_complete_label.setCharacterSize(25);
        level_complete_label.setPosition(sf::Vector2f(300.f,5.f));
		level_complete_label.setString("YOU WIN!\n Press Enter");

        is_game_running = true;
        is_paused = false;
        frame_time = sf::seconds(1.f / 60.f);
        tilemap_texture.loadFromFile("./gfx/tilemap.png");
        player_texture.loadFromFile("./gfx/player.png");
        box_texture.loadFromFile("./gfx/box.png");

        tilemap.setTileMapTex(&tilemap_texture);
        player.setTexture(&player_texture);

        player.setTilePosition(tilemap.getPlayerStartPos());

        this->generetaBoxesByPos(tilemap.getBoxesStartPos());

        this->targets = tilemap.getTargetsStartPos();

        map_paths.push_back("maps/1.txt");
        map_paths.push_back("maps/2.txt");
        map_paths.push_back("maps/3.txt");


        this->run();
    }

    Game::~Game() {
        if(bg_music.getVolume() > 0.1f){
            bg_music.setVolume(0.f);
            bg_music.stop();
        }

    }

    void Game::setMap(std::string p_map_path){
        ar::Tilemap new_tilemap(p_map_path);
        tilemap = new_tilemap;
        tilemap.setTileMapTex(&tilemap_texture);
        this->targets = tilemap.getTargetsStartPos();
        this->generetaBoxesByPos(tilemap.getBoxesStartPos());
        player.setTilePosition(tilemap.getPlayerStartPos());
        level_complete = false;

    }

    bool Game::loadNextMap(){
        current_map_index++;
        if(current_map_index > map_paths.size()-1)
            return false;
        else{
            setMap(map_paths[current_map_index]);
            return true;
        }

    }
    void Game::reloadCurrentMap(){
        setMap(map_paths[current_map_index]);
    }

    void Game::generetaBoxesByPos(std::vector<sf::Vector2i> p_boxes_pos) {
        std::vector< ar::Box > new_boxes;
        for (auto &&balls_pos : p_boxes_pos) {
            ar::Box new_box;
            new_box.setTilePosition(balls_pos);
            new_box.setTexture(&box_texture);
            new_boxes.push_back(new_box);
        }
        boxes = new_boxes;
    }
    int Game::getBoxByTileIndex(sf::Vector2i p_tile) {
        unsigned int index = 0;
        for (auto &&box : boxes) {
            if(box.getCurrentTile() == p_tile)
                return index;
            index++;
        }
        // if no Box in this pos return -1
        return -1;
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

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && level_complete)
                if(!loadNextMap())
                    is_game_running = false;


            switch (event.key.code) {
                case sf::Keyboard::Escape:
                    is_game_running = false;
                    bg_music.stop();
                    window_pointer->close();
                    break;
                case sf::Keyboard::R:
                    reloadCurrentMap();
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
        if (!is_paused && !level_complete) {
            if(player.isMoving()){
                std::clog << "PLAYER UPDATE " << player.getPosition().x << ", " << player.getPosition().y << "\n";
                sf::Vector2i destination_index = player.getDestinationTile();
                if(!tilemap.isTilePassable(destination_index)){
                    player.canMove(false);
                }
                if(getBoxByTileIndex(player.getDestinationTile()) != -1){
                    unsigned int ball_index = getBoxByTileIndex(player.getDestinationTile());
                    player.canMove(false);
                    sf::Vector2i box_movement(
                            player.getDestinationTile() - player.getCurrentTile());

                    if(tilemap.isTilePassable(player.getDestinationTile() + box_movement) &&
                            getBoxByTileIndex(player.getDestinationTile() + box_movement) == -1){
                        boxes[ball_index].move(box_movement);
                        player.canMove(true);
                    }
                }
            }
            player.update(p_time_delta);
			
			box_amount_on_targets = 0;
			
            for (auto &&box : boxes) {
                box.update(p_time_delta);

                box.isOnTarget(false);
                for (auto &&target : targets) {
                    if(box.getCurrentTile() == target){
						box_amount_on_targets++;
                        box.isOnTarget(true);
					}
                }
            }
			if(box_amount_on_targets == boxes.size()){
			   level_complete = true;
			}
        }
        else{
            if(current_map_index+1 == map_paths.size()){
                level_complete_label.setString("THE END!\n CONGRATULATIONS!");
                game_end = true;
            }
        }
    }

    void Game::render() {
		if(level_complete)
        	window_pointer->clear(sf::Color(49,179,44));
		else
        	window_pointer->clear(sf::Color(88, 99, 116));
        // here draw objects
        tilemap.draw(window_pointer);
        player.draw(window_pointer);
        for (auto &&box : boxes) {
            box.draw(window_pointer);
        }

        //interface last
        if(show_fps){
            window_pointer->draw(fps_text);
        }
		//after win
		if(level_complete){
			window_pointer->draw(level_complete_bg);
			window_pointer->draw(level_complete_label);
		}
        window_pointer->display();

    }
}