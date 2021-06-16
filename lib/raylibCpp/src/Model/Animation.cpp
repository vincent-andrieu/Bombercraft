/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Animation
*/

#include "Animation.hpp"
#include "Model.hpp"

raylib::Animation::Animation(const std::string &texturePath,
    const std::string &dirpath,
    const MyVector3 position,
    const RColor color,
    bool isLooping,
    std::size_t speed)
    : _speed(speed), _position(position), _rotation({0.0f, 0.0f, 0.0f}), _scale(1.0f), _color(color), _textures({}), _texturePath(texturePath),
      _path(dirpath), _currentFrame(0), _start(std::chrono::system_clock::now()), _isLooping(isLooping)
{
    std::vector<std::string> filenames = {};
    int count = 0;
    std::string workingDirectory = GetWorkingDirectory();

    if (!raylib::Model::_loaderManager)
        raylib::Model::_loaderManager =
            std::make_shared<raylib::LoaderManager<RModel, std::tuple<std::string, std::string>, tuple_hash>>(
                raylib::Model::myModelLoad, raylib::Model::myModelUnload);
    if (DirectoryExists(_path.data())) {
        filenames = goInDirectoryAndGetFileNames(_path, &count);
        for (size_t i = 0; i < (size_t) count; i++) {
            if (IsFileExtension(filenames[i].data(), ".obj")) {
                auto tmp = raylib::Model::_loaderManager->load({filenames[i], this->_texturePath});
                _models.push_back(tmp);
            }
        }
        LeaveDirectoryAndClearFileNames(workingDirectory);
    }
    if (_texturePath.compare("") != 0) {
        getNewTexture(_texturePath);
        setNewTexture();
    }
}

raylib::Animation::~Animation()
{
}

void raylib::Animation::getNewTexture(const std::string &texturePath)
{
    std::vector<std::string> filenames = {};
    std::vector<std::string> subFilenames = {};
    int count = 0;
    int subCount = 0;
    std::string workingDirectory = GetWorkingDirectory();

    if (DirectoryExists(texturePath.data())) {
        filenames = goInDirectoryAndGetFileNames(texturePath, &count);
        for (size_t i = 0; i < (size_t) count; i++) {
            if (DirectoryExists(filenames[i].data())) {
                _textures.push_back({});
                subFilenames = goInDirectoryAndGetFileNames(filenames[i], &subCount);
                for (size_t j = 0; j < (size_t) subCount; j++) {
                    if (!DirectoryExists(subFilenames[i].data()))
                        _textures[_textures.size() - 1].push_back(raylib::Texture::_loaderManager->load(subFilenames[j]));
                }
                LeaveDirectoryAndClearFileNames(texturePath);
            } else if (FileExists(filenames[i].data())) {
                _textures.push_back({raylib::Texture::_loaderManager->load(filenames[i])});
            }
        }
        LeaveDirectoryAndClearFileNames(workingDirectory);
    } else if (FileExists(texturePath.data())) {
        _textures.push_back({raylib::Texture::_loaderManager->load(texturePath.data())});
    }
}

std::vector<std::string> raylib::Animation::goInDirectoryAndGetFileNames(const std::string &directoryPath, int *count)
{
    char **filenames = nullptr;
    std::vector<std::string> vectorOfFilenames = {};
    int reelCount = 0;

    filenames = GetDirectoryFiles(directoryPath.data(), count);
    ChangeDirectory(directoryPath.data());
    for (size_t i = 0; i < (size_t) *count; i++) {
        if (!IsFileExtension(filenames[i], ".mtl") && strcmp(filenames[i], "..") != 0 && strcmp(filenames[i], ".") != 0) {
            vectorOfFilenames.push_back(filenames[i]);
            reelCount += 1;
        }
    }
    std::sort(vectorOfFilenames.begin(), vectorOfFilenames.end());
    *count = reelCount;
    return vectorOfFilenames;
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
            SetMaterialTexture(&_models[i].materials[j],
                MAP_DIFFUSE,
                _textures[i % _textures.size()][j % _textures[i % _textures.size()].size()]);
        }
    }
}

void raylib::Animation::draw()
{
    Vector3 rayPos = {_position.a, _position.b, _position.c};
    std::chrono::milliseconds timeElapsed(0);
    std::chrono::milliseconds waitTime(_speed);
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

    timeElapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch() - _start.time_since_epoch());
    if (timeElapsed >= waitTime) {
        _currentFrame += 1;
        if (_currentFrame == _models.size() && _isLooping) {
            _currentFrame = _currentFrame % _models.size();
        } else if (_currentFrame == _models.size() && !_isLooping) {
            _currentFrame -= 1;
        }
        _start = std::chrono::system_clock::now();
    }
    if (_models.size() > 0) {
        DrawModel(_models[_currentFrame], rayPos, _scale, _matchingColors.at(_color));
    }
}

void raylib::Animation::restartAnimation()
{
    _currentFrame = 0;
}

void raylib::Animation::setPosition(const MyVector3 position)
{
    this->_position = position;
}

const raylib::MyVector3 &raylib::Animation::getPosition() const
{
    return this->_position;
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
    this->_models.clear();
    filenames = GetDirectoryFiles(this->_path.data(), &count);
    for (size_t i = 0; i < (size_t) count; i++) {
        this->_models.push_back(raylib::Model::_loaderManager->load({filenames[i], this->_texturePath}));
    }
    ClearDirectoryFiles();
    for (size_t i = 0; i < this->_models.size(); i++) {
        this->_models[i].transform =
            MatrixRotateXYZ(MyVector3::makeVector3(MyVector3(DEG2RAD * pitch, DEG2RAD * yam, DEG2RAD * roll)));
    }
    if (_texturePath.compare("") != 0) {
        getNewTexture(_texturePath);
        setNewTexture();
    }
}

void raylib::Animation::setTexture(const std::string &texturePath)
{
    if (texturePath.compare("") != 0) {
        this->_texturePath = texturePath;
        getNewTexture(texturePath);
    }
    setNewTexture();
}

string raylib::Animation::getPath() const
{
    return this->_path;
}
