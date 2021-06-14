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

        void play(std::string const &entityName);

        void setVolume(float volume);

        void stopAll();
        void stopMusic();
    };
} // namespace System

#endif // AUDIOSYSTEM_HPP
