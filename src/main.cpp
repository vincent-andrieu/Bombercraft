/*
** EPITECH PROJECT, 2021
** main.cpp
** File description:
** main function
*/

#include <memory>
#include <iostream>
#include "ConfigFile/ConfigFile.hpp"
#include "Game/ProceduralMap/ProceduralMap.hpp"

int main(void)
{
    std::unique_ptr<IConfigFile> map = std::make_unique<ConfigFile>("./ConfigFileTest");

    //std::cout << "yolo ->" << map->getInt("fuck") << std::endl;
    std::cout << "1 == " << map->getInt("LoadInt") << std::endl;
    std::cout << "1.1 == " << map->getFloat("LoadFloat") << std::endl;
    std::cout << "? == " << map->getString("LoadString") << std::endl;
    /*std::unique_ptr<IProceduralMap> map = std::make_unique<ProceduralMap>();
    MapType end;

    map->setMapModel({
        {TileDisponibility::TILE_FORCE_EMPTY, TileDisponibility::TILE_FORCE_EMPTY, TileDisponibility::TILE_FORCE_SOFT, TileDisponibility::TILE_FORCE_SOFT, TileDisponibility::TILE_FORCE_SOFT, TileDisponibility::TILE_FORCE_SOFT, TileDisponibility::TILE_FORCE_SOFT, TileDisponibility::TILE_FORCE_SOFT, TileDisponibility::TILE_FORCE_SOFT, TileDisponibility::TILE_FORCE_SOFT, TileDisponibility::TILE_FORCE_SOFT, TileDisponibility::TILE_FORCE_SOFT, TileDisponibility::TILE_FORCE_SOFT, TileDisponibility::TILE_FORCE_SOFT, TileDisponibility::TILE_FORCE_SOFT, TileDisponibility::TILE_FORCE_EMPTY, TileDisponibility::TILE_FORCE_EMPTY},
        {TileDisponibility::TILE_FORCE_EMPTY, TileDisponibility::TILE_FORCE_HARD, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_FORCE_HARD, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_FORCE_HARD, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_FORCE_HARD, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_FORCE_HARD, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_FORCE_HARD, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_FORCE_HARD, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_FORCE_HARD, TileDisponibility::TILE_FORCE_EMPTY},
        {TileDisponibility::TILE_FORCE_SOFT, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_FORCE_SOFT},
        {TileDisponibility::TILE_FORCE_SOFT, TileDisponibility::TILE_FORCE_HARD, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_FORCE_HARD, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_FORCE_HARD, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_FORCE_HARD, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_FORCE_HARD, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_FORCE_HARD, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_FORCE_HARD, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_FORCE_HARD, TileDisponibility::TILE_FORCE_SOFT},
        {TileDisponibility::TILE_FORCE_SOFT, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_FORCE_SOFT},
        {TileDisponibility::TILE_FORCE_SOFT, TileDisponibility::TILE_FORCE_HARD, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_FORCE_HARD, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_FORCE_HARD, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_FORCE_HARD, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_FORCE_HARD, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_FORCE_HARD, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_FORCE_HARD, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_FORCE_HARD, TileDisponibility::TILE_FORCE_SOFT},
        {TileDisponibility::TILE_FORCE_SOFT, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_FORCE_SOFT},
        {TileDisponibility::TILE_FORCE_SOFT, TileDisponibility::TILE_FORCE_HARD, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_FORCE_HARD, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_FORCE_HARD, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_FORCE_HARD, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_FORCE_HARD, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_FORCE_HARD, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_FORCE_HARD, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_FORCE_HARD, TileDisponibility::TILE_FORCE_SOFT},
        {TileDisponibility::TILE_FORCE_SOFT, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_FORCE_SOFT},
        {TileDisponibility::TILE_FORCE_EMPTY, TileDisponibility::TILE_FORCE_HARD, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_FORCE_HARD, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_FORCE_HARD, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_FORCE_HARD, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_FORCE_HARD, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_FORCE_HARD, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_FORCE_HARD, TileDisponibility::TILE_AVAILABLE, TileDisponibility::TILE_FORCE_HARD, TileDisponibility::TILE_FORCE_EMPTY},
        {TileDisponibility::TILE_FORCE_EMPTY, TileDisponibility::TILE_FORCE_EMPTY, TileDisponibility::TILE_FORCE_SOFT, TileDisponibility::TILE_FORCE_SOFT, TileDisponibility::TILE_FORCE_SOFT, TileDisponibility::TILE_FORCE_SOFT, TileDisponibility::TILE_FORCE_SOFT, TileDisponibility::TILE_FORCE_SOFT, TileDisponibility::TILE_FORCE_SOFT, TileDisponibility::TILE_FORCE_SOFT, TileDisponibility::TILE_FORCE_SOFT, TileDisponibility::TILE_FORCE_SOFT, TileDisponibility::TILE_FORCE_SOFT, TileDisponibility::TILE_FORCE_SOFT, TileDisponibility::TILE_FORCE_SOFT, TileDisponibility::TILE_FORCE_EMPTY, TileDisponibility::TILE_FORCE_EMPTY},
    });
    map->setModelSettings({
        {TileType::TILE_BONUS, 5},
        {TileType::TILE_EMPTY, 30},
        {TileType::TILE_SOFT, 65},
    });
    end = map->getProceduralMap();
    for (auto it_y : end) {
        for (auto it_x : it_y) {
            switch (it_x)
            {
                case TileType::TILE_BONUS: std::cout << '?'; break;
                case TileType::TILE_EMPTY: std::cout << '.'; break;
                case TileType::TILE_HARD: std::cout << 'x'; break;
                case TileType::TILE_SOFT: std::cout << '#'; break;
                case TileType::TILE_DEFAULT: std::cout << '!'; break;
            }
        }
        std::cout << std::endl;
    }*/
    return EXIT_SUCCESS;
}
