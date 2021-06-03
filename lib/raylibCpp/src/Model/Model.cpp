/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Model
*/

#include "Model.hpp"

raylib::Model::Model(const std::string &texturePath, const string &filepath, const MyVector3 position = {0, 0, 0},
    const RColor color = RColor::RWHITE)
{
    this->_position = position;
    this->_rotation = {0.0f, 0.0f, 0.0f};
    this->_scale = 1.0f;
    this->_color = color;
    this->_texture = {0};
    this->_texturePath = texturePath;
    if (texturePath.compare("") != 0) {
        if (FileExists(texturePath.data())) {
            _texture = LoadTexture(texturePath.data());
        }
    }
    this->_path = filepath;
    this->_model = LoadModel(filepath.data());
    if (texturePath.compare("") != 0)
        SetMaterialTexture(&_model.materials[0], MAP_DIFFUSE, _texture);
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

void raylib::Model::setRotation(const MyVector3 rotation)
{
    float pitch = rotation.a;
    float yam = rotation.b;
    float roll = rotation.c;

    this->_rotation = rotation;
    this->_model.transform = MatrixRotateXYZ((Vector3){DEG2RAD * pitch, DEG2RAD * yam, DEG2RAD * roll});
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
    this->_model.transform = MatrixRotateXYZ((Vector3){DEG2RAD * pitch, DEG2RAD * yam, DEG2RAD * roll});
}

void raylib::Model::setTexture(const std::string &texturePath)
{
    if (_texturePath.compare("") != 0) {
        UnloadTexture(_texture);
    }
    _texturePath = texturePath;
    if (texturePath.compare("") != 0) {
        if (FileExists(texturePath.data())) {
            _texture = LoadTexture(texturePath.data());
        }
    }
    if (texturePath.compare("") != 0)
        SetMaterialTexture(&_model.materials[0], MAP_DIFFUSE, _texture);
}

string raylib::Model::getPath() const
{
    return this->_path;
}