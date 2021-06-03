/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** MyVector4
*/

#ifndef MYVECTOR4_HPP
#define MYVECTOR4_HPP

#include "raylib.h"

#include "export.hpp"

namespace raylib
{
    class EXPORT MyVector4
    {
        public:
            MyVector4();
            MyVector4(const float a, const float b, const float c, const float d);
            MyVector4(const MyVector4 &src);

            static Vector4 makeVector4(const MyVector4 vector);

        public:
            float a;
            float b;
            float c;
            float d;
    };
    EXPORT MyVector4 operator+(MyVector4 const &first, MyVector4 const &second);
    EXPORT MyVector4 operator-(MyVector4 const &first, MyVector4 const &second);
    EXPORT MyVector4 operator*(MyVector4 const &first, MyVector4 const &second);
    EXPORT MyVector4 operator/(MyVector4 const &first, MyVector4 const &second);
    EXPORT bool operator==(MyVector4 const &first, MyVector4 const &second);
};

#endif