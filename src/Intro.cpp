#include "Intro.h"

Intro::Intro(sf::RenderWindow * p_window_pointer) :
is_logo_displaying(true)
{
    this->window_pointer = p_window_pointer;
    // load texture and set to sprite
    logo_texture.loadFromFile("./gfx/sfml-logo-small.png");
    logo_sprite.setTexture(logo_texture);
    
    // now lets center our sprite
    int window_width = this->window_pointer->getSize().x;
    int window_heigth = this->window_pointer->getSize().y;
    
    logo_sprite.setOrigin(logo_sprite.getGlobalBounds().width / 2,logo_sprite.getGlobalBounds().height / 2);
    
    float logo_position_x = window_width / 2;
    float logo_position_y = window_heigth / 2;
    
    logo_sprite.setPosition(logo_position_x,logo_position_y);
    logo_sprite.setScale(0.2f,0.2f);
}

Intro::~Intro()
{
}


void Intro::run()
{
    if(this->window_pointer->isOpen())
        is_logo_displaying = true;
    
	sf::Clock clock;
    intro_length = sf::seconds(3.0f);
	sf::Time elapsed_time_since_update = sf::Time::Zero;
	sf::Time total_elapsed_time = sf::Time::Zero;
    while (is_logo_displaying)
    {
        
		sf::Time elapsed_time = clock.restart();
		elapsed_time_since_update += elapsed_time;
        total_elapsed_time += elapsed_time;
        if(elapsed_time_since_update > frame_time){
            elapsed_time_since_update -= frame_time;
            this->draw();
            this->handleEvents();
            this->updateLogoScale(total_elapsed_time / intro_length);
            if(intro_length < total_elapsed_time){
                is_logo_displaying = false;
            }
        }
    }
}

void Intro::draw()
{
    window_pointer->clear(sf::Color(29,31,33));
    window_pointer->draw(logo_sprite);
    window_pointer->display();
}

void Intro::handleEvents()
{
    sf::Event event;
    if (this->window_pointer->pollEvent(event))
    {
        if ((event.type == sf::Event::Closed) || event.key.code == sf::Keyboard::Escape )
        {
            is_logo_displaying = false;
            this->window_pointer->close();
            return;
        }
    }
}


void Intro::updateLogoScale(float p_percentage_elapsed_time)
{
    float new_logo_scale = 0.2f;
    new_logo_scale += p_percentage_elapsed_time;
    if(new_logo_scale > 1.0f){
        new_logo_scale = 1.0f;
    }
    logo_sprite.setScale(new_logo_scale,new_logo_scale);
}