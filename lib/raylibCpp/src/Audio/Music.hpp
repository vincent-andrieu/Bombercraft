/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Music
*/

#ifndef MUSIC_HPP
#define MUSIC_HPP

#include "../../include/include.hpp"

#include "IAudio.hpp"

typedef Music RMusic;

namespace raylib
{
    class Music : public IAudio
    {
        public :
            Music(const std::string &path, float volume = 100, float pitch = 100);
            ~Music();

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
            RMusic _music;
    };
};

#endif // MUSIC_HPP