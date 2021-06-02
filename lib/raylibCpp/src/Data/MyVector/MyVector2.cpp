/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** MyVector2.cpp
*/

#include "MyVector2.hpp"

using namespace raylib;

MyVector2::MyVector2()
{
    this->a = 0;
    this->b = 0;
}

MyVector2::MyVector2(const float a, const float b)
{
    this->a = a;
    this->b = b;
}

MyVector2::MyVector2(const MyVector2 &src)
{
    this->a = src.a;
    this->b = src.b;
}

MyVector2 raylib::operator+(MyVector2 const &first, MyVector2 const &second)
{
    return MyVector2(first.a + second.a, first.b + second.b);
}

MyVector2 raylib::operator-(MyVector2 const &first, MyVector2 const &second)
{
    return MyVector2(first.a - second.a, first.b - second.b);
}

MyVector2 raylib::operator*(MyVector2 const &first, MyVector2 const &second)
{
    return MyVector2(first.a * second.a, first.b * second.b);
}

MyVector2 raylib::operator/(MyVector2 const &first, MyVector2 const &second)
{
    float one = 0;
    float two = 0;

    if (second.a)
        one = first.a / second.a;
    if (second.b)
        two = first.b / second.b;
    return MyVector2(one, two);
}

bool raylib::operator==(MyVector2 const &first, MyVector2 const &second)
{
    bool a = first.a == second.a;
    bool b = first.b == second.b;

    return a && b;
}