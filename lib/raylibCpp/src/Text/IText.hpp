/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** IText
*/

#ifndef ITEXT_HPP
#define ITEXT_HPP

#include "../Font/IFont.hpp"
#include "../../include/include.hpp"
#include "../Renderable/IRenderable.hpp"

namespace raylib
{
    class IText : public IRenderable
    {
        public :
            virtual ~IText() {};

            virtual void draw() = 0;

            virtual void setText(const std::string &text) = 0;
            virtual void setPosition(const MyVector2 position) = 0;
            virtual void setFont(const std::string &font) = 0;
            virtual void setColor(const RColor color) = 0;
            virtual void setFontSize(const size_t size) = 0;
            virtual void setLimit(const MyVector4 limit) = 0;

            virtual void removeFont() = 0;
            virtual void removeLimit() = 0;
    };
};

#endif // ITEXT_HPP