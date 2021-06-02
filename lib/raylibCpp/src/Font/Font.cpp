/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Font
*/

#include "Font.hpp"

raylib::Font::Font(const std::string path)
{
    _path = path;
    if (_path.compare("") != 0) {
        _font = LoadFont(_path.data());
        _hasFont = true;
    } else {
        _font = GetFontDefault();
        _hasFont = false;
    }
}

raylib::Font::~Font()
{
    if (_hasFont)
        UnloadFont(_font);
}

void raylib::Font::setPath(const std::string &path)
{
    _path = path;
    UnloadFont(_font);
    _hasFont = true;
    _font = LoadFont(_path.data());
}

RFont raylib::Font::getFont() const
{
    return _font;
}

void raylib::Font::reset()
{
    if (_hasFont) {
        _hasFont = false;
        UnloadFont(_font);
    }
}