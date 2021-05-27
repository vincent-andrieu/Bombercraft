/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** ObjectLine
*/

#ifndef OBJECTLINE_HPP
#define OBJECTLINE_HPP

#include "Data/MyVector/MyVector2.hpp"

using namespace raylib;

namespace ObjectType
{
    class ObjectLine
    {
        public:
            ObjectLine(MyVector2 a, MyVector2 b);
            ~ObjectLine();
            void setLine(MyVector2 a, MyVector2 b);
            MyVector2 getPointA() const;
            MyVector2 getPointB() const;

        private:
            MyVector2 _a;
            MyVector2 _b;
    };
};

#endif