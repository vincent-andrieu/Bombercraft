/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** MyVector2
*/

#ifndef MYVECTOR2_HPP
#define MYVECTOR2_HPP

#include <fstream>
#include "raylib.h"

namespace raylib
{
    class MyVector2 {
      public:
        MyVector2();
        MyVector2(const float a, const float b);
        MyVector2(const MyVector2 &src);

        MyVector2 &operator=(MyVector2 const &src);

        static Vector2 makeVector2(const MyVector2 vector);

      public:
        float a;
        float b;
    };
    MyVector2 operator+(MyVector2 const &first, MyVector2 const &second);
    MyVector2 operator-(MyVector2 const &first, MyVector2 const &second);
    MyVector2 operator*(MyVector2 const &first, MyVector2 const &second);
    MyVector2 operator*(const float first, MyVector2 const &second);
    MyVector2 operator*(MyVector2 const &first, const float second);
    MyVector2 operator/(MyVector2 const &first, MyVector2 const &second);
    MyVector2 operator/(MyVector2 const &first, const float second);
    MyVector2 operator/(const float first, MyVector2 const &second);
    bool operator==(MyVector2 const &first, MyVector2 const &second);
    std::ostream &operator<<(std::ostream &stream, MyVector2 const &vector);
}; // namespace raylib

#endif