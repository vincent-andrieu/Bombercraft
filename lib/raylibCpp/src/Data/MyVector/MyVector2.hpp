/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** MyVector2
*/

#ifndef MYVECTOR2_HPP
#define MYVECTOR2_HPP

#include "raylib.h"
#include "export.hpp"

namespace raylib
{
    class EXPORT MyVector2
    {
        public:
            MyVector2();
            MyVector2(const float a, const float b);
            MyVector2(const MyVector2 &src);

            static Vector2 makeVector2(const MyVector2 vector);

        public:
            float a;
            float b;
    };
    EXPORT MyVector2 operator+(MyVector2 const &first, MyVector2 const &second);
    EXPORT MyVector2 operator-(MyVector2 const &first, MyVector2 const &second);
    EXPORT MyVector2 operator*(MyVector2 const &first, MyVector2 const &second);
    EXPORT MyVector2 operator/(MyVector2 const &first, MyVector2 const &second);
    EXPORT bool operator==(MyVector2 const &first, MyVector2 const &second);
};

#endif