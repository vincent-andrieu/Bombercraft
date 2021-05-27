/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Collision.cpp
*/

#include "Collision.hpp"

using namespace raylib;

Collision::Collision()
{
}

Collision::~Collision()
{
}

// 2D
bool Collision::checkCollision(const ObjectRectangle &first, const ObjectRectangle &second) const
{
    return CheckCollisionRecs(this->convertObjectRegtangle(first), this->convertObjectRegtangle(second));
}

bool Collision::checkCollision(const ObjectCircle &first, const ObjectCircle &second) const
{
    return CheckCollisionCircles(this->convertMyVector2(first.getCircleCenter()), first.getCircleRadius(),
    this->convertMyVector2(second.getCircleCenter()), second.getCircleRadius());
}

bool Collision::checkCollision(const ObjectLine &first, const ObjectLine &second) const
{
    return CheckCollisionLines(this->convertMyVector2(first.getPointA()), this->convertMyVector2(first.getPointB()),
    this->convertMyVector2(second.getPointA()), this->convertMyVector2(second.getPointB()), nullptr);
}

bool Collision::checkCollision(const ObjectCircle &circle, const ObjectRectangle &rect) const
{
    return CheckCollisionCircleRec(this->convertMyVector2(circle.getCircleCenter()), circle.getCircleRadius(), this->convertObjectRegtangle(rect));
}

// 3D
bool Collision::checkCollision(const ObjectSphere &first, const ObjectSphere &second) const
{
    return CheckCollisionSpheres(this->convertMyVector3(first.getSphereCenter()), first.getSphereRadius(),
    this->convertMyVector3(second.getSphereCenter()), second.getSphereRadius());
}

bool Collision::checkCollision(const ObjectBox &first, const ObjectBox &second) const
{
    Vector3 origin_f = this->convertMyVector3(first.getBoxOrigin());
    Vector3 end_f = this->convertMyVector3(first.getBoxOrigin() + first.getBoxSize());
    Vector3 origin_s = this->convertMyVector3(second.getBoxOrigin());
    Vector3 end_s = this->convertMyVector3(second.getBoxOrigin() + second.getBoxSize());
    BoundingBox box_f = {origin_f, end_f};
    BoundingBox box_s = {origin_s, end_s};

    return CheckCollisionBoxes(box_f, box_s);
}

bool Collision::checkCollision(const ObjectBox &box, const ObjectSphere &sphere) const
{
    Vector3 origin = this->convertMyVector3(box.getBoxOrigin());
    Vector3 end = this->convertMyVector3(box.getBoxOrigin() + box.getBoxSize());
    BoundingBox box_bb = {origin, end};

    return CheckCollisionBoxSphere(box_bb, this->convertMyVector3(sphere.getSphereCenter()), sphere.getSphereRadius());
}

Rectangle Collision::convertObjectRegtangle(const ObjectRectangle &src) const
{
    MyVector2 origin = src.getRectangleOrigin();
    MyVector2 size = src.getRectangleSize();

    return {origin.a, origin.b, size.a, size.b};
}

Vector2 Collision::convertMyVector2(const MyVector2 &src) const
{
    return {src.a, src.b};
}

Vector3 Collision::convertMyVector3(const MyVector3 &src) const
{
    return {src.a, src.b, src.c};
}