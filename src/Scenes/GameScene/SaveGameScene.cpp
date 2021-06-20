/*
** EPITECH PROJECT, 2021
** SaveGameScene.cpp
** File description:
** Save state of entities in GameScene to save
*/

#include "GameScene.hpp"
#include "Components/Matrix2D/Matrix2D.hpp"

using namespace Game;

extern std::unique_ptr<Game::Core> core;

void GameScene::saveOptions()
{
    Engine::Entity optionEntity = core->globalEntities.getEntity("options");
    auto &options = Game::CoreData::entityManager->getComponent<Component::OptionComponent>(optionEntity);
    const auto my_filename("options");

    try {
        if (!CoreData::entityManager->saveManager.fileExistsInWD(my_filename))
            CoreData::entityManager->saveManager.createFile(my_filename);
        CoreData::entityManager->saveManager.setWritingFile(my_filename);
        CoreData::entityManager->saveManager.writeActFile(options.volumeEffects);
        CoreData::entityManager->saveManager.writeActFile(options.volumeMusic);
        CoreData::entityManager->saveManager.writeActFile(options.ressourcePack);
        CoreData::entityManager->saveManager.writeActFile(options.fov);
        CoreData::entityManager->saveManager.writeActFile(options.nbPlayers);
        CoreData::entityManager->saveManager.writeActFile(options.IARandomProb);
        CoreData::entityManager->saveManager.writeActFile(options.smoothMode);
        CoreData::entityManager->saveManager.closeWritingFile(my_filename);
    } catch (const std::filesystem::filesystem_error &my_e) {
        std::cerr << my_e.what() << std::endl;
    }
}

void GameScene::savePlayerConfig()
{
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
        my_filename = configName_prefix + toString(i + 1);
        try {
            if (!CoreData::entityManager->saveManager.fileExistsInWD(my_filename))
                CoreData::entityManager->saveManager.createFile(my_filename);
            CoreData::entityManager->saveManager.setWritingFile(my_filename);
            CoreData::entityManager->saveManager.writeActFile(config[i]->getSkinPath());
            CoreData::entityManager->saveManager.writeActFile(config[i]->getXP());
            CoreData::entityManager->saveManager.writeActFile(config[i]->getStatus());
            CoreData::entityManager->saveManager.closeWritingFile(my_filename);
        } catch (const std::filesystem::filesystem_error &my_e) {
            std::cerr << my_e.what() << std::endl;
        }
    }
}

void GameScene::saveGameMap()
{
    std::string my_filename("map");
    Engine::Entity mapEntity = this->localEntities.getEntity("gameMap");
    Component::Matrix2D &map = CoreData::entityManager->getComponent<Component::Matrix2D>(mapEntity);
    const raylib::MyVector2 &mapSize = map.getMapSize();
    const std::shared_ptr<DataMatrix> &dataMatrix = map.getData();

    if (!CoreData::entityManager->saveManager.fileExistsInWD(my_filename))
        CoreData::entityManager->saveManager.createFile(my_filename);
    CoreData::entityManager->saveManager.setWritingFile(my_filename);
    // Read type matrix
    std::vector<std::vector<GUI::BlockFactory::BlockType>> typeMatrix;
    typeMatrix.reserve(mapSize.b);
    for (size_t y = 0; y < mapSize.b; y++) {
        typeMatrix.push_back({});
        for (size_t x = 0; x < mapSize.a; x++) {
            GUI::BlockFactory::BlockType type = dataMatrix->getCategory({x, y});
            typeMatrix[y].push_back(type);
        }
    }
    // Save
    CoreData::entityManager->saveManager
        .writeActFile<GUI::BlockFactory::BlockType, std::vector<std::vector<GUI::BlockFactory::BlockType>>>(typeMatrix);
    CoreData::entityManager->saveManager.closeWritingFile(my_filename);
}

void GameScene::saveGame(const std::string &saveName)
{
    if (saveName.empty())
        return;
    try {
        if (!CoreData::entityManager->saveManager.directoryExistsInWD(saveName))
            CoreData::entityManager->saveManager.createDirectory(saveName);
        CoreData::entityManager->saveManager.setWorkingDirectory(saveName);
    } catch (const std::filesystem::filesystem_error &my_e) {
        Engine::SaveManager::printException(my_e);
        return;
    }
    try {
        std::filesystem::copy(Game::CoreData::settings->getString("GAME_SCREENSHOT"),
            CoreData::entityManager->saveManager.getWorkingDirectory(),
            std::filesystem::copy_options::update_existing);
    } catch (const std::filesystem::filesystem_error &my_e) {
        Engine::SaveManager::printException(my_e);
    }
    this->saveOptions();
    this->savePlayerConfig();
    this->saveGameMap();
    CoreData::entityManager->saveManager.unsetWorkingDirectory();
}