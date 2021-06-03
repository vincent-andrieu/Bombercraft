/*
** EPITECH PROJECT, 2021
** main.cpp
** File description:
** main function
*/

#include <memory>
#include <iostream>
#include "ConfigFile/ConfigFile.hpp"
#include "Exceptions/Exceptions.hpp"
#include "Game/ProceduralMap/ProceduralMap.hpp"

int main(void)
{
    try {
        std::unique_ptr<IConfigFile> config = std::make_unique<ConfigFile>("bomberman.config");
        std::unique_ptr<IProceduralMap> map = std::make_unique<ProceduralMap>();
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
            {TileType::TILE_BONUS, config->getInt("BONUS_POURCENT")},
            {TileType::TILE_EMPTY, config->getInt("EMPTY_POURCENT")},
            {TileType::TILE_SOFT, config->getInt("SOFT__POURCENT")},
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
        }
    } catch (const ParserExceptions &e) {
        std::cout << e.what() << std::endl;
        return EXIT_FAILURE;        
    }
    return EXIT_SUCCESS;
}
