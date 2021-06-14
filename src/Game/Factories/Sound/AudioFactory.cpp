/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 10/06/2021 AudioFactory.cpp.cc
*/

#include "Components/Sound/Sound.hpp"
#include "AudioFactory.hpp"
#include "Game/CoreData/CoreData.hpp"
#include "raylib.hpp"

using namespace Game;

const AudioConfig AudioFactory::getDefaultConfig()
{
    return AudioConfig{
        CoreData::settings->getFloat("STANDARD_SOUND_VOLUME"), CoreData::settings->getFloat("STANDARD_SOUND_PITCH")};
}

void AudioFactory::create(Engine::EntityPack &entityPack,
    AudioType type,
    std::string const &filePath,
    AudioConfig const &config,
    std::string const &name)
{
    Engine::Entity entity;
    bool isMusic = (type == AudioType::MUSIC);

    if (name.empty()) {
        throw std::invalid_argument("AudioFactory::create Invalid entity name");
    } else {
        entity = entityPack.createEntity(name);
    }
    CoreData::entityManager->addComponent<Component::Sound>(
        entity, std::make_shared<raylib::Sound>(filePath, config.volume, config.pitch), isMusic);
}

void AudioFactory::create(Engine::EntityPack &entityPack, AudioType type, std::string const &filePath, std::string const &name)
{
    AudioFactory::create(entityPack, type, filePath, AudioFactory::getDefaultConfig(), name);
}