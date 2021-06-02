/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Animation
*/

#include "Animation.hpp"

raylib::Animation::Animation(const std::shared_ptr<ITexture> texture, const std::string &dirpath,
const MyVector3 position, const RColor color)
{
    char **filenames = nullptr;
    int count = 0;
    const char *workingDirectory = GetWorkingDirectory();

    _position = position;
    _rotation = {0.0f, 0.0f, 0.0f};
    _scale = 1.0f;
    _color = color;
    _texture = texture;
    _path = dirpath;
    _currentFrame = 0;
    start = std::chrono::system_clock::now();
    if (DirectoryExists(_path.data())) {
        filenames = GetDirectoryFiles(_path.data(), &count);
        ChangeDirectory(_path.data());
        for (size_t i = 0; i < (size_t) count; i++) {
            if (IsFileExtension(filenames[i], ".obj"))
                _models.push_back(LoadModel(filenames[i]));
        }
        ClearDirectoryFiles();
        ChangeDirectory(workingDirectory);
    }
    if (_texture == nullptr)
        return;
    for (size_t i = 0; i < _models.size(); i++) {
        SetMaterialTexture(&_models[i].materials[0], MAP_DIFFUSE, texture->getTexture());
    }
}

raylib::Animation::~Animation()
{
    for (size_t i = 0; i < _models.size(); i++) {
        UnloadModel(_models[i]);
    }
    _models.clear();
}

void raylib::Animation::draw()
{
    Vector3 rayPos = {_position.a, _position.b, _position.c};
    std::chrono::milliseconds timeElapsed(0);
    std::chrono::milliseconds waitTime(100);
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

    timeElapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch() - start.time_since_epoch());
    if (timeElapsed >= waitTime) {
        _currentFrame = (_currentFrame + 1) % _models.size();
        start = std::chrono::system_clock::now();
    }
    if (_models.size() > 0) {
        DrawModel(_models[_currentFrame], rayPos, _scale, _matchingColors.at(_color));        
    }
}

void raylib::Animation::setPosition(const MyVector3 position)
{
    _position = position;
}

void raylib::Animation::setRotation(const MyVector3 rotation)
{
    float pitch = rotation.a;
    float yam = rotation.b;
    float roll = rotation.c;

    _rotation = rotation;
    for (size_t i = 0; i < _models.size(); i++) {
        _models[i].transform =
        MatrixRotateXYZ((Vector3){ DEG2RAD * pitch, DEG2RAD * yam, DEG2RAD * roll});
    }
}

void raylib::Animation::setScale(const float scale)
{
    _scale = scale;
}

void raylib::Animation::setColor(const RColor color)
{
    _color = color;
}

void raylib::Animation::setPath(const std::string &path)
{
    float pitch = _rotation.a;
    float yam = _rotation.b;
    float roll = _rotation.c;
    char **filenames = nullptr;
    int count = 0;

    _path = path;
    for (size_t i = 0; i < _models.size(); i++) {
        UnloadModel(_models[i]);
    }
    _models.clear();
    filenames = GetDirectoryFiles(_path.data(), &count);
    for (size_t i = 0; i < (size_t) count; i++) {
        _models.push_back(LoadModel(filenames[i]));
    }
    ClearDirectoryFiles();
    for (size_t i = 0; i < _models.size(); i++) {
        _models[i].transform =
        MatrixRotateXYZ((Vector3){ DEG2RAD * pitch, DEG2RAD * yam, DEG2RAD * roll});
    }
}

void raylib::Animation::setTexture(const std::shared_ptr<ITexture> &texture)
{
    _texture = texture;
    if (_texture == nullptr)
        return;
    for (size_t i = 0; i < _models.size(); i++) {
        SetMaterialTexture(&_models[i].materials[0], MAP_DIFFUSE, texture->getTexture());
    }
}

std::string raylib::Animation::getPath() const
{
    return _path;
}