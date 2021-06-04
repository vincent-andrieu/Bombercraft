/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** IRenderable
*/

#ifndef IRENDERABLE_HPP
#define IRENDERABLE_HPP

namespace raylib
{
    class IRenderable
    {
        public :
            virtual ~IRenderable() {};
            virtual void draw() = 0;
    };
};

#endif