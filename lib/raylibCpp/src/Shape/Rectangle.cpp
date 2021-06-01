/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Rectangle
*/

#include "Rectangle.hpp"

raylib::Rectangle::Rectangle(MyVector2 position,
MyVector2 size, RColor color)
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

void raylib::Rectangle::setPosition(MyVector2 position)
{
    _position = position;
}

void raylib::Rectangle::setSize(MyVector2 size)
{
    _size = size;
}

void raylib::Rectangle::setColor(RColor color)
{
    _color = color;
}