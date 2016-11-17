//
// Created by piotr on 16.11.16.
//

#include "Tilemap.h"

namespace ar{
    Tilemap::Tilemap() :
        map_graphic(sf::Quads, TILES_X*TILES_Y*4),
        player_start(6,3)
    {
        generateTileTypes();
        generateMap();
    }
    Tilemap::Tilemap(std::string p_file_path) :
        map_graphic(sf::Quads, TILES_X*TILES_Y*4),
        player_start(6,3)
    {
        generateTileTypes();
        generateMap(p_file_path);
    }
    void Tilemap::generateTileTypes() {
        TileType player_pos;
        player_pos.tex_index = sf::Vector2i(0,1);
        player_pos.symbol = PLAYER_SYMBOL;
        TileType balls_tile;
        balls_tile.tex_index = sf::Vector2i(0,1);
        balls_tile.symbol = BALL_SYMBOL;
        TileType target_tile;
        target_tile.tex_index = sf::Vector2i(2,1);
        target_tile.symbol = TARGET_SYMBOL;
        TileType gleba;
        gleba.tex_index = sf::Vector2i(0,0);
        gleba.symbol = '.';
        TileType wall;
        wall.tex_index = sf::Vector2i(1,1);
        wall.symbol = '#';
        wall.is_wall = true;
        TileType dirt;
        dirt.tex_index = sf::Vector2i(0,1);
        dirt.symbol = '*';
        TileType ice;
        ice.tex_index = sf::Vector2i(1,0);
        ice.symbol = 'i';

        tile_types.push_back(player_pos);
        tile_types.push_back(balls_tile);
        tile_types.push_back(target_tile);
        tile_types.push_back(gleba);
        tile_types.push_back(wall);
        tile_types.push_back(dirt);
        tile_types.push_back(ice);
    }
    void Tilemap::generateMap() {
        //configTile(0,0,tile_types[0]);
        configTile(1,0,tile_types[0]);
        configTile(0,1,tile_types[0]);
        configTile(2,0,tile_types[1]);
        configTile(1,1,tile_types[1]);
        configTile(2,1,tile_types[2]);
        configTile(2,3,tile_types[2]);
        configTile(3,3,tile_types[1]);
    }

    void Tilemap::generateMap(std::string p_file_path){
        std::ifstream map_file(p_file_path.c_str());
        std::string one_line;
        char tile_symbol;
        unsigned int index_x = 0, index_y = 0;
        std::clog << "START\n";
        if(!map_file.good()){
            std::cerr << "Map file error\n";
            return;
        }

        std::clog << "File open\n";
        while(std::getline(map_file, one_line)) {

            if(index_y >= TILES_Y)
                break;

            std::clog << "Next line\n";

            for(index_x = 0; index_x < TILES_X;index_x++){
                tile_symbol = one_line[index_x];

                for(auto const& single_tile: tile_types) {

                    if(single_tile.symbol == tile_symbol){
                        this->configTile(index_x,index_y,single_tile);
                        if(single_tile.symbol == PLAYER_SYMBOL){
                            this->player_start = sf::Vector2i(index_x, index_y);
                        }
                        if(single_tile.symbol == BALL_SYMBOL){
                            boxes_pos.push_back(sf::Vector2i(index_x, index_y));
                        }
                        if(single_tile.symbol == TARGET_SYMBOL){
                            targets_pos.push_back(sf::Vector2i(index_x, index_y));
                        }
                    }
                }

            }
            index_y++;
        }

    }
    bool Tilemap::isTilePassable(unsigned int p_x, unsigned int p_y) {
        unsigned int tile_index = 4*(p_y * TILES_X + p_x)+1;
        float dist_x, dist_y;
        for (auto &&tile : tile_types) {
            dist_x = tile.tex_index.x*tile_length - map_graphic[tile_index].texCoords.x;
            dist_y = tile.tex_index.y*tile_length - map_graphic[tile_index].texCoords.y;
            dist_x = dist_x > 0 ? dist_x : dist_x * -1;
            dist_y = dist_y > 0 ? dist_y : dist_y * -1;
            if(dist_x < 0.1f && dist_y  < 0.1f){
                return !tile.is_wall;
            }
        }

        return false;

    }
    bool Tilemap::isTilePassable(sf::Vector2i p_tile_index) {
        unsigned int tile_index = 4*(p_tile_index.y * TILES_X + p_tile_index.x)+1;
        float dist_x, dist_y;
        for (auto &&tile : tile_types) {
            dist_x = tile.tex_index.x*tile_length - map_graphic[tile_index].texCoords.x;
            dist_y = tile.tex_index.y*tile_length - map_graphic[tile_index].texCoords.y;
            dist_x = dist_x > 0 ? dist_x : dist_x * -1;
            dist_y = dist_y > 0 ? dist_y : dist_y * -1;
            if(dist_x < 0.1f && dist_y  < 0.1f){
                return !tile.is_wall;
            }
        }

        return false;

    }

    void Tilemap::configTile(unsigned int p_x, unsigned int p_y, TileType p_tile_type){
        unsigned int start_index = 4*(p_y * TILES_X + p_x);
        map_graphic[start_index+1].position = sf::Vector2f(p_x * tile_length, p_y * tile_length);
        map_graphic[start_index+2].position = sf::Vector2f(p_x * tile_length, p_y * tile_length+tile_length);
        map_graphic[start_index].position = sf::Vector2f(p_x * tile_length+tile_length, p_y * tile_length);
        map_graphic[start_index+3].position = sf::Vector2f(p_x * tile_length+tile_length, p_y * tile_length+tile_length);

        std::clog << TILES_X << "\t START INDEX: " << start_index << "\n";
        std::clog << map_graphic[start_index+1].position.x << "," << map_graphic[start_index+1].position.y << "\t"
                << map_graphic[start_index+2].position.x << "," << map_graphic[start_index+2].position.y << "\t"
                << map_graphic[start_index].position.x << "," << map_graphic[start_index].position.y << "\t"
                << map_graphic[start_index+3].position.x << "," << map_graphic[start_index+3].position.y << "\t\n\n";
        map_graphic[start_index+1].texCoords = sf::Vector2f(
                p_tile_type.tex_index.x*tile_length,
                p_tile_type.tex_index.y*tile_length);
        map_graphic[start_index+2].texCoords = sf::Vector2f(
                p_tile_type.tex_index.x*tile_length+tile_length,
                p_tile_type.tex_index.y*tile_length);
        map_graphic[start_index].texCoords = sf::Vector2f(
                p_tile_type.tex_index.x*tile_length,
                p_tile_type.tex_index.y*tile_length+tile_length);
        map_graphic[start_index+3].texCoords = sf::Vector2f(
                p_tile_type.tex_index.x*tile_length+tile_length,
                p_tile_type.tex_index.y*tile_length+tile_length);
    }

    void Tilemap::draw(sf::RenderWindow *p_window_pointer) {
        p_window_pointer->draw(map_graphic,  texture_pointer);
    }
}