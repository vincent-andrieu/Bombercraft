/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** ObjectSphere.cpp
*/

#include "ObjectSphere.hpp"

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

bool ObjectSphere::checkCollisionWith(const ObjectSphere &sphere)
{
    return Collision::checkCollision(*this, sphere);
}

bool ObjectSphere::checkCollisionWith(const ObjectBox &box)
{
    return Collision::checkCollision(box, *this);
}