/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** IText
*/

#ifndef ITEXT_HPP
#define ITEXT_HPP

#include "../Font/IFont.hpp"
#include "../Font/Font.hpp"
#include "../../include/object.hpp"
#include "../../include/IRenderable.hpp"

namespace raylib
{
    class IText : public IRenderable {
      public:
        virtual ~IText() = default;

        virtual void draw() = 0;

        virtual void setText(const string &text) = 0;
        virtual std::string getText() const  = 0;
        virtual void setPosition(const MyVector2 position) = 0;
        virtual void setFont(std::shared_ptr<raylib::IFont> &font) = 0;
        virtual void setFont(const string &font) = 0;
        virtual void setColor(const RColor color) = 0;
        virtual void setFontSize(const size_t size) = 0;
        virtual void setLimit(const MyVector4 limit) = 0;

        virtual void removeFont() = 0;
        virtual void removeLimit() = 0;
    };
}; // namespace raylib

#endif // ITEXT_HPP