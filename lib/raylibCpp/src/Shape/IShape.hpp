/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** IShape
*/

#ifndef ISHAPE_HPP
#define ISHAPE_HPP

#include "../Texture/ITexture.hpp"
#include "../../include/object.hpp"
#include "../../include/IRenderable.hpp"

namespace raylib
{
    class IShape : public IRenderable {
      public:
        virtual ~IShape() = default;

        virtual void draw() = 0;

        virtual void setPosition(const MyVector2 position) = 0;
        virtual void setSize(const MyVector2 size) = 0;
        virtual void setColor(const RColor color) = 0;
    };
}; // namespace raylib

#endif // ISHAPE_HPP