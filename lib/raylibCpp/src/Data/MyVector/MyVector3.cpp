/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** MyVector3.cpp
*/

#include "MyVector3.hpp"

using namespace raylib;

MyVector3::MyVector3()
{
    this->a = 0;
    this->b = 0;
    this->c = 0;
}

MyVector3::MyVector3(float a, float b, float c)
{
    this->a = a;
    this->b = b;
    this->c = c;
}

MyVector3::MyVector3(const MyVector3 &src)
{
    this->a = src.a;
    this->b = src.b;
    this->c = src.c;
}

MyVector3 operator+(MyVector3 const &first, MyVector3 const &second)
{
    return MyVector3(first.a + second.a, first.b + second.b, first.c + second.c);
}

MyVector3 operator-(MyVector3 const &first, MyVector3 const &second)
{
    return MyVector3(first.a - second.a, first.b - second.b, first.c - second.c);
}

MyVector3 operator*(MyVector3 const &first, MyVector3 const &second)
{
    return MyVector3(first.a * second.a, first.b * second.b, first.c * second.c);
}

MyVector3 operator/(MyVector3 const &first, MyVector3 const &second)
{
    float one = 0;
    float two = 0;
    float three = 0;

    if (second.a)
        one = first.a / second.a;
    if (second.b)
        two = first.b / second.b;
    if (second.c)
        two = first.c / second.c;
    return MyVector3(one, two, three);
}