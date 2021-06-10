/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Animation
*/

#include "Animation.hpp"

raylib::Animation::Animation(const std::string &texturePath, const string &dirpath, const MyVector3 position, const RColor color)
{
    char **filenames = nullptr;
    int count = 0;
    const char *workingDirectory = GetWorkingDirectory();

    this->_position = position;
    this->_rotation = {0.0f, 0.0f, 0.0f};
    this->_scale = 1.0f;
    this->_color = color;
    this->_textures = {};
    if (texturePath.compare("") != 0)
        getNewTexture(texturePath);
    this->_path = dirpath;
    this->_currentFrame = 0;
    this->_start = std::chrono::system_clock::now();
    if (DirectoryExists(_path.data())) {
        filenames = goInDirectoryAndGetFileNames(_path, &count);
        for (size_t i = 0; i < (size_t) count; i++) {
            if (IsFileExtension(filenames[i], ".obj"))
                _models.push_back(LoadModel(filenames[i]));
        }
        LeaveDirectoryAndClearFileNames(workingDirectory);
    }
}

raylib::Animation::~Animation()
{
    for (size_t i = 0; i < this->_models.size(); i++) {
        UnloadModel(this->_models[i]);
    }
    this->_models.clear();
    for (size_t i = 0; i < _textures.size(); i++) {
        for (size_t j = 0; j < _textures[i].size(); j++) {
            UnloadTexture(_textures[i][j]);
        }
    }
}

void raylib::Animation::getNewTexture(const std::string &texturePath)
{
    char **filenames = nullptr;
    char **subFilenames = nullptr;
    int count = 0;
    int subCount = 0;
    const char *workingDirectory = GetWorkingDirectory();

    if (DirectoryExists(texturePath.data())) {
        filenames = goInDirectoryAndGetFileNames(texturePath, &count);
        for (size_t i = 0; i < (size_t) count; i++) {
            if (strcmp(filenames[i], "..") == 0 || strcmp(filenames[i], ".") == 0)
                continue;
            if (DirectoryExists(filenames[i])) {
                _textures.push_back({});
                subFilenames = goInDirectoryAndGetFileNames(filenames[i], &subCount);
                for (size_t j = 0; j < (size_t) subCount; j++) {
                    if (!DirectoryExists(subFilenames[i]))
                        _textures[_textures.size() - 1].push_back(LoadTexture(subFilenames[j]));
                }
                LeaveDirectoryAndClearFileNames(texturePath);
            } else if (FileExists(filenames[i]))
                _textures.push_back({LoadTexture(filenames[i])});
        }
        LeaveDirectoryAndClearFileNames(workingDirectory);
    } else if (FileExists(texturePath.data()))
        _textures.push_back({LoadTexture(texturePath.data())});
}

char **raylib::Animation::goInDirectoryAndGetFileNames(const std::string &directoryPath, int *count)
{
    char **filenames = nullptr;

    filenames = GetDirectoryFiles(directoryPath.data(), count);
    ChangeDirectory(directoryPath.data());
    return filenames;
}

void raylib::Animation::LeaveDirectoryAndClearFileNames(const std::string &oldDirectoryPath)
{
    ClearDirectoryFiles();
    ChangeDirectory(oldDirectoryPath.data());
}

void raylib::Animation::setNewTexture()
{
    if (_textures.size() == 0)
        return;
    for (size_t i = 0; i < _models.size(); i++) {
        if (_textures[i % _textures.size()].size() == 0)
            continue;
        for (size_t j = 0; j < _models[i].materialCount; j++) {
            SetMaterialTexture(&_models[i].materials[j], MAP_DIFFUSE, _textures[i % _textures.size()][j % _textures[i].size()]);
        }
    }
}

void raylib::Animation::draw()
{
    Vector3 rayPos = {_position.a, _position.b, _position.c};
    std::chrono::milliseconds timeElapsed(0);
    std::chrono::milliseconds waitTime(100);
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

    timeElapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch() - _start.time_since_epoch());
    if (timeElapsed >= waitTime) {
        _currentFrame = (_currentFrame + 1) % _models.size();
        _start = std::chrono::system_clock::now();
    }
    if (_models.size() > 0) {
        DrawModel(_models[_currentFrame], rayPos, _scale, _matchingColors.at(_color));
    }
}

void raylib::Animation::setPosition(const MyVector3 position)
{
    this->_position = position;
}

void raylib::Animation::setRotation(const MyVector3 rotation)
{
    float pitch = rotation.a;
    float yam = rotation.b;
    float roll = rotation.c;

    this->_rotation = rotation;
    for (size_t i = 0; i < this->_models.size(); i++) {
        this->_models[i].transform =
            MatrixRotateXYZ(MyVector3::makeVector3(MyVector3(DEG2RAD * pitch, DEG2RAD * yam, DEG2RAD * roll)));
    }
}

void raylib::Animation::setScale(const float scale)
{
    this->_scale = scale;
}

void raylib::Animation::setColor(const RColor color)
{
    this->_color = color;
}

void raylib::Animation::setPath(const string &path)
{
    MyVector3 rotation;
    float pitch = this->_rotation.a;
    float yam = this->_rotation.b;
    float roll = this->_rotation.c;
    char **filenames = nullptr;
    int count = 0;

    this->_path = path;
    for (size_t i = 0; i < this->_models.size(); i++) {
        UnloadModel(this->_models[i]);
    }
    this->_models.clear();
    filenames = GetDirectoryFiles(this->_path.data(), &count);
    for (size_t i = 0; i < (size_t) count; i++) {
        this->_models.push_back(LoadModel(filenames[i]));
    }
    ClearDirectoryFiles();
    for (size_t i = 0; i < this->_models.size(); i++) {
        this->_models[i].transform =
            MatrixRotateXYZ(MyVector3::makeVector3(MyVector3(DEG2RAD * pitch, DEG2RAD * yam, DEG2RAD * roll)));
    }
}

void raylib::Animation::setTexture(const std::string &texturePath)
{
    char **filenames = nullptr;
    int count = 0;
    const char *workingDirectory = GetWorkingDirectory();

    if (texturePath.compare("") != 0) {
        getNewTexture(texturePath);
    }
    setNewTexture();
}

string raylib::Animation::getPath() const
{
    return this->_path;
}