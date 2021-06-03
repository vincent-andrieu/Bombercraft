/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** MyVector3
*/

#ifndef MYVECTOR3_HPP
#define MYVECTOR3_HPP

#include "raylib.h"

#include "export.hpp"

namespace raylib
{
    class EXPORT MyVector3
    {
        public:
            MyVector3();
            MyVector3(const float a, const float b, const float c);
            MyVector3(const MyVector3 &src);

            static Vector3 makeVector3(const MyVector3 vector);

        public:
            float a;
            float b;
            float c;
    };
    EXPORT MyVector3 operator+(MyVector3 const &first, MyVector3 const &second);
    EXPORT MyVector3 operator-(MyVector3 const &first, MyVector3 const &second);
    EXPORT MyVector3 operator*(MyVector3 const &first, MyVector3 const &second);
    EXPORT MyVector3 operator/(MyVector3 const &first, MyVector3 const &second);
    EXPORT bool operator==(MyVector3 const &first, MyVector3 const &second);
};

#endif