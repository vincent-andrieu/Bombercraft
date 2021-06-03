/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Music
*/

#include "Music.hpp"

raylib::Music::Music(const string &path, const float volume, const float pitch)
{
    this->_path = path;
    this->_volume = volume;
    this->_pitch = pitch;
    this->_music = LoadMusicStream(path.data());
}

raylib::Music::~Music()
{
    UnloadMusicStream(this->_music);
}

void raylib::Music::play()
{
    PlayMusicStream(this->_music);
}

void raylib::Music::stop()
{
    StopMusicStream(this->_music);
}

void raylib::Music::resume()
{
    ResumeMusicStream(this->_music);
}

void raylib::Music::pause()
{
    PauseMusicStream(this->_music);
}

void raylib::Music::update()
{
    UpdateMusicStream(_music);
}

void raylib::Music::setPath(const std::string &path)
{
    this->_path = path;
    UnloadMusicStream(this->_music);
    this->_music = LoadMusicStream(this->_path.data());
}

void raylib::Music::setVolume(const float volume)
{
    this->_volume = volume;
    SetMusicVolume(this->_music, this->_volume);
}

void raylib::Music::setPitch(const float pitch)
{
    this->_pitch = pitch;
    SetMusicPitch(this->_music, this->_pitch);
}