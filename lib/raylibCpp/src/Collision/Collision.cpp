/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Collision.cpp
*/

#include "Collision.hpp"

using namespace raylib;

// 2D
bool Collision::checkCollision(const ObjectRectangle &first, const ObjectRectangle &second)
{
    return CheckCollisionRecs(Collision::convertObjectRegtangle(first), Collision::convertObjectRegtangle(second));
}

bool Collision::checkCollision(const ObjectCircle &first, const ObjectCircle &second)
{
    return CheckCollisionCircles(Collision::convertMyVector2(first.getCircleCenter()), first.getCircleRadius(),
    Collision::convertMyVector2(second.getCircleCenter()), second.getCircleRadius());
}

bool Collision::checkCollision(const ObjectLine &first, const ObjectLine &second)
{
    return CheckCollisionLines(Collision::convertMyVector2(first.getPointA()), Collision::convertMyVector2(first.getPointB()),
    Collision::convertMyVector2(second.getPointA()), Collision::convertMyVector2(second.getPointB()), nullptr);
}

bool Collision::checkCollision(const ObjectCircle &circle, const ObjectRectangle &rect)
{
    return CheckCollisionCircleRec(Collision::convertMyVector2(circle.getCircleCenter()), circle.getCircleRadius(), Collision::convertObjectRegtangle(rect));
}

// 3D
bool Collision::checkCollision(const ObjectSphere &first, const ObjectSphere &second)
{
    return CheckCollisionSpheres(Collision::convertMyVector3(first.getSphereCenter()), first.getSphereRadius(),
    Collision::convertMyVector3(second.getSphereCenter()), second.getSphereRadius());
}

bool Collision::checkCollision(const ObjectBox &first, const ObjectBox &second)
{
    Vector3 origin_f = Collision::convertMyVector3(first.getBoxOrigin());
    Vector3 end_f = Collision::convertMyVector3(first.getBoxOrigin() + first.getBoxSize());
    Vector3 origin_s = Collision::convertMyVector3(second.getBoxOrigin());
    Vector3 end_s = Collision::convertMyVector3(second.getBoxOrigin() + second.getBoxSize());
    BoundingBox box_f = {origin_f, end_f};
    BoundingBox box_s = {origin_s, end_s};

    return CheckCollisionBoxes(box_f, box_s);
}

bool Collision::checkCollision(const ObjectBox &box, const ObjectSphere &sphere)
{
    Vector3 origin = Collision::convertMyVector3(box.getBoxOrigin());
    Vector3 end = Collision::convertMyVector3(box.getBoxOrigin() + box.getBoxSize());
    BoundingBox box_bb = {origin, end};

    return CheckCollisionBoxSphere(box_bb, Collision::convertMyVector3(sphere.getSphereCenter()), sphere.getSphereRadius());
}

Rectangle Collision::convertObjectRegtangle(const ObjectRectangle &src)
{
    MyVector2 origin = src.getRectangleOrigin();
    MyVector2 size = src.getRectangleSize();

    return {origin.a, origin.b, size.a, size.b};
}

Vector2 Collision::convertMyVector2(const MyVector2 &src)
{
    return {src.a, src.b};
}

Vector3 Collision::convertMyVector3(const MyVector3 &src)
{
    return {src.a, src.b, src.c};
}