/*
** EPITECH PROJECT, 2021
** Map
** File description:
** MapFactory.cpp
*/

#include "MapFactory.hpp"

using namespace GUI;

void MapFactory::create(
    Engine::EntityPack &entityPack, const std::string &ressourcePackRoot, const std::string &name, unsigned int seed)
{
    Engine::Entity tmpEntityId = 0;
    GUI::BlockFactory::BlockType tmpBlockType = GUI::BlockFactory::BlockType::BLOCK_SOFT;
    std::pair<size_t, size_t> sizeDest;
    GameModule::MapType map = MapFactory::getProceduralMap(sizeDest);
    const raylib::MyVector3 &size = Game::CoreData::settings->getMyVector3("STANDARD_BLOCK_SIZE");
    const Engine::Entity &entity = (name.size()) ? entityPack.createEntity(name) : entityPack.createAnonymousEntity();

    Game::CoreData::entityManager->addComponent<Component::Matrix2D>(entity, sizeDest);
    const Component::Matrix2D &matrix = Game::CoreData::entityManager->getComponent<Component::Matrix2D>(entity);
    if (Game::CoreData::settings->isSetInFile("SEED") && seed == 0) {
        seed = (unsigned int) Game::CoreData::settings->getInt("SEED");
        std::srand((seed) ? seed : (unsigned int) std::time(nullptr));
    } else
        std::srand((seed) ? seed : (unsigned int) std::time(nullptr));
    std::cout << "\t SEED = " << seed << std::endl;
    for (size_t y = 0; y < map.size(); y++) {
        for (size_t x = 0; x < map[y].size(); x++) {
            if (map[y][x] != GameModule::TileType::TILE_EMPTY) {
                tmpBlockType = MapFactory::blockTypeSinceTile(map[y][x]);
                tmpEntityId =
                    GUI::BlockFactory::create(entityPack, {x * size.a, 0 * size.b, y * size.c}, tmpBlockType, ressourcePackRoot);
                matrix.getData()->save({x, y}, tmpEntityId, tmpBlockType);
            } else {
                matrix.getData()->save({x, y}, tmpEntityId, GUI::BlockFactory::BlockType::BLOCK_AIR);
            }
            tmpEntityId = GUI::BlockFactory::create(
                entityPack, {x * size.a, -1 * size.b, y * size.c}, BlockFactory::BlockType::BLOCK_FLOOR, ressourcePackRoot);
        }
    }
}

GameModule::MapType MapFactory::getProceduralMap(std::pair<size_t, size_t> &sizeDest)
{
    GameModule::MapType endMap;
    GameModule::ProceduralMap map;
    std::vector<std::vector<int>> tab = Game::CoreData::settings->getTabTabInt("MAP_CONFIG");
    std::vector<std::vector<TileDisponibility>> settings;
    std::vector<TileDisponibility> tmp;
    MapType end;

    for (auto &b : tab) {
        tmp.clear();
        std::transform(b.begin(), b.end(), std::back_inserter(tmp), [](int n) {
            return static_cast<TileDisponibility>(n);
        });
        settings.push_back(tmp);
    }
    map.setMapModel(settings);
    map.setModelSettings({
        {TileType::TILE_BONUS, Game::CoreData::settings->getInt("BONUS_POURCENT")},
        {TileType::TILE_EMPTY, Game::CoreData::settings->getInt("EMPTY_POURCENT")},
        {TileType::TILE_SOFT, Game::CoreData::settings->getInt("SOFT__POURCENT")},
    });
    endMap = map.getProceduralMap();
    sizeDest = map.getSize();
    return endMap;
}

GUI::BlockFactory::BlockType MapFactory::blockTypeSinceTile(GameModule::TileType tile)
{
    switch (tile) {
        case GameModule::TileType::TILE_HARD: return GUI::BlockFactory::BlockType::BLOCK_HARD; break;
        case GameModule::TileType::TILE_SOFT: return GUI::BlockFactory::BlockType::BLOCK_SOFT; break;
        case GameModule::TileType::TILE_EMPTY: return GUI::BlockFactory::BlockType::BLOCK_FLOOR; break;
        case GameModule::TileType::TILE_BONUS: return GUI::BlockFactory::BlockType::BLOCK_BONUS_SOFT; break;
        case GameModule::TileType::TILE_DEFAULT: return GUI::BlockFactory::BlockType::BLOCK_FLOOR; break;
        case GameModule::TileType::TILE_EXPLOSION: return GUI::BlockFactory::BlockType::BLOCK_BLAST; break;
        default: return GUI::BlockFactory::BlockType::BLOCK_FLOOR; break;
    }
}