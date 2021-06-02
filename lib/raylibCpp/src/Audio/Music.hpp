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
    class Music : public IAudio {
      public:
        Music(const string &path, const float volume = 100, const float pitch = 100);
        ~Music();

        void play();
        void stop();
        void resume();
        void pause();

        void setPath(const string &path);
        void setVolume(const float volume);
        void setPitch(const float pitch);

      private:
        string _path;
        float _volume;
        float _pitch;
        RMusic _music;
    };
}; // namespace raylib

#endif // MUSIC_HPP