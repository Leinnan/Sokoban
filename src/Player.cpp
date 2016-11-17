//
// Created by piotr on 16.11.16.
//

#include "Player.h"

namespace ar{

    Player::Player() {
        this->setSpriteColor(sf::Color::White);
        current_tile.x = 5;
        current_tile.y = 2;
        setPosition(current_tile.x*tile_length,current_tile.y*tile_length);
    }
    void Player::move(unsigned int direction) {

        is_moving = true;
        destination.x = current_tile.x*tile_length;
        destination.y = current_tile.y*tile_length;
        destination_tile = current_tile;

        if(direction == M_UP){
            destination.y -= tile_length;
            destination_tile.y--;
        }
        else if(direction == M_LEFT){
            destination.x -= tile_length;
            destination_tile.x--;
        }
        else if(direction == M_DOWN){
            destination.y += tile_length;
            destination_tile.y++;
        }
        else if(direction == M_RIGHT){
            destination.x += tile_length;
            destination_tile.x++;
        }
        else{
            is_moving = false;
        }

    }
    void Player::update(sf::Time p_delta) {
        if(!is_moving) {
            setPosition(current_tile.x * tile_length, current_tile.y * tile_length);
            completion = 0.f;
        }
        else{

            completion += p_delta.asSeconds() * speed;
            if(completion <= 1){
                sf::Vector2f current_position(current_tile.x*tile_length,current_tile.y*tile_length);
                current_position += (destination - current_position) * completion;
                setPosition(current_position);
            }
            else{
                current_tile = destination_tile;
                is_moving = false;
            }

        }

    }

}