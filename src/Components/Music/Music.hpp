/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 10/06/2021 Music.hpp.h
*/

#ifndef MUSICCOMP_HPP
#define MUSICCOMP_HPP

#include "GameEngine.hpp"
#include "raylib.hpp"

namespace Component
{
    class Music : public Engine::Component<Music> {
      public:
        explicit Music(std::shared_ptr<raylib::Music> music);
        virtual ~Music() = default;

        std::shared_ptr<raylib::Music> sound;
    };
}

#endif // MUSIC_HPP
