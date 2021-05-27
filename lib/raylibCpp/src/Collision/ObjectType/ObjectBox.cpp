/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** ObjectBox.cpp
*/

#include "ObjectBox.hpp"

using namespace ObjectType;

ObjectBox::ObjectBox(MyVector3 origin, MyVector3 size) : _origin(origin), _size(size)
{
}

ObjectBox::~ObjectBox()
{
}

void ObjectBox::setSphere(MyVector3 origin, MyVector3 size)
{
    this->_origin = origin;
    this->_size = size;
}

MyVector3 ObjectBox::getBoxOrigin() const
{
    return this->_origin;
}

MyVector3 ObjectBox::getBoxSize() const
{
    return this->_size;
}