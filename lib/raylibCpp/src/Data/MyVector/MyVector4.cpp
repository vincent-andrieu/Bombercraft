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