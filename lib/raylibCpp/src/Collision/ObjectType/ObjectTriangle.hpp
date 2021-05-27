/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** ObjectTriangle
*/

#ifndef OBJECTTRIANGLE_HPP
#define OBJECTTRIANGLE_HPP

#include "Data/MyVector/MyVector3.hpp"

using namespace raylib;

namespace ObjectType
{
    class ObjectTriangle
    {
        public:
            ObjectTriangle(MyVector3 triangle);
            ~ObjectTriangle();
            void setTriangle(MyVector3 triangle);
            MyVector3 getTriangle() const;

        private:
            MyVector3 _triangle;
    };
};

#endif