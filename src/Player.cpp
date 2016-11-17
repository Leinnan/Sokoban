//
// Created by piotr on 16.11.16.
//

#include "Player.h"

namespace ar{

    Player::Player() {
        this->setSpriteColor(sf::Color::White);
        setPosition(current_tile.x*tile_length,current_tile.y*tile_length);
    }
    void Player::move(unsigned int direction) {

        is_moving = true;
        destination_tile = current_tile;

        if(direction == M_UP){
            destination_tile.y--;
        }
        else if(direction == M_LEFT){
            destination_tile.x--;
        }
        else if(direction == M_DOWN){
            destination_tile.y++;
        }
        else if(direction == M_RIGHT){
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
        else if(!can_move){
            setPosition(current_tile.x * tile_length, current_tile.y * tile_length);
            destination_tile = current_tile;
            can_move = true;
        }
        else{
            completion += p_delta.asSeconds() * speed;
            if(completion <= 1){
                sf::Vector2f current_position(current_tile.x*tile_length,current_tile.y*tile_length);
                sf::Vector2f destination(destination_tile.x*tile_length,destination_tile.y*tile_length);
                current_position += (destination - current_position) * completion;
                setPosition(current_position);
            }
            else{
                completion = 0.f;
                current_tile = destination_tile;
                is_moving = false;
                setPosition(current_tile.x*tile_length,current_tile.y*tile_length);
            }

        }

    }

    void Player::setTilePosition(sf::Vector2i p_new_pos) {
        current_tile = p_new_pos;
        destination_tile = p_new_pos;
        is_moving = false;
        setPosition(p_new_pos.x*tile_length,p_new_pos.y*tile_length);

    }
}