/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Texture
*/

#include "Texture.hpp"

std::shared_ptr<raylib::LoaderManager<Texture2D, std::string>> raylib::Texture::_loaderManager = nullptr;

raylib::Texture::Texture(const string &path,
    const MyVector2 size,
    const MyVector2 position,
    const RColor color,
    const bool scaleMode,
    const MyVector2 truncateSize)
{
    if (!this->_loaderManager)
        this->setLoaderManager();
    this->_path = path;
    this->_position = position;
    this->_color = color;
    this->_size = size;
    this->_texture = this->_loaderManager->load(path.data());
    this->_truncateCoef = {size.a / _texture.width, size.b / _texture.height};
    this->_destRect = {
        _position.a, _position.b, (_texture.width * _truncateCoef.a - truncateSize.a) , (_texture.height * _truncateCoef.b - truncateSize.b)};
    this->_scaleMode = scaleMode;
    this->_truncateSize = truncateSize;
}

raylib::Texture::~Texture()
{
}

void raylib::Texture::draw()
{
    Vector2 rayPos = {this->_position.a, this->_position.b};
    Rectangle srcRect = {0, 0, (float) _texture.width - (_truncateSize.a / _truncateCoef.a), (float) _texture.height - (_truncateSize.b / _truncateCoef.b)};
    Rectangle position = {this->_position.a, this->_position.b, (float) _texture.width, (float) _texture.height};

    if (_scaleMode) {
        if (_destRect.width == -1)
            DrawTexturePro(this->_texture, srcRect, position, {0, 0}, 0, _matchingColors.at(this->_color));
        else
            DrawTexturePro(this->_texture, srcRect, this->_destRect, {0, 0}, 0, _matchingColors.at(this->_color));
    } else {
        if (_destRect.width == -1)
            DrawTexture(this->_texture, this->_position.a, this->_position.b, _matchingColors.at(this->_color));
        else
            DrawTextureRec(this->_texture, this->_destRect, rayPos, _matchingColors.at(this->_color));
    }
}

void raylib::Texture::update()
{
}

void raylib::Texture::setPosition(const MyVector2 position)
{
    this->_position = position;
    this->_destRect.x = this->_position.a;
    this->_destRect.y = this->_position.b;
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
    this->_size = size;
}

void raylib::Texture::setRect(const MyVector2 rect)
{
    this->_destRect.x = rect.a;
    this->_destRect.y = rect.b;
}

void raylib::Texture::setTruncateSize(const MyVector2 &size)
{
    this->_truncateCoef = {_size.a / _texture.width, _size.b / _texture.height};
    this->_destRect = {_position.a, _position.b, (_texture.width * _truncateCoef.a - size.a), (_texture.height * _truncateCoef.b - size.b)};
    this->_truncateSize = size;
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
    return MyVector2(this->_destRect.x, this->_destRect.y);
}

raylib::MyVector2 raylib::Texture::getSize() const
{
    return _size;
}

void raylib::Texture::setLoaderManager()
{
    if (!this->_loaderManager) {
        this->_loaderManager = std::make_shared<raylib::LoaderManager<Texture2D, std::string>>(
            raylib::Texture::myTextureLoad, raylib::Texture::myTextureUnload);
    } else {
        this->_loaderManager.reset();
        this->_loaderManager = std::make_shared<raylib::LoaderManager<Texture2D, std::string>>(
            raylib::Texture::myTextureLoad, raylib::Texture::myTextureUnload);
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