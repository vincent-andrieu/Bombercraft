/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Save
*/

#include "Save.hpp"

raylib::Save::Save(const std::string &path)
{
    _path = path;
    if (FileExists(_path.data())) {
        _data = LoadFileText(_path.data());
    }
}

raylib::Save::~Save()
{
    if (FileExists(_path.data())) {
        UnloadFileText(_data);
    }
}

void raylib::Save::setPath(const std::string &path)
{
    if (FileExists(_path.data())) {
        UnloadFileText(_data);
    }
    _path = path;
    if (FileExists(_path.data())) {
        _data = LoadFileText(_path.data());
    }
}

char *raylib::Save::getData()
{
    return _data;
}

void raylib::Save::updateData(char *data)
{
    if (FileExists(_path.data())) {
        SaveFileText(_path.data(), data);
    }
}