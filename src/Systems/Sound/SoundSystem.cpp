/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 10/06/2021 SoundSystem.cpp.cc
*/

#include "SoundSystem.hpp"
#include "Game/CoreData/CoreData.hpp"
#include "Components/Sound/Sound.hpp"

using namespace System;

SoundSystem::SoundSystem() : AbstractSystem(*Game::CoreData::entityManager)
{
    this->setRequirements<Component::Sound>();
}

void SoundSystem::play(std::string const& entityName)
{
    auto scene = Game::CoreData::sceneManager->getCurrentScene();
    if (scene == nullptr) {
        return;
    }
    Engine::EntityPack &scenePack = scene->localEntities;
    try {
        Engine::Entity soundEntity = scenePack.getEntity(entityName);

        if (_entityManager.hasComponent<Component::Sound>(soundEntity) == false) {
            std::cerr << "Warning: SoundSystem::update entity " << entityName << " does not have a Sound component." << std::endl;
        } else {
            auto sound = _entityManager.getComponent<Component::Sound>(soundEntity);

            sound.sound->play();
        }
    } catch (std::invalid_argument const& e) {
        std::cerr << "Warning: SoundSystem::update entity " << entityName << " not found." << std::endl;
    }
}

void SoundSystem::stopAll()
{
    for (Engine::Entity entity : this->getManagedEntities()) {
        auto soundComponent = _entityManager.getComponent<Component::Sound>(entity);

        if (soundComponent.sound->isPlaying()) {
            soundComponent.sound->stop();
        }
    }
}
