/*
** EPITECH PROJECT, 2021
** Game
** File description:
** Matrix.cpp
*/

#include "Matrix2D.hpp"

using namespace Component;

Matrix2D::Matrix2D(std::pair<size_t, size_t> size) : _data(std::make_unique<DataMatrix>(size))
{
}

const std::shared_ptr<DataMatrix> &Matrix2D::getData() const
{
    return this->_data;
}

const std::pair<Engine::Entity, GUI::BlockFactory::BlockType> &Matrix2D::getData(std::pair<size_t, size_t> pos) const
{
    return this->_data->getBoth(pos);
}

raylib::MyVector3 Matrix2D::getPositionAbs(size_t posx, size_t posy)
{
    const raylib::MyVector3 &size = Game::CoreData::settings->getMyVector3("STANDARD_BLOCK_SIZE");

    return raylib::MyVector3(posx / size.a, posy / size.b, 0 / size.c);
}