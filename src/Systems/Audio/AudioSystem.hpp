/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 10/06/2021 AudioSystem.hpp.h
*/

#ifndef AUDIOSYSTEM_HPP
#define AUDIOSYSTEM_HPP

#include "GameEngine.hpp"

namespace System
{
    /**
     * Rules:
     * The Sound component has a isMusic attribute.
     * One music (isMusic == true) can be played at the same time.
     * Several sounds (isMusic == false) can be played at the same time.
     */
    class AudioSystem : public Engine::AbstractSystem {
      public:
        AudioSystem();
        virtual ~AudioSystem() = default;

        bool isPlaying(const std::string &entityName);
        bool isPlaying(const std::string &entityName, Engine::EntityPack &entityPack);

        void play(std::string const &entityName, Engine::EntityPack &entityPack);
        void play(std::string const &entityName);

        void setVolumeEffects(const float &volume);
        void setVolumeMusic(const float &volume);

        void stopAll();
        void stopMusic();
        void update();
    };
} // namespace System

#endif // AUDIOSYSTEM_HPP
