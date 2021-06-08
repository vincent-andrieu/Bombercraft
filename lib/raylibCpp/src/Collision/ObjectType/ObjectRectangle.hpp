/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** ObjectRectangle
*/

#ifndef OBJECTRECTANGLE_HPP
#define OBJECTRECTANGLE_HPP

#include "../Collision.hpp"
#include "../../Data/MyVector/MyVector2.hpp"
#include "../../../include/ICollidable.hpp"

#include <functional>

namespace raylib
{
    class ObjectCircle;
    class ObjectBox;
    class ObjectRectangle : public ICollidable {
      public:
        ObjectRectangle(const MyVector2 origin, const MyVector2 size);
        ~ObjectRectangle();
        void setRectangle(const MyVector2 origin, const MyVector2 size);
        MyVector2 getRectangleOrigin() const;
        MyVector2 getRectangleSize() const;
        bool checkCollisionWith(const ObjectCircle &circle);
        bool checkCollisionWith(const ObjectRectangle &rectangle);

        bool boxCollider(const ObjectBox &box);

      private:
        MyVector2 _origin;
        MyVector2 _size;
    };
}; // namespace raylib

#endif