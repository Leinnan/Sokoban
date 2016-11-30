//
// Created by piotr on 22.11.16.
//

#ifndef SFML_SOKOBAN_MENU_H
#define SFML_SOKOBAN_MENU_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

namespace ar {

    class Menu {
    public:
        Menu(sf::RenderWindow *p_window_pointer);

        ~Menu() = default;

        void run();

    private:
        void handleEvents();

        void update();

        void render();

        sf::RenderWindow *window_pointer;
        sf::Time time_between_option_change;
        std::vector< std::string > map_paths;
    };

}

#endif //SFML_SOKOBAN_MENU_H
