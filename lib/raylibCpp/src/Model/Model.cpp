/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Model
*/

#include "Model.hpp"

std::shared_ptr<raylib::LoaderManager<RModel, std::tuple<std::string, std::string>, tuple_hash>> raylib::Model::_loaderManager =
    nullptr;

raylib::Model::Model(const std::string &texturePath,
    const string &filepath,
    const MyVector3 &position,
    const RColor color,
    const MyVector3 &rotation,
    bool forced)
{
    char **filenames = nullptr;
    int count = 0;
    std::string workingDirectory = GetWorkingDirectory();
    std::vector<std::string> vectorOfFilenames = {};

    if (!this->_loaderManager)
        this->setLoaderManager();
    this->_position = position;
    this->_rotation = rotation;
    this->_scale = 1.0f;
    this->_color = color;
    this->_textures = {};
    this->_texturePath = texturePath;
    if (texturePath.compare("") != 0) {
        if (DirectoryExists(texturePath.data())) {
            filenames = GetDirectoryFiles(_texturePath.data(), &count);
            ChangeDirectory(_texturePath.data());
            for (size_t i = 0; i < (size_t) count; i++)
                vectorOfFilenames.push_back(filenames[i]);
            std::sort(vectorOfFilenames.begin(), vectorOfFilenames.end());
            for (size_t i = 0; i < (size_t) count; i++) {
                if (!DirectoryExists(vectorOfFilenames[i].data()))
                    _textures.push_back(raylib::Texture::_loaderManager->load(vectorOfFilenames[i]));
            }
            ClearDirectoryFiles();
            ChangeDirectory(workingDirectory.data());
        } else if (FileExists(texturePath.data())) {
            _textures.push_back(raylib::Texture::_loaderManager->load(texturePath.data()));
        }
    }
    this->_path = filepath;
    this->_model = raylib::Model::_loaderManager->load({filepath.data(), this->_texturePath.data()}, forced);
    if (_textures.size() == 0)
        return;
    for (size_t i = 0; i < _model.materialCount; i++) {
        SetMaterialTexture(&_model.materials[i], MAP_DIFFUSE, _textures[i % _textures.size()]);
    }
}

raylib::Model::~Model()
{
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

const raylib::MyVector3 &raylib::Model::getRotation() const
{
    return this->_rotation;
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
    this->_model = raylib::Model::_loaderManager->load({path.data(), this->_texturePath.data()});
    this->_model.transform = MatrixRotateXYZ(MyVector3::makeVector3(MyVector3(DEG2RAD * pitch, DEG2RAD * yam, DEG2RAD * roll)));
}

void raylib::Model::setTexture(const std::string &texturePath)
{
    char **filenames = nullptr;
    int count = 0;
    std::string workingDirectory = GetWorkingDirectory();
    std::vector<std::string> vectorOfFilenames = {};

    _textures.clear();
    _texturePath = texturePath;
    if (texturePath.compare("") != 0) {
        if (DirectoryExists(texturePath.data())) {
            filenames = GetDirectoryFiles(_texturePath.data(), &count);
            ChangeDirectory(_texturePath.data());
            for (size_t i = 0; i < (size_t) count; i++)
                vectorOfFilenames.push_back(filenames[i]);
            std::sort(vectorOfFilenames.begin(), vectorOfFilenames.end());
            for (size_t i = 0; i < (size_t) count; i++) {
                if (!DirectoryExists(vectorOfFilenames[i].data()))
                    _textures.push_back(raylib::Texture::_loaderManager->load(vectorOfFilenames[i]));
            }
            ClearDirectoryFiles();
            ChangeDirectory(workingDirectory.data());
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

void raylib::Model::setLoaderManager()
{
    if (!this->_loaderManager) {
        this->_loaderManager = std::make_shared<raylib::LoaderManager<RModel, std::tuple<std::string, std::string>, tuple_hash>>(
            raylib::Model::myModelLoad, raylib::Model::myModelUnload, raylib::Model::myModelUnique);
    } else {
        this->_loaderManager.reset();
        this->_loaderManager = std::make_shared<raylib::LoaderManager<RModel, std::tuple<std::string, std::string>, tuple_hash>>(
            raylib::Model::myModelLoad, raylib::Model::myModelUnload, raylib::Model::myModelUnique);
    }
}

RModel raylib::Model::myModelLoad(const std::tuple<std::string, std::string> &str)
{
    return LoadModel(std::get<0>(str).data());
}

void raylib::Model::myModelUnload(RModel &model)
{
    UnloadModel(model);
}

void raylib::Model::restartAnimation()
{
}

std::tuple<std::string, std::string> raylib::Model::myModelUnique(std::size_t forced)
{
    return {std::to_string(forced), std::to_string(forced)};
}