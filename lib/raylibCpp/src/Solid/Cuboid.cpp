/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Cuboid
*/

#include "Cuboid.hpp"

raylib::Cuboid::Cuboid(const std::shared_ptr<ITexture> texture, const MyVector3 position,
const MyVector3 size, const RColor color)
{
    _texture = texture;
    _position = position;
    _size = size;
    _color = color;
}

raylib::Cuboid::~Cuboid()
{

}

void raylib::Cuboid::draw()
{
    Vector3 rayPos = {_position.a, _position.b, _position.c};

    if (_texture == nullptr)
        DrawCube(rayPos, _size.a, _size.b, _size.c, _matchingColors.at(_color));
    else {
        DrawCubeTexture(_texture->getTexture(), rayPos, _size.a, _size.b,
        _size.c, _matchingColors.at(_color));
    }
}

void raylib::Cuboid::setPosition(const MyVector3 position)
{
    _position = position;
}

void raylib::Cuboid::setSize(const MyVector3 size)
{
    _size = size;
}

void raylib::Cuboid::setColor(const RColor color)
{
    _color = color;
}

void raylib::Cuboid::setTexture(const std::shared_ptr<ITexture> &texture)
{
    _texture = texture;
}