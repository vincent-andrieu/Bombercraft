/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** ObjectLine.cpp
*/

#include "ObjectLine.hpp"

using namespace ObjectType;

ObjectLine::ObjectLine(MyVector2 a, MyVector2 b) : _a(a), _b(b)
{
}

ObjectLine::~ObjectLine()
{
}

void ObjectLine::setLine(MyVector2 a, MyVector2 b)
{
    this->_a = a;
    this->_b = b;
}

MyVector2 ObjectLine::getPointA() const
{
    return this->_a;
}

MyVector2 ObjectLine::getPointB() const
{
    return this->_b;
}