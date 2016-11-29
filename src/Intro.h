#ifndef INTRO_H
#define INTRO_H
#include <SFML/Graphics.hpp>
#include "Arkona/Arkona.h"

class Intro
{
public:
    Intro(sf::RenderWindow * p_window_pointer);
    ~Intro();
    void run();
private:
    void handleEvents();
    void draw();
    void updateLogoScale(float p_percentage_elapsed_time);
    sf::Time frame_time;
    sf::Time intro_length;
    sf::RenderWindow * window_pointer;
    sf::Texture logo_texture;
    sf::Sprite logo_sprite;
    bool is_logo_displaying;
};

#endif // INTRO_H
