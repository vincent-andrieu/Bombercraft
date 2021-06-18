/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 10/06/2021 AudioFactory.hpp.h
*/

#ifndef AUDIOFACTORY_HPP
#define AUDIOFACTORY_HPP

#include "GameEngine.hpp"

namespace Game
{
    struct AudioConfig {
        float volumeEffects;
        float volumeMusic;
        float pitch;
    };

    enum class AudioType
    {
        MUSIC,
        SOUND
    };

    class AudioFactory {
      public:
        virtual ~AudioFactory() = delete;

        static const AudioConfig getDefaultConfig();

        static void create(Engine::EntityPack &entityPack,
            AudioType type,
            std::string const &filePath,
            AudioConfig const &config,
            std::string const &name);
        static void create(Engine::EntityPack &entityPack, AudioType type, std::string const &filePath, std::string const &name);
    };
} // namespace Game

#endif // AUDIOFACTORY_HPP
