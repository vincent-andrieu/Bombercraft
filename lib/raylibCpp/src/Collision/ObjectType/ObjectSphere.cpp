/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** ObjectSphere.cpp
*/

#include "ObjectSphere.hpp"

using namespace ObjectType;

ObjectSphere::ObjectSphere(MyVector3 center, float radius) : _center(center), _radius(radius)
{
}

ObjectSphere::~ObjectSphere()
{
}

void ObjectSphere::setSphere(MyVector3 center, float radius)
{
    this->_center = center;
    this->_radius = radius;
}

MyVector3 ObjectSphere::getSphereCenter() const
{
    return this->_center;
}

float ObjectSphere::getSphereRadius() const
{
    return this->_radius;
}