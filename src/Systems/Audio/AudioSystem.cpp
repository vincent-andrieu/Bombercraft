/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 10/06/2021 AudioSystem.cpp.cc
*/

#include "AudioSystem.hpp"
#include "Game/CoreData/CoreData.hpp"
#include "Components/Sound/Sound.hpp"
#include "Game/Core/Core.hpp"

extern std::unique_ptr<Game::Core> core;

using namespace System;

AudioSystem::AudioSystem() : AbstractSystem(*Game::CoreData::entityManager)
{
    this->setRequirements<Component::Sound>();
}

bool AudioSystem::isPlaying(const std::string &entityName)
{
    return this->isPlaying(entityName, core->globalEntities);
}

bool AudioSystem::isPlaying(const std::string &entityName, Engine::EntityPack &scenePack)
{
    auto scene = Game::CoreData::sceneManager->getCurrentScene();
    if (scene == nullptr) {
        return false;
    }
    try {
        Engine::Entity soundEntity = scenePack.getEntity(entityName);

        if (_entityManager.hasComponent<Component::Sound>(soundEntity) == false) {
            std::cerr << "Warning: AudioSystem::isPlaying entity " << entityName << " does not have a Sound component."
                      << std::endl;
        } else {
            auto sound = _entityManager.getComponent<Component::Sound>(soundEntity);

            return sound.audio->isPlaying();
        }
    } catch (UNUSED std::invalid_argument const &e) {
        std::cerr << "Warning: AudioSystem::update entity " << entityName << " not found." << std::endl;
    }
    return false;
}

void AudioSystem::play(const std::string &entityName)
{
    this->play(entityName, core->globalEntities);
}

void AudioSystem::play(std::string const &entityName, Engine::EntityPack &scenePack)
{
    auto scene = Game::CoreData::sceneManager->getCurrentScene();
    if (scene == nullptr) {
        return;
    }
    try {
        Engine::Entity soundEntity = scenePack.getEntity(entityName);

        if (_entityManager.hasComponent<Component::Sound>(soundEntity) == false) {
            std::cerr << "Warning: AudioSystem::update entity " << entityName << " does not have a Sound component." << std::endl;
        } else {
            auto sound = _entityManager.getComponent<Component::Sound>(soundEntity);

            if (sound.isMusic) {
                this->stopMusic();
            }
            sound.audio->play();
        }
    } catch (UNUSED std::invalid_argument const &e) {
        std::cerr << "Warning: AudioSystem::update entity " << entityName << " not found." << std::endl;
    }
}

void AudioSystem::stopAll()
{
    for (Engine::Entity entity : this->getManagedEntities()) {
        auto soundComponent = _entityManager.getComponent<Component::Sound>(entity);

        if (soundComponent.audio->isPlaying()) {
            soundComponent.audio->stop();
        }
    }
}

void AudioSystem::stopMusic()
{
    for (Engine::Entity entity : this->getManagedEntities()) {
        auto musicComponent = _entityManager.getComponent<Component::Sound>(entity);

        if (musicComponent.isMusic && musicComponent.audio->isPlaying()) {
            musicComponent.audio->stop();
        }
    }
}

void AudioSystem::setVolumeEffects(const float &volume)
{
    for (const Engine::Entity &entity : this->getManagedEntities()) {
        auto &component = _entityManager.getComponent<Component::Sound>(entity);

        if (!component.isMusic)
            component.audio->setVolume(volume);
    }
}

void AudioSystem::setVolumeMusic(const float &volume)
{
    for (const Engine::Entity &entity : this->getManagedEntities()) {
        auto &component = _entityManager.getComponent<Component::Sound>(entity);

        if (component.isMusic)
            component.audio->setVolume(volume);
    }
}

void AudioSystem::update()
{
    for (Engine::Entity entity : this->getManagedEntities()) {
        auto soundComponent = _entityManager.getComponent<Component::Sound>(entity);

        if (soundComponent.audio->isPlaying()) {
            soundComponent.audio->update();
        }
    }
}
