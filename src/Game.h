#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "Player.h"
#include "Box.h"
#include "Tilemap.h"
// import game object classes

// defines for game

namespace ar {
    class Game {
    public:
        Game(sf::RenderWindow *p_window_pointer);

        virtual ~Game();

        void run();

    protected:
    private:
        void handleEvents();
        void update(sf::Time p_time_delta);
        void render();

        void generetaBoxesByPos(std::vector<sf::Vector2i>);
        int getBoxByTileIndex(sf::Vector2i);

        sf::Time frame_time;

        sf::RenderWindow *window_pointer;
        sf::Music bg_music;
        bool is_game_running;
        bool is_paused;
        bool show_fps = false;

        // base font
        sf::Font basic_font;

        // fps label
        sf::Text fps_text;

        // game objects
        ar::Tilemap tilemap;
        sf::Texture tilemap_texture;
        sf::Texture player_texture;
        sf::Texture box_texture;
        ar::Player player;
        std::vector< ar::Box > boxes;
    };
}
#endif // GAME_H
