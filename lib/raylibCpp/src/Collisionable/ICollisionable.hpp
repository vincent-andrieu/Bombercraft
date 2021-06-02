/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** ICollisionable
*/

#ifndef ICOLLISIONABLE_HPP
#define ICOLLISIONABLE_HPP

namespace ObjectType
{
    class ObjectBox;
}

namespace raylib
{
    class ICollisionable
    {
        public :
            virtual ~ICollisionable() {};
            virtual bool boxCollider(const ObjectType::ObjectBox &box) = 0;
    };
};

#endif