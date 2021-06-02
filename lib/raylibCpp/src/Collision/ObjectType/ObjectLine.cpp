/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** ObjectLine.cpp
*/

#include "ObjectLine.hpp"

ObjectLine::ObjectLine(const MyVector2 a, const MyVector2 b) : _a(a), _b(b)
{
}

ObjectLine::~ObjectLine()
{
}

void ObjectLine::setLine(const MyVector2 a, const MyVector2 b)
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

bool ObjectLine::checkCollisionWith(const ObjectLine &line)
{
    return Collision::checkCollision(*this, line);
}

bool ObjectLine::boxCollider(const ObjectType::ObjectBox &box)
{
    //return this->checkCollisionWith(box);
    (void) box;
    throw std::bad_function_call();
    return false;
}