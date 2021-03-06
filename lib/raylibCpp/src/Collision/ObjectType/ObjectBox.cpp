/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** ObjectBox.cpp
*/

#include "ObjectBox.hpp"

using namespace raylib;

ObjectBox::ObjectBox(const MyVector3 origin, const MyVector3 size) : _origin(origin), _size(size)
{
}

ObjectBox::~ObjectBox()
{
}

void ObjectBox::setSphere(const MyVector3 origin, const MyVector3 size)
{
    this->_origin = origin;
    this->_size = size;
}

void ObjectBox::setOrigin(const MyVector3 origin)
{
    this->_origin = origin;
}

MyVector3 ObjectBox::getBoxOrigin() const
{
    return this->_origin;
}

MyVector3 ObjectBox::getBoxSize() const
{
    return this->_size;
}

bool ObjectBox::checkCollisionWith(const ObjectBox &box)
{
    return Collision::checkCollision(*this, box);
}

bool ObjectBox::checkCollisionWith(const ObjectSphere &sphere)
{
    return Collision::checkCollision(*this, sphere);
}

bool ObjectBox::boxCollider(const ObjectBox &box)
{
    return this->checkCollisionWith(box);
}