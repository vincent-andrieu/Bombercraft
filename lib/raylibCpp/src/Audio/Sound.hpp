/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Sound
*/

#ifndef SOUND_HPP
#define SOUND_HPP

#include "../../include/object.hpp"

#include "IAudio.hpp"

typedef Sound RSound;

namespace raylib
{
    class Sound : public IAudio
    {
        public:
            Sound(const std::string &path, const float volume = 1.0, const float pitch = 1.0);
            ~Sound();

            void play();
            void stop();
            void resume();
            void pause();
            void update();

            bool isPlaying() const;

            void setPath(const std::string &path);
            void setVolume(const float volume);
            void setPitch(const float pitch);

        private :
            std::string _path;
            float _volume;
            float _pitch;
            RSound _sound;
    };
}; // namespace raylib

#endif // SOUND_HPP