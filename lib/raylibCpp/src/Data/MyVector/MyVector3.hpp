/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** MyVector3
*/

#ifndef MYVECTOR3_HPP
#define MYVECTOR3_HPP

#include <fstream>
#include "raylib.h"

namespace raylib
{
    class MyVector3 {
      public:
        MyVector3();
        MyVector3(const float a, const float b, const float c = 0);
        MyVector3(const MyVector3 &src);

        static Vector3 makeVector3(const MyVector3 vector);
        MyVector3 &operator=(const MyVector3 &other);

      public:
        float a;
        float b;
        float c;
    };
    MyVector3 operator+(MyVector3 const &first, MyVector3 const &second);
    MyVector3 operator-(MyVector3 const &first, MyVector3 const &second);
    MyVector3 operator*(MyVector3 const &first, MyVector3 const &second);
    MyVector3 operator/(MyVector3 const &first, MyVector3 const &second);
    MyVector3 operator/(MyVector3 const &first, float second);
    bool operator==(MyVector3 const &first, MyVector3 const &second);
    bool operator!=(MyVector3 const &first, MyVector3 const &second);
    std::ostream &operator<<(std::ostream &stream, MyVector3 const &vector);
}; // namespace raylib

#endif