/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Sound
*/

#include "Sound.hpp"

raylib::Sound::Sound(const string &path, const float volume, const float pitch)
{
    _path = path;
    _volume = volume;
    _pitch = pitch;
    _sound = LoadSound(path.data());
}

raylib::Sound::~Sound()
{
    UnloadSound(_sound);
}

void raylib::Sound::play()
{
    PlaySound(_sound);
}

void raylib::Sound::stop()
{
    StopSound(_sound);
}

void raylib::Sound::resume()
{
    ResumeSound(_sound);
}

void raylib::Sound::pause()
{
    PauseSound(_sound);
}

void raylib::Sound::setPath(const string &path)
{
    _path = path;
    UnloadSound(_sound);
    _sound = LoadSound(_path.data());
}

void raylib::Sound::setVolume(const float volume)
{
    _volume = volume;
    SetSoundVolume(_sound, _volume);
}

void raylib::Sound::setPitch(const float pitch)
{
    _pitch = pitch;
    SetSoundPitch(_sound, _pitch);
}