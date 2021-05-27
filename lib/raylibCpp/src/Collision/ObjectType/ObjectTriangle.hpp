/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** ObjectTriangle
*/

#ifndef OBJECTTRIANGLE_HPP
#define OBJECTTRIANGLE_HPP

#include "Data/MyVector/MyVector2.hpp"

using namespace raylib;

namespace ObjectType
{
    class ObjectTriangle
    {
        public:
            ObjectTriangle(MyVector2 a, MyVector2 b, MyVector2 c);
            ~ObjectTriangle();
            void setTriangle(MyVector2 a, MyVector2 b, MyVector2 c);
            MyVector2 getPointA() const;
            MyVector2 getPointB() const;
            MyVector2 getPointC() const;

        private:
            MyVector2 _a;
            MyVector2 _b;
            MyVector2 _c;
    };
};

#endif