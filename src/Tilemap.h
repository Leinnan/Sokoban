//
// Created by piotr on 16.11.16.
//

#ifndef SFML_SOKOBAN_TILEMAP_H
#define SFML_SOKOBAN_TILEMAP_H

#define TILES_X 15
#define TILES_Y 15

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
    private:
        void configTile(unsigned int p_x, unsigned int p_y, TileType p_tile_type);
        void generateMap();
        void generateMap(std::string p_file_path);
        std::vector< ar::TileType > tile_types;
        sf::Texture *texture_pointer;
        sf::VertexArray map_graphic;
        unsigned int tile_length = 30;
    };
}



#endif //SFML_SOKOBAN_TILEMAP_H
