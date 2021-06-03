/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** ICollidable
*/

#ifndef ICOLLIDABLE_HPP
#define ICOLLIDABLE_HPP

#include "export.hpp"

namespace ObjectType
{
    class EXPORT ObjectBox;
}

namespace raylib
{
    class EXPORT ICollidable
    {
        public :
            virtual ~ICollidable() {};
            virtual bool boxCollider(const ObjectType::ObjectBox &box) = 0;
    };
};

#endif