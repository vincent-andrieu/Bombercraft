/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** ObjectCircle.cpp
*/

#include "ObjectCircle.hpp"

using namespace ObjectType;

ObjectCircle::ObjectCircle(MyVector2 center, float radius) : _center(center), _radius(radius)
{
}

ObjectCircle::~ObjectCircle()
{
}

void ObjectCircle::setCircle(MyVector2 center, float radius)
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