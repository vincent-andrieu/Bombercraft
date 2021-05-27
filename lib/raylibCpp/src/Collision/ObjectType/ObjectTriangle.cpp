/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** ObjectTriangle.cpp
*/

#include "ObjectTriangle.hpp"

using namespace ObjectType;

ObjectTriangle::ObjectTriangle(MyVector3 triangle) : _triangle(triangle)
{
}

ObjectTriangle::~ObjectTriangle()
{
}

void ObjectTriangle::setTriangle(MyVector3 triangle)
{
    this->_triangle = triangle;
}

MyVector3 ObjectTriangle::getTriangle() const
{
    return this->_triangle;
}