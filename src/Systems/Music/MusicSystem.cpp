/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 10/06/2021 MusicSystem.cpp.cc
*/

#include "MusicSystem.hpp"
#include "Game/CoreData/CoreData.hpp"
#include "Components/Music/Music.hpp"

System::MusicSystem::MusicSystem() : AbstractSystem(*Game::CoreData::entityManager)
{
    this->setRequirements<Component::Music>();
}

void System::MusicSystem::play(const string &entityName)
{
    auto scene = Game::CoreData::sceneManager->getCurrentScene();
    if (scene == nullptr) {
        return;
    }
    Engine::EntityPack &scenePack = scene->localEntities;
    try {
        Engine::Entity musicEntity = scenePack.getEntity(entityName);

        if (_entityManager.hasComponent<Component::Music>(musicEntity) == false) {
            std::cerr << "Warning: SoundSystem::update entity " << entityName << " does not have a Sound component." << std::endl;
        } else {
            auto sound = _entityManager.getComponent<Component::Music>(musicEntity);

            this->stopAll();
            sound.sound->play();
        }
    } catch (std::invalid_argument const& e) {
        std::cerr << "Warning: SoundSystem::update entity " << entityName << " not found." << std::endl;
    }
}

void System::MusicSystem::stopAll()
{
    for (Engine::Entity entity : this->getManagedEntities()) {
        auto musicComponent = _entityManager.getComponent<Component::Music>(entity);

        if (musicComponent.sound->isPlaying()) {
            musicComponent.sound->stop();
        }
    }
}
