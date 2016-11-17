//
// Created by piotr on 17.11.16.
//

#include "Ball.h"
namespace ar{

    Ball::Ball() {
        this->setSpriteColor(sf::Color::Yellow);
        setPosition(current_tile.x*tile_length,current_tile.y*tile_length);
    }

    void Ball::setTilePosition(sf::Vector2i p_new_pos) {
        current_tile = p_new_pos;
        destination_tile = p_new_pos;
        is_moving = false;
        setPosition(p_new_pos.x*tile_length,p_new_pos.y*tile_length);

    }
}