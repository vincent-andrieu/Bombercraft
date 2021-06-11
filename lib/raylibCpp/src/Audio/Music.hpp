/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Music
*/

#ifndef MUSIC_HPP
#define MUSIC_HPP

#include "../../include/object.hpp"

#include "IAudio.hpp"

typedef Music RMusic;

namespace raylib
{
    class Music : public IAudio
    {
        public :
            Music(const std::string &path, const float volume = 100, const float pitch = 1.0f);
            ~Music();

            void play();
            void stop();
            void resume();
            void pause();
            void update();

            void setPath(const std::string &path);
            void setVolume(const float volume);
            void setPitch(const float pitch);

            bool isPlaying() const;

        private :
            std::string _path;
            float _volume;
            float _pitch;
            RMusic _music;
    };
}; // namespace raylib

#endif // MUSIC_HPP