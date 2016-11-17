//
// Created by piotr on 16.11.16.
//

#ifndef SFML_SOKOBAN_TILEMAP_H
#define SFML_SOKOBAN_TILEMAP_H

#define TILES_X 15
#define TILES_Y 15
#define PLAYER_SYMBOL 'p'
#define BALL_SYMBOL   'o'

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

namespace ar{
    struct TileType{
        sf::Vector2i tex_index;
        bool is_wall = false;
        char symbol;
    };

    class Tilemap {
    public:
        Tilemap();
        Tilemap(std::string p_file_path);
        ~Tilemap() {};
        void generateTileTypes();//TODO version with config file
        inline void setTileMapTex(sf::Texture *p_texture_pointer){ this->texture_pointer = p_texture_pointer;};
        void draw(sf::RenderWindow *p_window_pointer);
        bool isTilePassable(unsigned int p_x, unsigned int p_y);
        inline sf::Vector2i getPlayerStartPos(){ return player_start;};
        inline std::vector< sf::Vector2i > getBallsByPos(){ return balls_pos;};
    private:
        void configTile(unsigned int p_x, unsigned int p_y, TileType p_tile_type);
        void generateMap();
        void generateMap(std::string p_file_path);
        std::vector< ar::TileType > tile_types;
        std::vector< sf::Vector2i > balls_pos;
        sf::Texture *texture_pointer;
        sf::VertexArray map_graphic;
        unsigned int tile_length = 30;
        sf::Vector2i player_start;
    };
}



#endif //SFML_SOKOBAN_TILEMAP_H
