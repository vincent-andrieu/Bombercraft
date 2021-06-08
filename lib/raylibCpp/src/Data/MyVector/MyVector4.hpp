/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** MyVector4
*/

#ifndef MYVECTOR4_HPP
#define MYVECTOR4_HPP

#include "raylib.h"

namespace raylib
{
    class MyVector4
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
    MyVector4 operator+(MyVector4 const &first, MyVector4 const &second);
    MyVector4 operator-(MyVector4 const &first, MyVector4 const &second);
    MyVector4 operator*(MyVector4 const &first, MyVector4 const &second);
    MyVector4 operator/(MyVector4 const &first, MyVector4 const &second);
    bool operator==(MyVector4 const &first, MyVector4 const &second);
};

#endif