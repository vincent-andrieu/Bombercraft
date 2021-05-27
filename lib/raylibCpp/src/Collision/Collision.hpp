/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Collision
*/

#ifndef COLLISION_HPP
#define COLLISION_HPP

#include "ICollision.hpp"
#include "raylib.h"

namespace raylib
{
    class Collision : public ICollision
    {
        public:
            Collision();
            ~Collision();

            // 2D
            bool checkCollision(const ObjectRectangle &first, const ObjectRectangle &second) const;
            bool checkCollision(const ObjectCircle &first, const ObjectCircle &second) const;
            bool checkCollision(const ObjectLine &first, const ObjectLine &second) const;
            bool checkCollision(const ObjectCircle &circle, const ObjectRectangle &rect) const;

            // 3D
            bool checkCollision(const ObjectSphere &first, const ObjectSphere &second) const;
            bool checkCollision(const ObjectBox &first, const ObjectBox &second) const;
            bool checkCollision(const ObjectBox &box, const ObjectSphere &sphere) const;
        
        private:
            Rectangle convertObjectRegtangle(const ObjectRectangle &src) const;
            Vector2 convertMyVector2(const MyVector2 &src) const;
            Vector3 convertMyVector3(const MyVector3 &src) const;
    };
};

#endif