//
// Created by piotr on 29.11.16.
//

#ifndef SFML_SOKOBAN_STARTMENU_H
#define SFML_SOKOBAN_STARTMENU_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>
#include <iostream>

namespace ar {

    class StartMenu {
    public:
        StartMenu(sf::RenderWindow *p_window_pointer);
        void addOption(std::string p_option_name);
        void run();
        unsigned int getSelectedOption(){ return selected_option_nr;};
    private:
        void handleEvents();
        void render();

        sf::RectangleShape getMenuRectangle();
        void updatePositions();
        void updateState();

        sf::RenderWindow *window_pointer;
        std::vector < sf::Text > labels;
        int selected_option_nr = 0;
        sf::Font menu_font;
        sf::Vector2f position;
        unsigned int options_padding = 15;
        int time_to_next_press = 10;
        unsigned int font_size = 25;
        bool is_game_running = false;
        bool is_text_centered = true;
    };

}
#endif //SFML_SOKOBAN_STARTMENU_H
