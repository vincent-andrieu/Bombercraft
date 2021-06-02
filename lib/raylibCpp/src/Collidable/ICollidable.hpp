/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** ICollidable
*/

#ifndef ICOLLIDABLE_HPP
#define ICOLLIDABLE_HPP

namespace ObjectType
{
    class ObjectBox;
}

namespace raylib
{
    class ICollidable
    {
        public :
            virtual ~ICollidable() {};
            virtual bool boxCollider(const ObjectType::ObjectBox &box) = 0;
    };
};

#endif