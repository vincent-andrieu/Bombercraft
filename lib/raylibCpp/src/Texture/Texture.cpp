/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Texture
*/

#include "Texture.hpp"

raylib::Texture::Texture(const string &path, const MyVector2 size, const MyVector2 position, const RColor color, const bool scaleMode)
    : _path(path), _position(position), _color(color), _texture(LoadTexture(path.data())),
      _size({this->_position.a, this->_position.b, size.a, size.b}), _scaleMode(scaleMode)
{
}

raylib::Texture::~Texture()
{
    UnloadTexture(this->_texture);
}

void raylib::Texture::draw()
{
    Vector2 rayPos = {this->_position.a, this->_position.b};
    Rectangle ogRect = {0, 0, (float) _texture.width, (float) _texture.height};
    Rectangle position = {this->_position.a, this->_position.b, (float)_texture.width, (float)_texture.height};

    if (_scaleMode) {
        if (_size.width == -1)
            DrawTexturePro(this->_texture, ogRect, position, {0, 0}, 0, _matchingColors.at(this->_color));
        else
            DrawTexturePro(this->_texture, ogRect, this->_size, {0, 0}, 0, _matchingColors.at(this->_color));
    } else {
        if (_size.width == -1)
            DrawTexture(this->_texture, this->_position.a, this->_position.b, _matchingColors.at(this->_color));
        else
            DrawTextureRec(this->_texture, this->_size, rayPos, _matchingColors.at(this->_color));
    }
}

void raylib::Texture::update()
{
}

void raylib::Texture::setPosition(const MyVector2 position)
{
    this->_position = position;
    this->_size.x = this->_position.a;
    this->_size.y = this->_position.b;
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

void raylib::Texture::setSize(const MyVector2 size)
{
    this->_size.width = size.a;
    this->_size.height = size.b;
}

void raylib::Texture::setScaleMode(const bool mode)
{
    _scaleMode = mode;
}

Texture2D raylib::Texture::getTexture() const
{
    return this->_texture;
}

string raylib::Texture::getPath() const
{
    return this->_path;
}