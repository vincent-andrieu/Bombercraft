/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** ObjectRectangle
*/

#ifndef OBJECTRECTANGLE_HPP
#define OBJECTRECTANGLE_HPP

#include "Data/MyVector/MyVector2.hpp"

using namespace raylib;

namespace ObjectType
{
    class ObjectRectangle
    {
        public:
            ObjectRectangle(MyVector2 origin, MyVector2 size);
            ~ObjectRectangle();
            void setRectangle(MyVector2 origin, MyVector2 size);
            MyVector2 getRectangleOrigin() const;
            MyVector2 getRectangleSize() const;

        private:
            MyVector2 _origin;
            MyVector2 _size;
    };
};

#endif