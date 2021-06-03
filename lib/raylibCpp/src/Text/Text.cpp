/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Text
*/

#include "Text.hpp"

raylib::Text::Text(const string &text, const MyVector2 position, const size_t size, const RColor color)
{
    this->_text = text;
    this->_position = position;
    this->_font = std::make_shared<raylib::Font>();
    this->_color = color;
    this->_size = size;
    this->_limit = {-1, -1, -1, -1};
}

void raylib::Text::draw()
{
    Vector2 rayPos = {this->_position.a, this->_position.b};
    int spacing = this->_size / 10;

    if (this->_size < 10) {
        spacing = 1;
    }
    if (this->_limit.height == -1) {
        DrawTextEx(this->_font->getFont(), this->_text.data(), rayPos, this->_size, spacing, _matchingColors.at(this->_color));
    } else {
        DrawTextRec(this->_font->getFont(), this->_text.data(), this->_limit, this->_size, spacing, true,
            _matchingColors.at(this->_color));
    }
}

void raylib::Text::setText(const string &text)
{
    this->_text = text;
}

void raylib::Text::setPosition(const MyVector2 position)
{
    this->_position = position;
}

void raylib::Text::setFont(const string &font)
{
    this->_font->setPath(font);
}

void raylib::Text::setColor(const RColor color)
{
    this->_color = color;
}

void raylib::Text::setFontSize(const size_t size)
{
    this->_size = size;
}

void raylib::Text::setLimit(const MyVector4 limit)
{
    this->_limit.x = limit.a;
    this->_limit.y = limit.b;
    this->_limit.width = limit.c;
    this->_limit.height = limit.d;
}

void raylib::Text::removeFont()
{
    this->_font->reset();
}

void raylib::Text::removeLimit()
{
    this->_limit.x = -1;
    this->_limit.y = -1;
    this->_limit.width = -1;
    this->_limit.height = -1;
}