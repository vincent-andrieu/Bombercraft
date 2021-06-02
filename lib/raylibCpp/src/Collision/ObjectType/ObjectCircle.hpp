/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** ObjectCircle
*/

#ifndef OBJECTCIRCLE_HPP
#define OBJECTCIRCLE_HPP

#include "../Collision.hpp"
#include "../../Data/MyVector/MyVector2.hpp"

using namespace raylib;

namespace ObjectType
{
    class ObjectRectangle;
    class ObjectCircle
    {
        public:
            ObjectCircle(const MyVector2 center, const float radius);
            ~ObjectCircle();
            void setCircle(const MyVector2 center, const float radius);
            MyVector2 getCircleCenter() const;
            float getCircleRadius() const;
            bool checkCollisionWith(const ObjectCircle &circle);
            bool checkCollisionWith(const ObjectRectangle &rectangle);

        private:
            MyVector2 _center;
            float _radius;
    };
};

#endif