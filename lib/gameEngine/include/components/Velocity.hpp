/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 27/05/2021 Velocity.hpp.h
*/

#ifndef VELOCITY_HPP
#define VELOCITY_HPP

namespace Engine
{
    struct Velocity : public Component<Velocity> {
        Velocity(float x, float y) : x(x), y(y) {}
        Velocity() : x(0), y(0) {}

        float x;
        float y;
    };
}

#endif // VELOCITY_HPP