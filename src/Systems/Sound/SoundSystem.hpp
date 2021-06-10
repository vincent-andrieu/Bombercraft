/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 10/06/2021 SoundSystem.hpp.h
*/

#ifndef SOUNDSYSTEM_HPP
#define SOUNDSYSTEM_HPP

#include "GameEngine.hpp"

namespace System
{
    class SoundSystem : public Engine::AbstractSystem {
      public:
        SoundSystem();
        virtual ~SoundSystem() = default;

        void play(std::string const& entityName);
        void stopAll();
    };
}

#endif // SOUNDSYSTEM_HPP
