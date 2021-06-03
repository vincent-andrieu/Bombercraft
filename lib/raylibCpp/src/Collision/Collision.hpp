/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Collision
*/

#ifndef COLLISION_HPP
#define COLLISION_HPP

#include "ObjectType/ObjectBox.hpp"
#include "ObjectType/ObjectLine.hpp"
#include "ObjectType/ObjectCircle.hpp"
#include "ObjectType/ObjectSphere.hpp"
#include "ObjectType/ObjectTriangle.hpp"
#include "ObjectType/ObjectRectangle.hpp"
#include "raylib.h"

#include "export.hpp"

using namespace ObjectType;

namespace raylib
{
    class EXPORT Collision
    {
        public:
            // 2D
            static bool checkCollision(const ObjectLine &first, const ObjectLine &second);
            static bool checkCollision(const ObjectCircle &first, const ObjectCircle &second);
            static bool checkCollision(const ObjectCircle &circle, const ObjectRectangle &rect);
            static bool checkCollision(const ObjectRectangle &first, const ObjectRectangle &second);

            // 3D
            static bool checkCollision(const ObjectSphere &first, const ObjectSphere &second);
            static bool checkCollision(const ObjectBox &first, const ObjectBox &second);
            static bool checkCollision(const ObjectBox &box, const ObjectSphere &sphere);
        
        private:
            static Rectangle convertObjectRegtangle(const ObjectRectangle &src);
            static Vector2 convertMyVector2(const MyVector2 &src);
            static Vector3 convertMyVector3(const MyVector3 &src);
    };
};

#endif