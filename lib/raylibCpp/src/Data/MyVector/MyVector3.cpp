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