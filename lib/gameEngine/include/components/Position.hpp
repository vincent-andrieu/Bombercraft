/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 27/05/2021 Position.hpp.h
*/

#ifndef POSITION_HPP
#define POSITION_HPP

#include "Component/Component.hpp"

namespace Engine
{
    struct Position : public Component<Position> {
        Position(float x, float y) : x(x), y(y) {}
        Position() : x(0), y(0) {}

        float x;
        float y;
    };
}

#endif // POSITION_HPP
