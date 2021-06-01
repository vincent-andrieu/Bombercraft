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
    class IAudio
    {
        public :
            virtual ~IAudio() {};

            virtual void play() = 0;
            virtual void stop() = 0;
            virtual void resume() = 0;
            virtual void pause() = 0;

            virtual void setPath(const std::string &path) = 0;
            virtual void setVolume(float volume) = 0;
            virtual void setPitch(float pitch) = 0;
    };
};

#endif // IAUDIO_HPP