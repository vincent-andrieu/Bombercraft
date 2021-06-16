/*
** EPITECH PROJECT, 2021
** Game
** File description:
** Matrix.hpp
*/

#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "GameEngine.hpp"
#include "DataMatrix/DataMatrix.hpp"

namespace Component
{
    class Matrix2D : public Engine::Component<Matrix2D> {
        public:
            Matrix2D(std::pair<size_t, size_t> size);
            virtual ~Matrix2D() = default;

            const std::shared_ptr<DataMatrix> &getData() const;

            raylib::MyVector2 getMapSize() const;

            static raylib::MyVector3 getPositionAbs(size_t posx, size_t posy);
            static std::pair<size_t, size_t> getPositionRelativ(raylib::MyVector3 pos);
            static raylib::MyVector2 getMapIndex(raylib::MyVector3 pos);
            const std::pair<Engine::Entity, GUI::BlockFactory::BlockType> &getData(std::pair<size_t, size_t> pos) const;

        private:
            std::shared_ptr<DataMatrix> _data;
    };
}

#endif