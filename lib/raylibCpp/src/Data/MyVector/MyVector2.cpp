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

MyVector2::MyVector2(float a, float b)
{
    this->a = a;
    this->b = b;
}

MyVector2::MyVector2(const MyVector2 &src)
{
    this->a = src.a;
    this->b = src.b;
}