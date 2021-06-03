/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** IRenderable
*/

#ifndef IRENDERABLE_HPP
#define IRENDERABLE_HPP

#include "export.hpp"

namespace raylib
{
    class EXPORT IRenderable
    {
        public :
            virtual ~IRenderable() {};
            virtual void draw() = 0;
    };
};

#endif