/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 15/06/2021 ModelList.cpp.cc
*/

#include "ModelList.hpp"

using namespace Component;

Component::ModelList::ModelList(const std::unordered_map<std::string, std::shared_ptr<raylib::IModel>> &models)
{
    if (models.empty()) {
        throw std::invalid_argument("ModelList::ModelList Empty model list.");
    }
    for (auto &pair : models) {
        _models.push_back(pair.second);
        _modelNames[pair.first] = _models.size() - 1;
    }
    _selected = _models.front();
}

void Component::ModelList::select(const std::string &label)
{
    auto it = _modelNames.find(label);

    if (it == _modelNames.end()) {
        throw std::invalid_argument("ModelList::select Unknown model label.");
    }
    this->_selected = _models[it->second];
}

void Component::ModelList::draw()
{
    this->_selected->draw();
}

void Component::ModelList::setPosition(const raylib::MyVector3 position)
{
    for (auto &model : _models) {
        model->setPosition(position);
    }
}

void Component::ModelList::setRotation(const raylib::MyVector3 rotation)
{
    for (auto &model : _models) {
        model->setRotation(rotation);
    }
}

void ModelList::setTexture(const std::string &path)
{
    for (auto &model : _models) {
        model->setTexture(path);
    }
}
