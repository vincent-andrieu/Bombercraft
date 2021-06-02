/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Font
*/

#include "Font.hpp"

raylib::Font::Font(const string path)
{
    this->_path = path;
    if (this->_path.compare("") != 0) {
        this->_font = LoadFont(this->_path.data());
        this->_hasFont = true;
    } else {
        this->_font = GetFontDefault();
        this->_hasFont = false;
    }
}

raylib::Font::~Font()
{
    if (this->_hasFont)
        UnloadFont(this->_font);
}

void raylib::Font::setPath(const string &path)
{
    this->_path = path;
    UnloadFont(this->_font);
    this->_hasFont = true;
    this->_font = LoadFont(this->_path.data());
}

RFont raylib::Font::getFont() const
{
    return this->_font;
}

void raylib::Font::reset()
{
    if (this->_hasFont) {
        this->_hasFont = false;
        UnloadFont(this->_font);
    }
}