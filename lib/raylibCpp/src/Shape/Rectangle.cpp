/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Rectangle
*/

#include "Rectangle.hpp"

raylib::Rectangle::Rectangle(const MyVector2 position,
const MyVector2 size, const RColor color)
{
    _position = position;
    _size = size;
    _color = color;
}

raylib::Rectangle::~Rectangle()
{

}

void raylib::Rectangle::draw()
{
    DrawRectangle(_position.a, _position.b, _size.a, _size.b, _matchingColors.at(_color));
}

void raylib::Rectangle::setPosition(const MyVector2 position)
{
    _position = position;
}

void raylib::Rectangle::setSize(const MyVector2 size)
{
    _size = size;
}

void raylib::Rectangle::setColor(const RColor color)
{
    _color = color;
}