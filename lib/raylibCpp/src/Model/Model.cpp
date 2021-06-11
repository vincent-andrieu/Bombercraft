/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Model
*/

#include "Model.hpp"

raylib::Model::Model(const std::string &texturePath, const string &filepath, const MyVector3 position, const RColor color)
{
    char **filenames = nullptr;
    int count = 0;
    const char *workingDirectory = GetWorkingDirectory();

    this->_position = position;
    this->_rotation = {0.0f, 0.0f, 0.0f};
    this->_scale = 1.0f;
    this->_color = color;
    this->_textures = {};
    this->_texturePath = texturePath;
    if (texturePath.compare("") != 0) {
        if (DirectoryExists(texturePath.data())) {
            filenames = GetDirectoryFiles(_texturePath.data(), &count);
            ChangeDirectory(_texturePath.data());
            for (size_t i = 0; i < (size_t) count; i++) {
                if (!DirectoryExists(filenames[i]))
                    _textures.push_back(raylib::Texture::_loaderManager->load(filenames[i]));
            }
            ClearDirectoryFiles();
            ChangeDirectory(workingDirectory);
        } else if (FileExists(texturePath.data())) {
            _textures.push_back(raylib::Texture::_loaderManager->load(texturePath.data()));
        }
    }
    this->_path = filepath;
    this->_model = LoadModel(filepath.data());
    if (_textures.size() == 0)
        return;
    for (size_t i = 0; i < _model.materialCount; i++) {
        SetMaterialTexture(&_model.materials[i], MAP_DIFFUSE, _textures[i % _textures.size()]);
    }
}

raylib::Model::~Model()
{
    UnloadModel(this->_model);
}

void raylib::Model::draw()
{
    Vector3 rayPos = {this->_position.a, this->_position.b, this->_position.c};

    DrawModel(this->_model, rayPos, this->_scale, _matchingColors.at(this->_color));
}

void raylib::Model::setPosition(const MyVector3 position)
{
    this->_position = position;
}

const raylib::MyVector3 &raylib::Model::getPosition() const
{
    return this->_position;
}

void raylib::Model::setRotation(const MyVector3 rotation)
{
    float pitch = rotation.a;
    float yam = rotation.b;
    float roll = rotation.c;

    this->_rotation = rotation;
    this->_model.transform = MatrixRotateXYZ(MyVector3::makeVector3(MyVector3(DEG2RAD * pitch, DEG2RAD * yam, DEG2RAD * roll)));
}

void raylib::Model::setScale(const float scale)
{
    this->_scale = scale;
}

void raylib::Model::setColor(const RColor color)
{
    this->_color = color;
}

void raylib::Model::setPath(const string &path)
{
    float pitch = this->_rotation.a;
    float yam = this->_rotation.b;
    float roll = this->_rotation.c;

    this->_path = path;
    UnloadModel(this->_model);
    this->_model = LoadModel(path.data());
    this->_model.transform = MatrixRotateXYZ(MyVector3::makeVector3(MyVector3(DEG2RAD * pitch, DEG2RAD * yam, DEG2RAD * roll)));
}

void raylib::Model::setTexture(const std::string &texturePath)
{
    char **filenames = nullptr;
    int count = 0;
    const char *workingDirectory = GetWorkingDirectory();

    _textures.clear();
    _texturePath = texturePath;
    if (texturePath.compare("") != 0) {
        if (DirectoryExists(texturePath.data())) {
            filenames = GetDirectoryFiles(_path.data(), &count);
            ChangeDirectory(_path.data());
            for (size_t i = 0; i < (size_t) count; i++) {
                _textures.push_back(raylib::Texture::_loaderManager->load(filenames[i]));
            }
            ClearDirectoryFiles();
            ChangeDirectory(workingDirectory);
        } else if (FileExists(texturePath.data())) {
            _textures.push_back(raylib::Texture::_loaderManager->load(texturePath.data()));
        }
    }
    if (_textures.size() == 0)
        return;
    for (size_t i = 0; i < _model.materialCount; i++) {
        SetMaterialTexture(&_model.materials[i], MAP_DIFFUSE, _textures[i % _textures.size()]);
    }
}

string raylib::Model::getPath() const
{
    return this->_path;
}