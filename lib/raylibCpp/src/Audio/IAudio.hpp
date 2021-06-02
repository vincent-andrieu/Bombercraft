/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** IAudio
*/

#ifndef IAUDIO_HPP
#define IAUDIO_HPP

#include "../../include/include.hpp"

namespace raylib
{
    class IAudio {
      public:
        virtual ~IAudio(){};

        virtual void play() = 0;
        virtual void stop() = 0;
        virtual void resume() = 0;
        virtual void pause() = 0;

        virtual void setPath(const string &path) = 0;
        virtual void setVolume(const float volume) = 0;
        virtual void setPitch(const float pitch) = 0;
    };
}; // namespace raylib

#endif // IAUDIO_HPP