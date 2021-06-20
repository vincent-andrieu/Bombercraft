/*
** EPITECH PROJECT, 2021
** LoadGameScene.cpp
** File description:
** Load state of entities in GameScene from file
*/

#include "GameScene.hpp"
#include "Game/Factories/Map/MapFactory.hpp"

using namespace Game;

extern std::unique_ptr<Game::Core> core;

void GameScene::setOptions(const Component::OptionComponent &options)
{
    auto &audioSystem = CoreData::systemManager->getSystem<System::AudioSystem>();
    const auto map = localEntities.getEntity("gameMap");

    audioSystem.setVolumeEffects(options.volumeEffects);
    audioSystem.setVolumeMusic(options.volumeMusic);
    GUI::MapFactory::updateMapTextures(options.ressourcePack, map);
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

    for (size_t i = 0; i < 4; i++) {
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
    loadPlayerConfig();
    loadOptions();
    CoreData::entityManager->saveManager.unsetWorkingDirectory();
}