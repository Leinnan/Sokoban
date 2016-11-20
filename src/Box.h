//
// Created by piotr on 17.11.16.
//

#ifndef SFML_SOKOBAN_BALL_H
#define SFML_SOKOBAN_BALL_H

#include <SFML/Graphics.hpp>
#include "Object.h"
namespace ar{
    class Box : public Object {
    public:
        Box();
        virtual void update(sf::Time p_delta) override ;
        void setTilePosition(sf::Vector2i p_new_pos);
        void move(sf::Vector2i p_move_vector);
        inline sf::Vector2i getCurrentTile(){return current_tile;};
        inline bool isOnTarget(){return is_on_target;};
        inline void isOnTarget(bool p_on_target){ is_on_target = p_on_target;};
    private:
        sf::Vector2i current_tile;
        sf::Vector2i destination_tile;
        float speed = 2.7f;
        bool is_moving = false;
        bool can_move = true;
        bool is_on_target = false;
        unsigned int tile_length = 40;
        float completion = 0;

    };
}



#endif //SFML_SOKOBAN_BALL_H
