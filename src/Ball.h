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
        virtual void update(sf::Time p_delta) override ;
        void setTilePosition(sf::Vector2i p_new_pos);
        void move(sf::Vector2i p_move_vector);
        inline sf::Vector2i getCurrentTile(){return current_tile;};
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
