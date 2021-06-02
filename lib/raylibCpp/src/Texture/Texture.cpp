/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Texture
*/

#include "Texture.hpp"

raylib::Texture::Texture(const string &path, const MyVector2 position, const RColor color)
{
    this->_path = path;
    this->_position = position;
    this->_color = color;
    this->_texture = LoadTexture(path.data());
}

raylib::Texture::~Texture()
{
    UnloadTexture(this->_texture);
}

void raylib::Texture::draw()
{
    DrawTexture(this->_texture, this->_position.a, this->_position.b, _matchingColors.at(this->_color));
}

void raylib::Texture::setPosition(const MyVector2 position)
{
    this->_position = position;
}

void raylib::Texture::setColor(const RColor color)
{
    this->_color = color;
}

void raylib::Texture::setPath(const string &path)
{
    this->_path = path;
    UnloadTexture(this->_texture);
    this->_texture = LoadTexture(path.data());
}

Texture2D raylib::Texture::getTexture() const
{
    return this->_texture;
}

string raylib::Texture::getPath() const
{
    return this->_path;
}