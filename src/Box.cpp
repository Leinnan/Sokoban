//
// Created by piotr on 17.11.16.
//

#include "Box.h"
namespace ar{

    Box::Box() {
        this->setSpriteColor(sf::Color::Yellow);
        setPosition(current_tile.x*tile_length,current_tile.y*tile_length);
    }

    void Box::move(sf::Vector2i p_move_vector) {
        is_moving = true;
        destination_tile = current_tile + p_move_vector;
    }

    void Box::setTilePosition(sf::Vector2i p_new_pos) {
        current_tile = p_new_pos;
        destination_tile = p_new_pos;
        is_moving = false;
        setPosition(p_new_pos.x*tile_length,p_new_pos.y*tile_length);

    }

    void Box::update(sf::Time p_delta) {
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

        if(is_on_target){
            setSpriteColor(sf::Color::Green);
        }
        else{
            setSpriteColor(sf::Color::White);
        }
    }
}