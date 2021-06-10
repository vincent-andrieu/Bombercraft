/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 02/06/2021 Render2D.cpp.cc
*/

#include "Render2D.hpp"

using namespace Component;

Render2D::Render2D(std::unordered_map<std::string, std::shared_ptr<raylib::IRenderable>> const &models)
{
    for (auto [label, model] : models) {
        if (this->_modelIndex.find(label) != this->_modelIndex.end()) {
            throw std::invalid_argument("in Render2D::Render2D, Label index already exist");
        }
        std::size_t index = this->_models.size();
        this->_modelIndex[label] = index;
        this->_labelIndex[index] = label;
        this->_models.push_back(model);
    }
}

void Render2D::add(std::shared_ptr<raylib::IRenderable> model, const std::string &label)
{
    if (this->_modelIndex.find(label) != this->_modelIndex.end()) {
        throw std::invalid_argument("in Render2D::add, Label index already exist");
    }
    std::size_t index = this->_models.size();
    this->_modelIndex[label] = index;
    this->_labelIndex[index] = label;
    this->_models.push_back(model);
}

void Render2D::remove(const std::string &label)
{
    if (this->_modelIndex.find(label) == this->_modelIndex.end()) {
        throw std::invalid_argument("in Render2D::remove, Undefined label index");
    }
    std::size_t index = this->_modelIndex[label];
    this->_modelIndex.erase(label);

    std::size_t indexLast = _models.size() - 1;
    std::string labelLast = this->_labelIndex[indexLast];
    if (index != indexLast) {
        this->_models[index] = this->_models.back();
        this->_modelIndex[labelLast] = index;
        this->_labelIndex[index] = labelLast;
    } else {
        this->_models.pop_back();
    }
    this->_labelIndex.erase(indexLast);
}

void Render2D::draw()
{
    for (auto &model : _models) {
        model->draw();
    }
}

std::shared_ptr<raylib::IRenderable> &Render2D::get(const std::string &label)
{
    if (this->_modelIndex.find(label) == this->_modelIndex.end()) {
        throw std::invalid_argument("in Render2D::get, Undefined label index");
    }
    return this->_models[_modelIndex[label]];
}

bool Render2D::save(Engine::SaveManager &saver) const
{
    if (!Component::save(saver))
        return false;
    try {
        saver.createFile(COMP_SAVE_FILE);
        saver.setWritingFile(COMP_SAVE_FILE);
        //        saver.writeActFile(modele); // TODO add overload function
        saver.closeWritingFile();
    } catch (const std::filesystem::filesystem_error &my_e) {
        Engine::SaveManager::printException(my_e);
        return false;
    }
    return true;
}
bool Render2D::load(Engine::SaveManager &saver)
{
    if (!Component::load(saver))
        return false;
    try {
        saver.createFile(COMP_SAVE_FILE);
        saver.setReadingFile(COMP_SAVE_FILE);
        //        saver.readActFile(modele); // TODO add overload function
        saver.closeReadingFile();
    } catch (const std::filesystem::filesystem_error &my_e) {
        Engine::SaveManager::printException(my_e);
        return false;
    }
    return true;
}