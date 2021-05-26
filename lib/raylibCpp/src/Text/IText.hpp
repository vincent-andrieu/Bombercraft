/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** IText
*/

#ifndef ITEXT_HPP
#define ITEXT_HPP

#include "../../include/include.hpp"

namespace raylib
{
    class IText
    {
        public :
            virtual ~IText() {};

            virtual void draw() = 0;

            virtual void setText(const std::string &text) = 0;
            virtual void setPosition(MyVector2 position) = 0;
            virtual void setFont(const std::string &font) = 0;
            virtual void setColor(RColor color) = 0;
            virtual void setFontSize(size_t size) = 0;
            virtual void setLimit(MyVector4 limit) = 0;

            virtual void removeFont() = 0;
            virtual void removeLimit() = 0;
    };
};

#endif // ITEXT_HPP