/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** ObjectSphere
*/

#ifndef OBJECTSPHERE_HPP
#define OBJECTSPHERE_HPP

#include "../Collision.hpp"
#include "../../Data/MyVector/MyVector3.hpp"
#include "../../../include/ICollidable.hpp"

namespace raylib
{
    class ObjectBox;
    class ObjectSphere : public ICollidable {
      public:
        ObjectSphere(const MyVector3 center, const float radius);
        ~ObjectSphere();
        void setSphere(const MyVector3 center, const float radius);
        MyVector3 getSphereCenter() const;
        float getSphereRadius() const;
        bool checkCollisionWith(const ObjectSphere &sphere);
        bool checkCollisionWith(const ObjectBox &box);

        bool boxCollider(const ObjectBox &box);

      private:
        MyVector3 _center;
        float _radius;
    };
}; // namespace raylib

#endif