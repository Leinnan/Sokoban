//
// Created by piotr on 29.11.16.
//

#include "StartMenu.h"

namespace ar{
    StartMenu::StartMenu(sf::RenderWindow *p_window_pointer){
        this->window_pointer = p_window_pointer;
        menu_font.loadFromFile("./gfx/font.ttf");
    }

    void StartMenu::run() {
        is_game_running = true;

        while (is_game_running) {
            this->handleEvents();
            this->render();
            time_to_next_press--;
        }
    }

    void StartMenu::addOption(std::string p_option_name) {
        labels.push_back(sf::Text(p_option_name,menu_font));
        labels.back().setCharacterSize(font_size);
        labels.back().setStyle(sf::Text::Regular);
        labels.back().setFillColor(sf::Color::Red);

        this->updatePositions();
        this->updateState();
    }


    sf::RectangleShape StartMenu::getMenuRectangle(){
        sf::RectangleShape menu_rectangle;
        float rectangle_width = 0;
        float rectangle_height = 0;
        int longest_text_width = 0;
        for(unsigned int i = 0; i < labels.size(); i++){
            if(labels[i].getLocalBounds().width > longest_text_width)
                longest_text_width = labels[i].getLocalBounds().width;
            std::clog << labels[i].getLocalBounds().top << "\t";
            std::clog << labels[i].getLocalBounds().left << "\n";
        }
        // width is length of longest text and two options padding(from left and right)
        rectangle_width = options_padding * 2 + longest_text_width;
        // height is size of padding on top and bottom + (padding and font size) * text amount
        rectangle_height += options_padding * 2;
        rectangle_height += (options_padding + font_size) * labels.size();

        menu_rectangle.setPosition(position);
        menu_rectangle.setSize(sf::Vector2f(rectangle_width,rectangle_height));

        return menu_rectangle;

    }
    void StartMenu::updatePositions() {
        sf::RectangleShape menu_rectangle = getMenuRectangle();
        sf::Vector2f updated_pos;
        updated_pos.x = position.x;
        updated_pos.y = position.y;
        updated_pos.x += options_padding;

        for(unsigned int i = 0; i < labels.size(); i++){
            //if is centered x position looks like this
            // position = base_pos + (menu_size/2) -  (text_width/2)
            if(is_text_centered){
                updated_pos.x = position.x;
                updated_pos.x += menu_rectangle.getSize().x/2;
                updated_pos.x -= labels[i].getLocalBounds().width/2;
            }
            else{
                updated_pos.x = position.x + options_padding;
            }

            labels[i].setPosition(updated_pos);
            updated_pos.y += font_size;
            updated_pos.y += options_padding;

        }
    }

    void StartMenu::updateState(){

        for(unsigned int i = 0; i < labels.size(); i++){
            if(selected_option_nr == i){
                labels[i].setFillColor(sf::Color::Red);
            }
            else{
                labels[i].setFillColor(sf::Color::Green);
            }
        }
    }


    void StartMenu::handleEvents(){

        if(time_to_next_press < 1){
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                if(selected_option_nr <= 0)
                    selected_option_nr = labels.size() - 1;
                else
                    selected_option_nr--;
                this->updateState();
                time_to_next_press = 10;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
                if(selected_option_nr >= labels.size() - 1)
                    selected_option_nr = 0;
                else
                    selected_option_nr++;
                this->updateState();
                time_to_next_press = 10;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
                selected_option_nr = -1;
                is_game_running = false;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
                is_game_running = false;
            }
        }
    }

    void StartMenu::render() {
        window_pointer->clear(sf::Color(29,31,33));
        for(sf::Text option: labels){

            window_pointer->draw(option);

        }
        window_pointer->display();
    }
}