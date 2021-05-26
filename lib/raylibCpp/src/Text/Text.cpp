/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Text
*/

#include "Text.hpp"

raylib::Text::Text(const std::string &text, MyVector2 position,
            size_t size, RColor color)
{
    _text = text;
    _position = position;
    _font = GetFontDefault();
    _color = color;
    _size = size;
    _limit = {-1, -1, -1, -1};
    _hasFont = false;
}

raylib::Text::~Text()
{
    if (_hasFont) {
        UnloadFont(_font);
    }
}

void raylib::Text::draw()
{
    Vector2 rayPos = {_position.a, _position.b};
    int spacing = _size/10;

    if (_size < 10) {
        spacing = 1;
    }
    if (_limit.height == -1) {
        DrawTextEx(_font, _text.data(), rayPos,
        _size, spacing, _matchingColors.at(_color));
    } else {
        DrawTextRec(_font, _text.data(), _limit,
        _size, spacing, true, _matchingColors.at(_color));
    }
}

void raylib::Text::setText(const std::string &text)
{
    _text = text;
}

void raylib::Text::setPosition(MyVector2 position)
{
    _position = position;
}

void raylib::Text::setFont(const std::string &path)
{
    if (_hasFont) {
        UnloadFont(_font);
    }
    _font = LoadFont(path.data());
    _hasFont = true;
}

void raylib::Text::setColor(RColor color)
{
    _color = color;
}

void raylib::Text::setFontSize(size_t size)
{
    _size = size;
}

void raylib::Text::setLimit(MyVector4 limit)
{
    _limit.x = limit.a;
    _limit.y = limit.b;
    _limit.width = limit.c;
    _limit.height = limit.d;
}

void raylib::Text::removeFont()
{
    if (_hasFont) {
        _hasFont = false;
        UnloadFont(_font);
    }
}

void raylib::Text::removeLimit()
{
    _limit.x = -1;
    _limit.y = -1;
    _limit.width = -1;
    _limit.height = -1;
}