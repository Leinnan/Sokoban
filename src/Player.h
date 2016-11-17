//
// Created by piotr on 16.11.16.
//

#ifndef SFML_SOKOBAN_PLAYER_H
#define SFML_SOKOBAN_PLAYER_H

#define M_UP    0
#define M_RIGHT 1
#define M_DOWN  2
#define M_LEFT  3


#include <SFML/Graphics.hpp>
#include "Object.h"
namespace ar{

class Player : public Object {
public:
    Player();
    virtual void update(sf::Time p_delta) override ;
    void setDestinationTile(uint8_t p_x, uint8_t p_y, unsigned int p_tile_length);
    inline bool isMoving(){return is_moving;};
    void move(unsigned int direction);
private:
    sf::Vector2f destination;
    sf::Vector2i current_tile;
    sf::Vector2i destination_tile;
    unsigned int speed = 1;
    bool is_moving = false;
    unsigned int tile_length = 30;
    float completion = 0;
};
}

#endif //SFML_SOKOBAN_PLAYER_H