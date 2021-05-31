/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 27/05/2021 Position.hpp.h
*/

#ifndef POSITION_HPP
#define POSITION_HPP

#include "Component/Component.hpp"

struct Position : public Component<Position>
{
    float x;
    float y;
};

#endif // POSITION_HPP