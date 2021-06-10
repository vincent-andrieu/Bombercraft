/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** DataMatrix.cpp
*/

#include "DataMatrix.hpp"

DataMatrix::DataMatrix(std::pair<size_t, size_t> size)
{
    this->_matrix.reserve(size.second);
    for (size_t y = 0; y < size.second; y++)
        this->_matrix[y].reserve(size.first);
}

DataMatrix::~DataMatrix()
{
    this->_matrix.clear();
}

void DataMatrix::save(std::pair<size_t, size_t> pos, Engine::Entity entity, GUI::BlockFactory::BlockType category)
{
    if (pos.first > this->_size.first || pos.second > this->_size.second)
        throw std::out_of_range("Invalide pos");
    this->_matrix[pos.second][pos.first].first = entity;
    this->_matrix[pos.second][pos.first].second = category;
}

Engine::Entity DataMatrix::getEntity(std::pair<size_t, size_t> pos) const
{
    if (pos.first > this->_size.first || pos.second > this->_size.second)
        throw std::out_of_range("Invalide pos");
    return this->_matrix[pos.second][pos.first].first;
}

GUI::BlockFactory::BlockType DataMatrix::getCategory(std::pair<size_t, size_t> pos) const
{
    if (pos.first > this->_size.first || pos.second > this->_size.second)
        throw std::out_of_range("Invalide pos");
    return this->_matrix[pos.second][pos.first].second;
}

const std::pair<Engine::Entity, GUI::BlockFactory::BlockType> &DataMatrix::getBoth(std::pair<size_t, size_t> pos) const
{
    if (pos.first > this->_size.first || pos.second > this->_size.second)
        throw std::out_of_range("Invalide pos");
    return this->_matrix[pos.second][pos.first];
}