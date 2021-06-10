/*
** EPITECH PROJECT, 2021
** AARender2D.cpp
** File description:
** Implementation abstract class to render 2D objects
*/

#include "ARender2D.hpp"

using namespace Component;

ARender2D::ARender2D(render2dMapModels const &models)
{
    for (auto [label, model] : models) {
        if (this->_modelIndex.find(label) != this->_modelIndex.end()) {
            throw std::invalid_argument("in ARender2D::ARender2D, Label index "
                                        "already exists");
        }
        std::size_t index = this->_models.size();
        this->_modelIndex[label] = index;
        this->_labelIndex[index] = label;
        this->_models.push_back(model);
    }
}

void ARender2D::add(std::shared_ptr<raylib::IRenderable> model, const std::string &label)
{
    if (this->_modelIndex.find(label) != this->_modelIndex.end()) {
        throw std::invalid_argument("in ARender2D::add, Label index already "
                                    "exists");
    }
    std::size_t index = this->_models.size();
    this->_modelIndex[label] = index;
    this->_labelIndex[index] = label;
    this->_models.push_back(model);
}

void ARender2D::remove(const std::string &label)
{
    if (this->_modelIndex.find(label) == this->_modelIndex.end()) {
        throw std::invalid_argument("in ARender2D::remove, undefined label "
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
    this->_labelIndex.erase(indexLast);
}

std::shared_ptr<raylib::IRenderable> &ARender2D::get(const std::string &label)
{
    if (this->_modelIndex.find(label) == this->_modelIndex.end()) {
        throw std::invalid_argument("in Render2D::get, Undefined label index");
    }
    return this->_models[_modelIndex[label]];
}