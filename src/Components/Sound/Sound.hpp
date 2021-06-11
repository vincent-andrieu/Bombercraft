/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 10/06/2021 SoundComponent.hpp.h
*/

#ifndef SOUNDCOMPONENT_HPP
#define SOUNDCOMPONENT_HPP

#include "GameEngine.hpp"
#include "raylib.hpp"
#include <memory>

namespace Component
{
    class Sound : public Engine::Component<Sound> {
      public:
        explicit Sound(std::shared_ptr<raylib::Sound> sound, bool isMusic);
        virtual ~Sound() = default;

        std::shared_ptr<raylib::Sound> sound;
        bool isMusic;
    };
}

#endif // SOUND_HPP
