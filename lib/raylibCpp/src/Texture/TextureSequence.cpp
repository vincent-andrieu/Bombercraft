/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** TextureSequence Sequence
*/

#include "TextureSequence.hpp"

raylib::TextureSequence::TextureSequence(const string &path, const MyVector2 size, const MyVector2 position, const RColor color)
    : _path(path), _position(position), _color(color), _currentFrame(0), _textures({}),
      _size({this->_position.a, this->_position.b, size.a, size.b}), _scaleMode(true)
{
    std::string workingDirectory = GetWorkingDirectory();
    char **filenames = nullptr;
    int count = 0;
    std::vector<std::string> vectorOfFilenames = {};

    if (!raylib::Texture::_loaderManager) {
        raylib::Texture::_loaderManager = std::make_shared<raylib::LoaderManager<Texture2D, std::string>>(
            raylib::Texture::myTextureLoad, raylib::Texture::myTextureUnload);
    }
    if (!DirectoryExists(path.data())) {
        this->_frameNumber = 0;
    } else {
        filenames = GetDirectoryFiles(_path.data(), &count);
        this->_frameNumber = count;
        ChangeDirectory(_path.data());
        for (size_t i = 0; i < (size_t) count; i++) {
            vectorOfFilenames.push_back(filenames[i]);
        }
        std::sort(vectorOfFilenames.begin(), vectorOfFilenames.end());
        for (size_t i = 0; i < (size_t) count; i++) {
            if (!DirectoryExists(vectorOfFilenames[i].data())) {
                _textures.push_back(raylib::Texture::_loaderManager->load(vectorOfFilenames[i].data()));
            }
        }
        ClearDirectoryFiles();
        ChangeDirectory(workingDirectory.data());
    }
}

raylib::TextureSequence::~TextureSequence()
{
}

void raylib::TextureSequence::draw()
{
    Vector2 rayPos = {this->_position.a, this->_position.b};
    Rectangle ogRect = {0, 0, (float) _textures[_currentFrame].width, (float) _textures[_currentFrame].height};
    Rectangle position = {
        this->_position.a, this->_position.b, (float) _textures[_currentFrame].width, (float) _textures[_currentFrame].height};

    if (_scaleMode) {
        if (_size.width == -1)
            DrawTexturePro(this->_textures[_currentFrame], ogRect, position, {0, 0}, 0, _matchingColors.at(this->_color));
        else
            DrawTexturePro(this->_textures[_currentFrame], ogRect, this->_size, {0, 0}, 0, _matchingColors.at(this->_color));
    } else {
        if (_size.width == -1)
            DrawTexture(this->_textures[_currentFrame], this->_position.a, this->_position.b, _matchingColors.at(this->_color));
        else
            DrawTextureRec(this->_textures[_currentFrame], this->_size, rayPos, _matchingColors.at(this->_color));
    }
}

void raylib::TextureSequence::update()
{
    _currentFrame += 1;
    if (_frameNumber != 0)
        _currentFrame = _currentFrame % _frameNumber;
}

void raylib::TextureSequence::setPosition(const MyVector2 position)
{
    this->_position = position;
    this->_size.x = this->_position.a;
    this->_size.y = this->_position.b;
}

void raylib::TextureSequence::setColor(const RColor color)
{
    this->_color = color;
}

void raylib::TextureSequence::setPath(const string &path)
{
    std::string workingDirectory = GetWorkingDirectory();
    char **filenames = nullptr;
    int count = 0;

    this->_textures.clear();
    this->_path = path;
    this->_currentFrame = 0;
    if (!DirectoryExists(path.data())) {
        this->_frameNumber = 0;
    } else {
        filenames = GetDirectoryFiles(_path.data(), &count);
        this->_frameNumber = count;
        ChangeDirectory(_path.data());
        for (size_t i = 0; i < (size_t) count; i++) {
            _textures.push_back(raylib::Texture::_loaderManager->load(filenames[i]));
        }
        ClearDirectoryFiles();
        ChangeDirectory(workingDirectory.data());
    }
}

void raylib::TextureSequence::setSize(const MyVector2 size)
{
    this->_size.width = size.a;
    this->_size.height = size.b;
}

void raylib::TextureSequence::setScaleMode(const bool mode)
{
    _scaleMode = mode;
}

void raylib::TextureSequence::setRect(const MyVector2 rect)
{
    this->_size.x = rect.a;
    this->_size.y = rect.b;
}

void raylib::TextureSequence::setOgRect(const MyVector4 ogRect)
{
}

Texture2D raylib::TextureSequence::getTexture() const
{
    return this->_textures[_currentFrame];
}

string raylib::TextureSequence::getPath() const
{
    return this->_path;
}

raylib::MyVector2 raylib::TextureSequence::getRect() const
{
    return MyVector2(this->_size.x, this->_size.y);
}

raylib::MyVector2 raylib::TextureSequence::getSize() const
{
    return MyVector2(this->_size.width, this->_size.height);
}

raylib::MyVector2 raylib::TextureSequence::getPosition() const
{
    return _position;
}