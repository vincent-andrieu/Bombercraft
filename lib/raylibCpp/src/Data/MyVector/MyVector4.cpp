/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** MyVector4.cpp
*/

#include "MyVector4.hpp"

using namespace raylib;

MyVector4::MyVector4()
{
    this->a = 0;
    this->b = 0;
    this->c = 0;
    this->d = 0;
}

MyVector4::MyVector4(float a, float b, float c, float d)
{
    this->a = a;
    this->b = b;
    this->c = c;
    this->d = d;
}

MyVector4::MyVector4(const MyVector4 &src)
{
    this->a = src.a;
    this->b = src.b;
    this->c = src.c;
    this->d = src.d;
}

MyVector4 operator+(MyVector4 const &first, MyVector4 const &second)
{
    return MyVector4(first.a + second.a, first.b + second.b, first.c + second.c, first.d + second.d);
}

MyVector4 operator-(MyVector4 const &first, MyVector4 const &second)
{
    return MyVector4(first.a - second.a, first.b - second.b, first.c - second.c, first.d - second.d);
}

MyVector4 operator*(MyVector4 const &first, MyVector4 const &second)
{
    return MyVector4(first.a * second.a, first.b * second.b, first.c * second.c, first.d * second.d);
}

MyVector4 operator/(MyVector4 const &first, MyVector4 const &second)
{
    float one = 0;
    float two = 0;
    float three = 0;
    float four = 0;

    if (second.a)
        one = first.a / second.a;
    if (second.b)
        two = first.b / second.b;
    if (second.c)
        two = first.c / second.c;
    if (second.d)
        two = first.d / second.d;
    return MyVector4(one, two, three, four);
}

bool operator==(MyVector4 const &first, MyVector4 const &second)
{
    bool a = first.a == second.a;
    bool b = first.b == second.b;
    bool c = first.c == second.c;
    bool d = first.d == second.d;

    return a && b && c && d;
}