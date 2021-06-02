/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** ObjectBox
*/

#ifndef OBJECTBOX_HPP
#define OBJECTBOX_HPP

#include "../Collision.hpp"
#include "../../Data/MyVector/MyVector3.hpp"

using namespace raylib;

namespace ObjectType
{
    class ObjectSphere;
    class ObjectBox
    {
        public:
            ObjectBox(const MyVector3 origin, const MyVector3 size);
            ~ObjectBox();
            void setSphere(const MyVector3 origin, const MyVector3 size);
            MyVector3 getBoxOrigin() const;
            MyVector3 getBoxSize() const;
            bool checkCollisionWith(const ObjectBox &box);
            bool checkCollisionWith(const ObjectSphere &sphere);

        private:
            MyVector3 _origin;
            MyVector3 _size;
    };
};

#endif