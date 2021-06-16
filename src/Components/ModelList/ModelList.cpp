/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 15/06/2021 ModelList.cpp.cc
*/

#include "ModelList.hpp"

using namespace Component;

Component::ModelList::ModelList(
    const std::unordered_map<std::string, std::shared_ptr<raylib::IModel>> &models, std::string const &firstModel)
{
    if (models.empty()) {
        throw std::invalid_argument("ModelList::ModelList Empty model list.");
    }
    for (auto &pair : models) {
        _models.push_back(pair.second);
        _modelNames[pair.first] = _models.size() - 1;
    }
    this->select(firstModel);
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
        this->_prevPosition = model->getPosition();
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
const raylib::MyVector3 &ModelList::getPosition() const
{
    return _selected->getPosition();
}

void ModelList::setScale(const float scale)
{
    for (auto &model : _models) {
        model->setScale(scale);
    }
}

void ModelList::resetPosition(bool x, bool z)
{
    raylib::MyVector3 pos = this->getPosition();

    if (x) {
        pos.a = _prevPosition.a;
    }
    if (z) {
        pos.c = _prevPosition.c;
    }
    this->setPosition(pos);
}
