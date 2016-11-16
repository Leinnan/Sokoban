#include "Object.h"
namespace ar{

    void Object::setPosition(sf::Vector2f p_position)
    {
        this->position = p_position;
        this->sprite.setPosition(this->position);
    }

    void Object::setPosition(float p_position_x, float p_position_y)
    {
        this->position.x = p_position_x;
        this->position.y = p_position_y;
        this->sprite.setPosition(this->position);
    }

    void Object::move(float p_position_x, float p_position_y)
    {
        sf::Vector2f movement(p_position_x, p_position_y);
        this->position += movement;
        this->sprite.setPosition(this->position);
    }

    void Object::move(sf::Vector2f p_position)
    {
        this->position += p_position;
        this->sprite.setPosition(this->position);
    }

    void Object::setTexture(sf::Texture * p_texture_pointer)
    {
        this->texture_pointer = p_texture_pointer;
        sprite.setTexture(*texture_pointer);
    }

    void Object::draw(sf::RenderWindow * p_window_pointer){
        this->sprite.setPosition(this->position);
        p_window_pointer->draw(this->sprite);

    }
}