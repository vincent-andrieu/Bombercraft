/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** ObjectSphere
*/

#ifndef OBJECTSPHERE_HPP
#define OBJECTSPHERE_HPP

#include "Data/MyVector/MyVector3.hpp"

using namespace raylib;

namespace ObjectType
{
    class ObjectSphere
    {
        public:
            ObjectSphere(MyVector3 center, float radius);
            ~ObjectSphere();
            void setSphere(MyVector3 center, float radius);
            MyVector3 getSphereCenter() const;
            float getSphereRadius() const;

        private:
            MyVector3 _center;
            float _radius;
    };
};

#endif