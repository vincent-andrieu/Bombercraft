/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Sound
*/

#ifndef SOUND_HPP
#define SOUND_HPP

#include "../../include/include.hpp"

#include "IAudio.hpp"

typedef Sound RSound;

namespace raylib
{
    class Sound : public IAudio
    {
        public :
            Sound(const std::string &path, float volume, float pitch);
            ~Sound();

            void play();
            void stop();
            void resume();
            void pause();

            void setPath(const std::string &path);
            void setVolume(float volume);
            void setPitch(float pitch);

        private :
            std::string _path;
            float _volume;
            float _pitch;
            RSound _sound;
    };
};

#endif // SOUND_HPP