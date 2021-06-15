/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** DataMatrix.hpp
*/

#ifndef DATAMATRIX_HPP
#define DATAMATRIX_HPP

#include "EntityPack/EntityPack.hpp"
#include "Game/Factories/Block/BlockFactory.hpp"

class DataMatrix
{
    public:
        DataMatrix(std::pair<size_t, size_t> size);
        ~DataMatrix();
        void save(std::pair<size_t, size_t> pos, Engine::Entity entity, GUI::BlockFactory::BlockType category);
        Engine::Entity getEntity(std::pair<size_t, size_t> pos) const;
        GUI::BlockFactory::BlockType getCategory(std::pair<size_t, size_t> pos) const;
        const std::pair<Engine::Entity, GUI::BlockFactory::BlockType> &getBoth(std::pair<size_t, size_t> pos) const;

    private:
        std::pair<size_t, size_t> _size;
        std::vector<std::vector<std::pair<Engine::Entity, GUI::BlockFactory::BlockType>>> _matrix;
};

#endif