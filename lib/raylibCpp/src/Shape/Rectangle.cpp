/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Rectangle
*/

#include "Rectangle.hpp"

raylib::Rectangle::Rectangle(const MyVector2 position, const MyVector2 size, const RColor color)
{
    this->_position = position;
    this->_size = size;
    this->_color = color;
}

void raylib::Rectangle::draw()
{
    DrawRectangle(this->_position.a, this->_position.b, this->_size.a, this->_size.b, _matchingColors.at(this->_color));
}

void raylib::Rectangle::setPosition(const MyVector2 position)
{
    this->_position = position;
}

raylib::MyVector2 raylib::Rectangle::getPosition() const
{
    return this->_position;
}

void raylib::Rectangle::setSize(const MyVector2 size)
{
    this->_size = size;
}

raylib::MyVector2 raylib::Rectangle::getSize() const
{
    return this->_size;
}

void raylib::Rectangle::setColor(const RColor color)
{
    this->_color = color;
}