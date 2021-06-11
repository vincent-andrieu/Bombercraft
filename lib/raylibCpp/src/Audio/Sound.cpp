/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Sound
*/

#include "Sound.hpp"

raylib::Sound::Sound(const string &path, const float volume, const float pitch)
{
    this->_path = path;
    this->_sound = LoadSound(path.data());
    this->setVolume(volume);
    this->setPitch(pitch);
}

raylib::Sound::~Sound()
{
    UnloadSound(this->_sound);
}

void raylib::Sound::play()
{
    PlaySound(this->_sound);
}

void raylib::Sound::stop()
{
    StopSound(this->_sound);
}

void raylib::Sound::resume()
{
    ResumeSound(this->_sound);
}

void raylib::Sound::pause()
{
    PauseSound(this->_sound);
}

void raylib::Sound::update()
{
}

void raylib::Sound::setPath(const std::string &path)
{
    this->_path = path;
    UnloadSound(this->_sound);
    this->_sound = LoadSound(this->_path.data());
}

void raylib::Sound::setVolume(const float volume)
{
    this->_volume = volume;
    SetSoundVolume(this->_sound, this->_volume);
}

void raylib::Sound::setPitch(const float pitch)
{
    this->_pitch = pitch;
    SetSoundPitch(this->_sound, this->_pitch);
}

bool raylib::Sound::isPlaying() const
{
    return IsSoundPlaying(this->_sound);
}
