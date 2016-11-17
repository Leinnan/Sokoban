#ifndef OBJECT_H
#define OBJECT_H
#include <SFML/Graphics.hpp>

namespace ar {
    class Object {
    public:
        Object() {};

        ~Object() {};

        virtual void update(sf::Time p_time_delta) {};

        virtual void draw(sf::RenderWindow *p_window_pointer);

        void setPosition(sf::Vector2f p_position);

        void setPosition(float p_position_x, float p_position_y);

        void setTexture(sf::Texture *p_texture_pointer);

        sf::Vector2f getPosition() {
            return position;
        };

        sf::Sprite getSprite() {
            return sprite;
        };

        void move(float p_position_x, float p_position_y);

        void move(sf::Vector2f p_position);

        inline void setSpriteColor(sf::Color p_color){ sprite.setColor(p_color);};

    private:
        sf::Sprite sprite;
        sf::Vector2f position;
        sf::Texture *texture_pointer;
    };
}
#endif // OBJECT_H
