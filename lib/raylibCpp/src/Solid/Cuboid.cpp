/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Cuboid
*/

#include "Cuboid.hpp"

raylib::Cuboid::Cuboid(
    const std::shared_ptr<ITexture> texture, const MyVector3 position, const MyVector3 size, const RColor color)
{
    this->_texture = texture;
    this->_position = position;
    this->_size = size;
    this->_color = color;
}

void raylib::Cuboid::draw()
{
    Vector3 rayPos = {this->_position.a, this->_position.b, this->_position.c};

    if (this->_texture == nullptr)
        DrawCube(rayPos, this->_size.a, this->_size.b, this->_size.c, _matchingColors.at(this->_color));
    else {
        DrawCubeTexture(
            this->_texture->getTexture(), rayPos, this->_size.a, this->_size.b, this->_size.c, _matchingColors.at(this->_color));
    }
}

void raylib::Cuboid::setPosition(const MyVector3 position)
{
    this->_position = position;
}

const raylib::MyVector3 &raylib::Cuboid::getPosition() const
{
    return this->_position;
}

void raylib::Cuboid::setSize(const MyVector3 size)
{
    this->_size = size;
}

void raylib::Cuboid::setColor(const RColor color)
{
    this->_color = color;
}

void raylib::Cuboid::setTexture(const std::shared_ptr<ITexture> &texture)
{
    this->_texture = texture;
}