/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** ICollision
*/

#ifndef ICOLLISION_HPP
#define ICOLLISION_HPP

#include "ObjectType/ObjectBox.hpp"
#include "ObjectType/ObjectLine.hpp"
#include "ObjectType/ObjectCircle.hpp"
#include "ObjectType/ObjectSphere.hpp"
#include "ObjectType/ObjectTriangle.hpp"
#include "ObjectType/ObjectRectangle.hpp"

using namespace ObjectType;

namespace raylib
{
    class ICollision
    {
        // 2D
        virtual bool checkCollision(const ObjectRectangle &first, const ObjectRectangle &second) const = 0;
        virtual bool checkCollision(const ObjectCircle &first, const ObjectCircle &second) const = 0;
        virtual bool checkCollision(const ObjectLine &first, const ObjectLine &second) const = 0;
        virtual bool checkCollision(const ObjectCircle &circle, const ObjectRectangle &rect) const = 0;

        // 3D
        virtual bool checkCollision(const ObjectSphere &first, const ObjectSphere &second) const = 0;
        virtual bool checkCollision(const ObjectBox &first, const ObjectBox &second) const = 0;
        virtual bool checkCollision(const ObjectBox &box, const ObjectSphere &sphere) const = 0;
        virtual bool checkCollision(const ObjectLine &line, const ObjectSphere &sphere) const = 0;
        virtual bool checkCollision(const ObjectLine &line, const ObjectBox &box) const = 0;
    };
};

#endif