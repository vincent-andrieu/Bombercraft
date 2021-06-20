/*
** EPITECH PROJECT, 2021
** Map
** File description:
** MapFactory.cpp
*/

#include "MapFactory.hpp"

using namespace Game;

void MapFactory::create(
    Engine::EntityPack &entityPack, const std::string &ressourcePackRoot, const std::string &name, unsigned int seed)
{
    Engine::Entity tmpEntityId = 0;
    GUI::BlockFactory::BlockType tmpBlockType = GUI::BlockFactory::BlockType::BLOCK_SOFT;
    std::pair<size_t, size_t> sizeDest;
    GameModule::MapType map = MapFactory::getProceduralMap(sizeDest);
    const raylib::MyVector3 &size = CoreData::settings->getMyVector3("STANDARD_BLOCK_SIZE");
    const Engine::Entity &entity = (name.size()) ? entityPack.createEntity(name) : entityPack.createAnonymousEntity();

    CoreData::entityManager->addComponent<Component::Matrix2D>(entity, sizeDest);
    const Component::Matrix2D &matrix = CoreData::entityManager->getComponent<Component::Matrix2D>(entity);
    if (CoreData::settings->isSetInFile("SEED") && seed == 0) {
        seed = (unsigned int) CoreData::settings->getInt("SEED");
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
                entityPack, {x * size.a, -1 * size.b, y * size.c}, GUI::BlockFactory::BlockType::BLOCK_FLOOR, ressourcePackRoot);
        }
    }
}

GameModule::MapType MapFactory::getProceduralMap(std::pair<size_t, size_t> &sizeDest)
{
    GameModule::MapType endMap;
    GameModule::ProceduralMap map;
    std::vector<std::vector<int>> tab = CoreData::settings->getTabTabInt("MAP_CONFIG");
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
        {TileType::TILE_BONUS, CoreData::settings->getInt("BONUS_POURCENT")},
        {TileType::TILE_EMPTY, CoreData::settings->getInt("EMPTY_POURCENT")},
        {TileType::TILE_SOFT, CoreData::settings->getInt("SOFT__POURCENT")},
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
void MapFactory::updateMapTextures(const std::string &resourcePackRoot, Engine::Entity mapEntity)
{
    const raylib::MyVector3 size = CoreData::settings->getMyVector3("STANDARD_BLOCK_SIZE");
    auto &matrix = CoreData::entityManager->getComponent<Component::Matrix2D>(mapEntity);
    const raylib::MyVector2 &mapSize = matrix.getMapSize();
    const std::shared_ptr<DataMatrix> &dataMatrix = matrix.getData();

    // Update soft blocks texture
    for (size_t y = 0; y < mapSize.b; y++) {
        for (size_t x = 0; x < mapSize.a; x++) {
            if (dataMatrix->getCategory({x, y}) == GUI::BlockFactory::BlockType::BLOCK_SOFT) {
                std::string const &path =
                    GUI::BlockFactory::getTexturePath(GUI::BlockFactory::BlockType::BLOCK_SOFT, resourcePackRoot);
                auto &render = CoreData::entityManager->getComponent<Component::Render3D>(dataMatrix->getEntity({x, y}));
                static_cast<raylib::IModel *>(render.modele.get())->setTexture(path);
            }
        }
    }
    // Update Floor blocks Texture
    const std::string path = GUI::BlockFactory::getTexturePath(GUI::BlockFactory::BlockType::BLOCK_FLOOR, resourcePackRoot);
    CoreData::entityManager->foreachComponent<Engine::Position>([path, size](Engine::Position const &position) {
        if (position.y == (size.b * -1)) { // IS A TILE BLOCK
            Engine::Entity entity = CoreData::entityManager->getOwner<Engine::Position>(position);
            if (CoreData::entityManager->hasComponent<Component::Render3D>(entity)) {
                auto &render = CoreData::entityManager->getComponent<Component::Render3D>(entity);
                static_cast<raylib::IModel *>(render.modele.get())->setTexture(path);
            }
        }
    });
}
