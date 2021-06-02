/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** ITexture
*/

#ifndef ITEXTURE_HPP
#define ITEXTURE_HPP

#include "../../include/include.hpp"

namespace raylib
{
    class ITexture {
      public:
        virtual ~ITexture() = default;

        virtual void draw() = 0;

        virtual void setPosition(const MyVector2 position) = 0;
        virtual void setColor(const RColor color) = 0;
        virtual void setPath(const string &path) = 0;

        virtual Texture2D getTexture() const = 0;
        virtual string getPath() const = 0;
    };
}; // namespace raylib

#endif // ITEXTURE_HPP