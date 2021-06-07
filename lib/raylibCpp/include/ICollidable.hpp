/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** ICollidable
*/

#ifndef ICOLLIDABLE_HPP
#define ICOLLIDABLE_HPP

namespace raylib
{
    class ObjectBox;

    class ICollidable
    {
        public :
            virtual ~ICollidable() {};
            virtual bool boxCollider(const ObjectBox &box) = 0;
    };
};

#endif