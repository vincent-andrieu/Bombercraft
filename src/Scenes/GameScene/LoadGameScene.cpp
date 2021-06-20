/*
** EPITECH PROJECT, 2021
** LoadGameScene.cpp
** File description:
** Load state of entities in GameScene from file
*/

#include "GameScene.hpp"
#include "Components/Matrix2D/Matrix2D.hpp"
#include "Game/Factories/Map/MapFactory.hpp"

using namespace Game;

extern std::unique_ptr<Game::Core> core;

void GameScene::setOptions(const Component::OptionComponent &options)
{
    auto &audioSystem = CoreData::systemManager->getSystem<System::AudioSystem>();
    const auto map = localEntities.getEntity("gameMap");

    audioSystem.setVolumeEffects(options.volumeEffects);
    audioSystem.setVolumeMusic(options.volumeMusic);
    MapFactory::updateMapTextures(options.ressourcePack, map);
    Game::CoreData::camera->setFovy((float) options.fov);
}

void GameScene::loadOptions()
{
    Engine::Entity optionEntity = core->globalEntities.getEntity("options");
    auto &options = Game::CoreData::entityManager->getComponent<Component::OptionComponent>(optionEntity);
    const auto my_filename("options");

    try {
        CoreData::entityManager->saveManager.setReadingFile(my_filename);
        CoreData::entityManager->saveManager.readActFile(options.volumeEffects);
        CoreData::entityManager->saveManager.readActFile(options.volumeMusic);
        CoreData::entityManager->saveManager.readActFile(options.ressourcePack);
        CoreData::entityManager->saveManager.readActFile(options.fov);
        CoreData::entityManager->saveManager.readActFile(options.nbPlayers);
        CoreData::entityManager->saveManager.readActFile(options.IARandomProb);
        CoreData::entityManager->saveManager.readActFile(options.smoothMode);
        CoreData::entityManager->saveManager.closeReadingFile(my_filename);
    } catch (const std::filesystem::filesystem_error &my_e) {
        std::cerr << my_e.what() << std::endl;
        return;
    }
    setOptions(options);
}

void GameScene::loadPlayerConfig()
{
    string my_skinPath;
    size_t my_xp;
    Component::PlayerStatus my_status;
    const auto configName_prefix("config");
    std::string my_filename;
    Component::PlayerConfig *config[MAX_PLAYERS] = {&CoreData::entityManager->getComponent<Component::PlayerConfig>(
                                                        core->globalEntities.getEntity(configName_prefix + toString(1))),
        &CoreData::entityManager->getComponent<Component::PlayerConfig>(
            core->globalEntities.getEntity(configName_prefix + toString(2))),
        &CoreData::entityManager->getComponent<Component::PlayerConfig>(
            core->globalEntities.getEntity(configName_prefix + toString(3))),
        &CoreData::entityManager->getComponent<Component::PlayerConfig>(
            core->globalEntities.getEntity(configName_prefix + toString(4)))};

    for (size_t i = 0; i < MAX_PLAYERS; i++) {
        my_skinPath = "";
        my_xp = 0;
        my_status = Component::PlayerStatus::ALIVE;
        my_filename = configName_prefix + toString(i + 1);
        try {
            if (!CoreData::entityManager->saveManager.fileExistsInWD(my_filename)) {
                continue;
            }
            CoreData::entityManager->saveManager.setReadingFile(my_filename);
            CoreData::entityManager->saveManager.readActFile(my_skinPath);
            CoreData::entityManager->saveManager.readActFile(my_xp);
            CoreData::entityManager->saveManager.readActFile(my_status);
            CoreData::entityManager->saveManager.closeReadingFile(my_filename);
        } catch (const std::filesystem::filesystem_error &my_e) {
            std::cerr << my_e.what() << std::endl;
            continue;
        }
        config[i]->setSkinPath(my_skinPath);
        config[i]->setXP(my_xp);
        config[i]->setStatus(my_status);
    }
}

void GameScene::loadGameMap()
{
    std::string my_filename("map");
    Engine::Entity mapEntity = this->localEntities.getEntity("gameMap");
    Component::Matrix2D &map = CoreData::entityManager->getComponent<Component::Matrix2D>(mapEntity);
    const raylib::MyVector2 &mapSize = map.getMapSize();
    const std::shared_ptr<DataMatrix> &dataMatrix = map.getData();
    std::vector<std::vector<GUI::BlockFactory::BlockType>> typeMatrix;
    Engine::Entity optionEntity = core->globalEntities.getEntity("options");
    auto &options = Game::CoreData::entityManager->getComponent<Component::OptionComponent>(optionEntity);
    const raylib::MyVector3 &size = Game::CoreData::settings->getMyVector3("STANDARD_BLOCK_SIZE");

    try {
        if (!CoreData::entityManager->saveManager.fileExistsInWD(my_filename)) {
            return;
        }
        CoreData::entityManager->saveManager.setReadingFile(my_filename);
        CoreData::entityManager->saveManager
            .readActFile<GUI::BlockFactory::BlockType, std::vector<std::vector<GUI::BlockFactory::BlockType>>>(typeMatrix);
        CoreData::entityManager->saveManager.closeReadingFile(my_filename);
    } catch (const std::filesystem::filesystem_error &my_e) {
        std::cerr << my_e.what() << std::endl;
        return;
    }
    if (typeMatrix.empty() || typeMatrix[0].empty())
        return;
    // Apply changes
    for (size_t y = 0; y < mapSize.b; y++) {
        for (size_t x = 0; x < mapSize.a; x++) {
            if (dataMatrix->getCategory({x, y}) != typeMatrix[y][x]) {
                if (dataMatrix->getCategory({x, y}) != GUI::BlockFactory::BlockType::BLOCK_AIR)
                    this->localEntities.removeEntity(dataMatrix->getEntity({x, y})); // remove old block
                if (typeMatrix[y][x] == GUI::BlockFactory::BlockType::BLOCK_AIR) {
                    dataMatrix->save({x, y}, 0, GUI::BlockFactory::BlockType::BLOCK_AIR); // update matrix
                } else if (typeMatrix[y][x] == GUI::BlockFactory::BlockType::BLOCK_BOMB
                    || typeMatrix[y][x] == GUI::BlockFactory::BlockType::BLOCK_BLAST) {
                    dataMatrix->save({x, y}, 0, GUI::BlockFactory::BlockType::BLOCK_AIR); // update matrix
                    // TODO : reload bombs - need character id
                    // const auto bombPosition(Component::Matrix2D::getPositionAbs(x, y);
                    // BombFactory::create(Game::Core::sceneManager->getCurrentScene()->localEntities, bombPosition, character);
                } else {
                    Engine::Entity block = GUI::BlockFactory::create(this->localEntities,
                        {x * size.a, 0, y * size.c},
                        typeMatrix[y][x],
                        mapEntity,
                        options.ressourcePack);                        // create new block
                    dataMatrix->save({x, y}, block, typeMatrix[y][x]); // update matrix
                }
            }
        }
    }
}

void GameScene::loadGame(const std::string &loadName)
{
    if (loadName.empty())
        return;
    try {
        if (!CoreData::entityManager->saveManager.directoryExistsInWD(loadName))
            return;
        CoreData::entityManager->saveManager.setWorkingDirectory(loadName);
    } catch (const std::filesystem::filesystem_error &my_e) {
        std::cerr << my_e.what() << std::endl;
        return;
    }
    this->loadPlayerConfig();
    this->loadGameMap();
    this->loadOptions();
    CoreData::entityManager->saveManager.unsetWorkingDirectory();
}