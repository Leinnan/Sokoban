//
// Created by piotr on 17.11.16.
//

#ifndef SFML_SOKOBAN_BALL_H
#define SFML_SOKOBAN_BALL_H

#include <SFML/Graphics.hpp>
#include "Object.h"
namespace ar{
    class Ball : public Object {
    public:
        Ball();
        void setTilePosition(sf::Vector2i p_new_pos);
    private:
        sf::Vector2i current_tile;
        sf::Vector2i destination_tile;
        float speed = 2.3f;
        bool is_moving = false;
        bool can_move = true;
        unsigned int tile_length = 30;
        float completion = 0;

    };
}



#endif //SFML_SOKOBAN_BALL_H
