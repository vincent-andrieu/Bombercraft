/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** ObjectRectangle.cpp
*/

#include "ObjectRectangle.hpp"

using namespace ObjectType;

ObjectRectangle::ObjectRectangle(MyVector2 origin, MyVector2 size) : _origin(origin), _size(size)
{
}

ObjectRectangle::~ObjectRectangle()
{
}

void ObjectRectangle::setRectangle(MyVector2 origin, MyVector2 size)
{
    this->_origin = origin;
    this->_size = size;
}

MyVector2 ObjectRectangle::getRectangleOrigin() const
{
    return this->_origin;
}

MyVector2 ObjectRectangle::getRectangleSize() const
{
    return this->_size;
}