/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 10/06/2021 MusicSystem.hpp.h
*/

#ifndef MUSICSYSTEM_HPP
#define MUSICSYSTEM_HPP

#include "GameEngine.hpp"

namespace System
{
    class MusicSystem : public Engine::AbstractSystem {
      public:
        MusicSystem();
        virtual ~MusicSystem() = default;

        void play(std::string const& entityName);
        void stopAll();
    };
}

#endif // MUSICSYSTEM_HPP
