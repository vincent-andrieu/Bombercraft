/*
** EPITECH PROJECT, 2021
** Map
** File description:
** MapFactory.cpp
*/

#include "MapFactory.hpp"

using namespace GUI;

void MapFactory::create(Engine::EntityPack &entityPack, const std::string &name, unsigned int seed)
{
    Engine::Entity tmpEntityId;
    GUI::BlockFactory::BlockType tmpBlockType = GUI::BlockFactory::BlockType::BLOCK_SOFT;
    std::pair<size_t, size_t> sizeDest;
    GameModule::MapType map = MapFactory::getProceduralMap(seed, sizeDest);
    const raylib::MyVector3 &size = Game::CoreData::settings->getMyVector3("STANDARD_BLOCK_SIZE");
    const Engine::Entity &entity = (name.size()) ? entityPack.createEntity(name) : entityPack.createAnonymousEntity();

    Game::CoreData::entityManager->addComponent<Component::Matrix2D>(entity, sizeDest);
    const Component::Matrix2D &matrix = Game::CoreData::entityManager->getComponent<Component::Matrix2D>(entity);
    std::srand((seed) ? seed : (unsigned int) std::time(nullptr));
    for (size_t y = 0; y < map.size(); y++) {
        for (size_t x = 0; x < map[y].size(); x++) {
            if (map[y][x] != GameModule::TileType::TILE_EMPTY) {
                tmpBlockType = MapFactory::blockTypeSinceTile(map[y][x]);
                tmpEntityId = GUI::BlockFactory::create(entityPack, {x * size.a, y * size.b, 0 * size.c}, tmpBlockType, "Asset/Texture/Nether/");
                matrix.getData()->save({x, y}, tmpEntityId, tmpBlockType);
            }
            tmpEntityId = GUI::BlockFactory::create(
                entityPack, {x * size.a, y * size.b, -1 * size.c}, BlockFactory::BlockType::BLOCK_FLOOR, "Asset/Texture/Nether/");
            matrix.getData()->save({x, y}, tmpEntityId, tmpBlockType);
        }
    }
}

GameModule::MapType MapFactory::getProceduralMap(unsigned int seed, std::pair<size_t, size_t> &sizeDest)
{
    GameModule::MapType endMap;
    GameModule::ProceduralMap map(seed);
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

GUI::BlockFactory::BlockType MapFactory::randomBonus()
{
    int value = std::rand() % 101;
    int total = 0;
    std::vector<int> prob;
    std::vector<GUI::BlockFactory::BlockType> tab = {
        GUI::BlockFactory::BlockType::BLOCK_BONUS_BOOMUP,
        GUI::BlockFactory::BlockType::BLOCK_BONUS_FIREUP,
        GUI::BlockFactory::BlockType::BLOCK_BONUS_SPEEDUP,
        GUI::BlockFactory::BlockType::BLOCK_BONUS_WALLPASS,
    };

    if (Game::CoreData::settings->isSetInFile("RANDOM_BONUS")) {
        for (size_t i = 0; i < 4; i++)
            prob.push_back(25);
    } else {
        prob = Game::CoreData::settings->getTabInt("RANDOM_BONUS");
    }
    if (prob.size() != 4)
        throw std::invalid_argument("Invalide bonus array of proba");
    for (size_t i = 0; i < 4; i++)
        total += prob[i];
    if (total != 100)
        throw std::invalid_argument("Invalide bonus array of proba");
    total = 0;
    for (size_t i = 0; i < 4; i++) {
        total += prob[i];
        if (value <= total)
            return tab[i];
    }
    return GUI::BlockFactory::BlockType::BLOCK_BONUS_BOOMUP;
}