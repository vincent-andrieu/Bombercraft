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
        std::vector<std::vector<int>> tab = config->getTabTabInt("MAP_CONFIG");
        std::vector<std::vector<TileDisponibility>> settings;
        std::vector<TileDisponibility> tmp;
        MapType end;

        for (auto &b: tab) {
            tmp.clear();
            std::transform(b.begin(), b.end(), std::back_inserter(tmp),
                [](int n) {  return static_cast<TileDisponibility>(n); 
            });
            settings.push_back(tmp);
        }

        map->setMapModel(settings);
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
