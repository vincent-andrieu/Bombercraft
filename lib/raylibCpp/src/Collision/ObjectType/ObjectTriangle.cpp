/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** ObjectTriangle.cpp
*/

#include "ObjectTriangle.hpp"

using namespace ObjectType;

ObjectTriangle::ObjectTriangle(const MyVector2 a, const MyVector2 b, const MyVector2 c) : _a(a), _b(b), _c(c)
{
}

ObjectTriangle::~ObjectTriangle()
{
}

void ObjectTriangle::setTriangle(const MyVector2 a, const MyVector2 b, const MyVector2 c)
{
    this->_a = a;
    this->_b = b;
    this->_c = c;
}

MyVector2 ObjectTriangle::getPointA() const
{
    return this->_a;
}

MyVector2 ObjectTriangle::getPointB() const
{
    return this->_b;
}

MyVector2 ObjectTriangle::getPointC() const
{
    return this->_c;
}