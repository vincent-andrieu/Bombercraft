/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 02/06/2021 Render2D.cpp.cc
*/

#include "Render2D.hpp"

using namespace Component;

Render2D::Render2D(render2dMapModels const &models)
{
    for (auto [label, model] : models) {
        if (this->_modelIndex.find(label) != this->_modelIndex.end()) {
            throw std::invalid_argument("in Render2D::Render2D, Label index "
                                        "already exists");
        }
        std::size_t index = this->_models.size();
        this->_modelIndex[label] = index;
        this->_labelIndex[index] = label;
        this->_modelsToDrawIndex.insert(index);
        this->_models.push_back(model);
    }
}

void Render2D::draw()
{
    #ifdef __linux__
        for (auto &index : _modelsToDrawIndex) {
            _models.at(index)->draw();
        }
    #elif _WIN32
        for (auto it = _modelsToDrawIndex.rbegin(); it != _modelsToDrawIndex.rend();  it++ ) {
            _models.at(*it)->draw();
        }
    #endif
}

void Render2D::add(std::shared_ptr<raylib::IRenderable> model, const std::string &label)
{
    if (this->_modelIndex.find(label) != this->_modelIndex.end()) {
        throw std::invalid_argument("in Render2D::add, Label index already "
                                    "exists");
    }
    std::size_t index = this->_models.size();
    this->_modelIndex[label] = index;
    this->_labelIndex[index] = label;
    this->_modelsToDrawIndex.insert(index);

    this->_models.push_back(model);
}

void Render2D::remove(const std::string &label)
{
    if (this->_modelIndex.find(label) == this->_modelIndex.end()) {
        throw std::invalid_argument("in Render2D::remove, undefined label "
                                    "index");
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
    _modelsToDrawIndex.erase(index);
    this->_labelIndex.erase(indexLast);
}

std::shared_ptr<raylib::IRenderable> &Render2D::get(const std::string &label)
{
    if (this->_modelIndex.find(label) == this->_modelIndex.end()) {
        throw std::invalid_argument("in Render2D::get, Undefined label index");
    }
    return this->_models[_modelIndex[label]];
}

void Render2D::setToDrawFirst(const string &label)
{
    const auto &my_index(_modelIndex.at(label));

    #ifdef __linux__
        _modelsToDrawIndex.insert(_modelsToDrawIndex.begin(), my_index);
    #elif _WIN32
        _modelsToDrawIndex.insert(_modelsToDrawIndex.end(), my_index);
    #endif
}

void Render2D::setToDrawLast(const string &label)
{
    const auto &my_index(_modelIndex.at(label));

    #ifdef __linux__
        _modelsToDrawIndex.insert(_modelsToDrawIndex.end(), my_index);
    #elif _WIN32
        _modelsToDrawIndex.insert(_modelsToDrawIndex.begin(), my_index);
    #endif
}

void Render2D::unsetToDraw(const string &label)
{
    _modelsToDrawIndex.erase(_modelIndex.at(label));
}

// bool Render2D::save(Engine::SaveManager &saver) const
// {
//     if (!Component::save(saver))
//         return false;
//     try {
//         saver.createFile(COMP_SAVE_FILE);
//         saver.setWritingFile(COMP_SAVE_FILE);
//         //        saver.writeActFile(model); // TODO add overload function
//         saver.closeWritingFile();
//     } catch (const std::filesystem::filesystem_error &my_e) {
//         Engine::SaveManager::printException(my_e);
//         return false;
//     }
//     return true;
// }

// bool Render2D::load(Engine::SaveManager &saver)
// {
//     if (!Component::load(saver))
//         return false;
//     try {
//         saver.createFile(COMP_SAVE_FILE);
//         saver.setReadingFile(COMP_SAVE_FILE);
//         //        saver.readActFile(model); // TODO add overload function
//         saver.closeReadingFile();
//     } catch (const std::filesystem::filesystem_error &my_e) {
//         Engine::SaveManager::printException(my_e);
//         return false;
//     }
//     return true;
// }