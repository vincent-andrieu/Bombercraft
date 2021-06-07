/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** ObjectLine
*/

#ifndef OBJECTLINE_HPP
#define OBJECTLINE_HPP

#include "../Collision.hpp"
#include "../../Data/MyVector/MyVector2.hpp"
#include "../../../include/ICollidable.hpp"

#include <functional>

namespace raylib
{
    class ObjectBox;
    class ObjectLine : public ICollidable {
      public:
        ObjectLine(const MyVector2 a, const MyVector2 b);
        ~ObjectLine();
        void setLine(const MyVector2 a, const MyVector2 b);
        MyVector2 getPointA() const;
        MyVector2 getPointB() const;
        bool checkCollisionWith(const ObjectLine &line);

        bool boxCollider(const ObjectBox &box);

      private:
        MyVector2 _a;
        MyVector2 _b;
    };
}; // namespace raylib

#endif