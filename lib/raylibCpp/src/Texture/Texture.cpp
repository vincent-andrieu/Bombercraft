/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Texture
*/

#include "Texture.hpp"

std::shared_ptr<raylib::LoaderManager<Texture2D, std::string>> raylib::Texture::_loaderManager = nullptr;

raylib::Texture::Texture(const string &path, const MyVector2 size, const MyVector2 position, const RColor color, const bool scaleMode, const MyVector2 rectPosition)
{
    if (!this->_loaderManager)
        this->setLoaderManager();
    this->_path = path;
    this->_position = position;
    this->_color = color;
    this->_texture = this->_loaderManager->load(path.data());
    if (rectPosition.a == -1 && rectPosition.b == -1) {
        this->_size = {this->_position.a, this->_position.b, size.a, size.b};
    } else {
        this->_size = {rectPosition.a, rectPosition.b, size.a, size.b};
    }
    this->_scaleMode = scaleMode;
}

raylib::Texture::~Texture()
{
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
    this->_texture = this->_loaderManager->load(path.data());
}

void raylib::Texture::setSize(const MyVector2 size)
{
    this->_size.width = size.a;
    this->_size.height = size.b;
}

void raylib::Texture::setRect(const MyVector2 rect)
{
    this->_size.x = rect.a;
    this->_size.y = rect.b;
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

raylib::MyVector2 raylib::Texture::getRect() const
{
    return MyVector2(this->_size.x, this->_size.y);
}

void raylib::Texture::setLoaderManager()
{
    if (!this->_loaderManager) {
        this->_loaderManager = std::make_shared<raylib::LoaderManager<Texture2D, std::string>>(raylib::Texture::myTextureLoad, raylib::Texture::myTextureUnload);
    } else {
        this->_loaderManager.reset();
        this->_loaderManager = std::make_shared<raylib::LoaderManager<Texture2D, std::string>>(raylib::Texture::myTextureLoad, raylib::Texture::myTextureUnload);
    }
}

std::shared_ptr<raylib::LoaderManager<Texture2D, std::string>> raylib::Texture::getLoaderManager() const
{
    return this->_loaderManager;
}

Texture2D raylib::Texture::myTextureLoad(const std::string &str)
{
    return LoadTexture(str.data());
}

void raylib::Texture::myTextureUnload(Texture2D &texture)
{
    UnloadTexture(texture);
}

raylib::MyVector2 raylib::Texture::getPosition() const
{
    return this->_position;
}