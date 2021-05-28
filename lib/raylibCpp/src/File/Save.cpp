/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Save
*/

#include <cstring>
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
    char *cstr = nullptr;

    if (FileExists(_path.data())) {
        cstr = new char[this->_data.length() + 1];
        std::strcpy(cstr, this->_data.c_str());
        UnloadFileText((char *) _data.c_str());
        delete [] cstr;
    }
}

void raylib::Save::setPath(const std::string &path)
{
    char *cstr = nullptr;

    if (FileExists(_path.data())) {
        cstr = new char[this->_data.length() + 1];
        std::strcpy(cstr, this->_data.c_str());
        UnloadFileText((char *) _data.c_str());
        delete [] cstr;
    }
    _path = path;
    if (FileExists(_path.data())) {
        _data = LoadFileText(_path.data());
    }
}

std::string raylib::Save::getData()
{
    return _data;
}

void raylib::Save::updateData(std::string data)
{
    char *cstr = nullptr;

    if (FileExists(_path.data())) {
        cstr = new char[data.length() + 1];
        std::strcpy(cstr, data.c_str());
        SaveFileText(_path.data(), cstr);
        delete [] cstr;
    }
}