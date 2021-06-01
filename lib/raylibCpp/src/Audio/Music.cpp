/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Music
*/

#include "Music.hpp"

raylib::Music::Music(const std::string &path, float volume, float pitch)
{
    _path = path;
    _volume = volume;
    _pitch = pitch;
    _music = LoadMusicStream(path.data());
}

raylib::Music::~Music()
{
    UnloadMusicStream(_music);
}

void raylib::Music::play()
{
    PlayMusicStream(_music);
}

void raylib::Music::stop()
{
    StopMusicStream(_music);
}

void raylib::Music::resume()
{
    ResumeMusicStream(_music);
}

void raylib::Music::pause()
{
    PauseMusicStream(_music);
}

void raylib::Music::setPath(const std::string &path)
{
    _path = path;
    UnloadMusicStream(_music);
    _music = LoadMusicStream(_path.data());
}

void raylib::Music::setVolume(float volume)
{
    _volume = volume;
    SetMusicVolume(_music, _volume);
}

void raylib::Music::setPitch(float pitch)
{
    _pitch = pitch;
    SetMusicPitch(_music, _pitch);
}