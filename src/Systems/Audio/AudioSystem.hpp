/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 10/06/2021 AudioSystem.hpp.h
*/

#ifndef AUDIOSYSTEM_HPP
#define AUDIOSYSTEM_HPP

#include <mutex>
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

        void play(const std::string &entityName, Engine::EntityPack &entityPack);
        void play(const std::string &entityName);

        void setVolume(float volume);

        void stopAll();
        void stopMusic();
        void update();

      private:
        std::mutex _mutex;
    };
} // namespace System

#endif // AUDIOSYSTEM_HPP
