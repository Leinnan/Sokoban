#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "Player.h"
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

        sf::Time frame_time;

        sf::RenderWindow *window_pointer;
        sf::Music bg_music;
        bool is_game_running;
        bool is_paused;
        bool show_fps = true;

        // base font
        sf::Font basic_font;

        // fps label
        sf::Text fps_text;

        // game objects
        ar::Tilemap tilemap;
        sf::Texture tilemap_texture;
        sf::Texture player_texture;
        ar::Player player;
    };
}
#endif // GAME_H
