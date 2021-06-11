/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** TextureSequence Sequence
*/

#include "TextureSequence.hpp"

raylib::TextureSequence::TextureSequence(const string &path, const MyVector2 size, const MyVector2 position, const RColor color)
{
    const char *workingDirectory = GetWorkingDirectory();
    char **filenames = nullptr;
    int count = 0;

    this->_path = path;
    this->_position = position;
    this->_color = color;
    this->_currentFrame = 0;
    if (!DirectoryExists(path.data())) {
        this->_textures = {};
        this->_frameNumber = 0;
    } else {
        filenames = GetDirectoryFiles(_path.data(), &count);
        this->_frameNumber = count;
        ChangeDirectory(_path.data());
        for (size_t i = 0; i < (size_t) count; i++) {
            _textures.push_back(raylib::Texture::_loaderManager->load(filenames[i]));
        }
        ClearDirectoryFiles();
        ChangeDirectory(workingDirectory);
    }
    this->_size = {this->_position.a, this->_position.b, size.a, size.b};
}

raylib::TextureSequence::~TextureSequence()
{
}

void raylib::TextureSequence::draw()
{
    Vector2 rayPos = {this->_position.a, this->_position.b};

    if (_size.width == -1)
        DrawTexture(this->_textures[_currentFrame], this->_position.a, this->_position.b, _matchingColors.at(this->_color));
    else
        DrawTextureRec(this->_textures[_currentFrame], this->_size, rayPos, _matchingColors.at(this->_color));
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
    const char *workingDirectory = GetWorkingDirectory();
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
        ChangeDirectory(workingDirectory);
    }
}

void raylib::TextureSequence::setSize(const MyVector2 size)
{
    this->_size.width = size.a;
    this->_size.height = size.b;
}

Texture2D raylib::TextureSequence::getTexture() const
{
    return this->_textures[_currentFrame];
}

string raylib::TextureSequence::getPath() const
{
    return this->_path;
}