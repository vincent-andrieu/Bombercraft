/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** ObjectCircle.cpp
*/

#include "ObjectCircle.hpp"

ObjectCircle::ObjectCircle(const MyVector2 center, const float radius) : _center(center), _radius(radius)
{
}

ObjectCircle::~ObjectCircle()
{
}

void ObjectCircle::setCircle(const MyVector2 center, const float radius)
{
    this->_center = center;
    this->_radius = radius;
}

MyVector2 ObjectCircle::getCircleCenter() const
{
    return this->_center;
}

float ObjectCircle::getCircleRadius() const
{
    return this->_radius;
}

bool ObjectCircle::checkCollisionWith(const ObjectCircle &circle)
{
    return Collision::checkCollision(*this, circle);
}

bool ObjectCircle::checkCollisionWith(const ObjectRectangle &rectangle)
{
    return Collision::checkCollision(*this, rectangle);
}

bool ObjectCircle::boxCollider(const ObjectType::ObjectBox &box)
{
    //return this->checkCollisionWith(box);
    (void) box;
    throw std::bad_function_call();
    return false;
}