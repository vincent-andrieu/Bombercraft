/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** ITexture
*/

#ifndef ITEXTURE_HPP
#define ITEXTURE_HPP

#include "../../include/object.hpp"
#include "../Renderable/IRenderable.hpp"

namespace raylib
{
    class ITexture : public IRenderable
    {
        public :
            virtual ~ITexture() {};

            virtual void draw() = 0;

            virtual void setPosition(const MyVector2 position) = 0;
            virtual void setColor(const RColor color) = 0;
            virtual void setPath(const std::string &path) = 0;

            virtual Texture2D getTexture() const = 0;
            virtual std::string getPath() const = 0;
    };
};

#endif // ITEXTURE_HPP