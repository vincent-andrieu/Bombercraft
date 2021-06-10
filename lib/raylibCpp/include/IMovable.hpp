/*
 * EPITECH PROJECT, 2021
 * include
 * File description:
 * IMovable.hpp - Created: 10/06/2021
 */

#ifndef IMOVABLE_HPP
#define IMOVABLE_HPP

namespace raylib
{
    class MyVector2;

    class IMovable {
      public:
        virtual ~IMovable() = default;

        virtual void setPosition(const MyVector3 position) = 0;
        virtual const MyVector3 &getPosition() const = 0;
    };
}; // namespace raylib

#endif