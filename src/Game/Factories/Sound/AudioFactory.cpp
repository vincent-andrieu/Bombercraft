/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 10/06/2021 AudioFactory.cpp.cc
*/

#include "Components/Sound/Sound.hpp"
#include "Components/Music/Music.hpp"
#include "AudioFactory.hpp"
#include "Game/CoreData/CoreData.hpp"
#include "raylib.hpp"

using namespace Game;

const AudioConfig AudioFactory::getDefaultConfig()
{
    return AudioConfig{CoreData::settings->getFloat("DEF_SOUND_VOLUME"), CoreData::settings->getFloat("DEF_SOUND_PITCH")};
}

void AudioFactory::create(Engine::EntityPack &entityPack, AudioType type, std::string const &filePath, AudioConfig const &config,
    std::string const &name)
{
    Engine::Entity entity;

    if (name.empty()) {
        entity = entityPack.createAnonymousEntity();
    } else {
        entity = entityPack.createEntity(name);
    }
    if (type == AudioType::SOUND) {
        CoreData::entityManager->addComponent<Component::Sound>(
            entity, std::make_shared<raylib::Sound>(filePath, config.volume, config.pitch));
    } else if (type == AudioType::MUSIC) {
        CoreData::entityManager->addComponent<Component::Music>(
            entity, std::make_shared<raylib::Music>(filePath, config.volume, config.pitch));
    }
}

void AudioFactory::create(Engine::EntityPack &entityPack, AudioType type, std::string const &filePath, std::string const &name)
{
    AudioFactory::create(entityPack, type, filePath, AudioFactory::getDefaultConfig(), name);
}
