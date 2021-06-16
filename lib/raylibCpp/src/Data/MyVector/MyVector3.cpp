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

MyVector3::MyVector3(const float a, const float b, const float c)
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

Vector3 MyVector3::makeVector3(const MyVector3 vector)
{
    Vector3 v = {0};

    v.x = vector.a;
    v.y = vector.b;
    v.z = vector.c;
    return v;
}

MyVector3 &MyVector3::operator=(const MyVector3 &other)
{
    this->a = other.a;
    this->b = other.b;
    this->c = other.c;
    return *this;
}

MyVector3 raylib::operator+(MyVector3 const &first, MyVector3 const &second)
{
    return MyVector3(first.a + second.a, first.b + second.b, first.c + second.c);
}

MyVector3 raylib::operator-(MyVector3 const &first, MyVector3 const &second)
{
    return MyVector3(first.a - second.a, first.b - second.b, first.c - second.c);
}

MyVector3 raylib::operator*(MyVector3 const &first, MyVector3 const &second)
{
    return MyVector3(first.a * second.a, first.b * second.b, first.c * second.c);
}

MyVector3 raylib::operator/(MyVector3 const &first, MyVector3 const &second)
{
    float one = 0;
    float two = 0;
    float three = 0;

    if (second.a)
        one = first.a / second.a;
    if (second.b)
        two = first.b / second.b;
    if (second.c)
        three = first.c / second.c;
    return MyVector3(one, two, three);
}

bool raylib::operator==(MyVector3 const &first, MyVector3 const &second)
{
    const bool a = first.a == second.a;
    const bool b = first.b == second.b;
    const bool c = first.c == second.c;

    return a && b && c;
}

std::ostream &raylib::operator<<(std::ostream &stream, MyVector3 const &vector)
{
    stream << "a: " << vector.a << ", b: " << vector.b << ", c: " << vector.c;

    return stream;
}