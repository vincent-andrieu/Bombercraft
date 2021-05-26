/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Cube
*/

#include "Cube.hpp"

raylib::Cube::Cube(std::shared_ptr<ITexture> texture, MyVector3 position,
MyVector3 size, RColor color)
{
    _texture = texture;
    _position = position;
    _size = size;
    _color = color;
}

raylib::Cube::~Cube()
{

}

void raylib::Cube::draw()
{
    Vector3 rayPos = {_position.a, _position.b, _position.c};

    if (_texture == nullptr)
        DrawCube(rayPos, _size.a, _size.b, _size.c, _matchingColors.at(_color));
    else {
        DrawCubeTexture(_texture->getTexture(), rayPos, _size.a, _size.b,
        _size.c, _matchingColors.at(_color));
    }
}

void raylib::Cube::setPosition(MyVector3 position)
{
    _position = position;
}

void raylib::Cube::setSize(MyVector3 size)
{
    _size = size;
}

void raylib::Cube::setColor(RColor color)
{
    _color = color;
}

void raylib::Cube::setTexture(std::shared_ptr<ITexture> &texture)
{
    _texture = texture;
}