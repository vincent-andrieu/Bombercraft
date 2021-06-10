/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Text
*/

#ifndef TEXT_HPP
#define TEXT_HPP

#include "../../include/object.hpp"

#include "IText.hpp"

namespace raylib
{
    class Text : public IText {
      public:
        Text(const string &text, const MyVector2 position = {0, 0}, const size_t size = 1, const RColor color = RColor::RWHITE,
            std::shared_ptr<raylib::Font> font = std::make_shared<raylib::Font>());
        Text(const string &text, const string &fontPath, const MyVector2 position = {0, 0}, const size_t size = 1,
            const RColor color = RColor::RWHITE);
        ~Text() = default;

        void draw();

        void setText(const string &text);
        std::string getText() const;
        void setPosition(const MyVector2 position);
        void setFont(std::shared_ptr<raylib::IFont> &font);
        void setFont(const string &font);
        void setColor(const RColor color);
        void setFontSize(const size_t size);
        void setLimit(const MyVector4 limit);

        void removeFont();
        void removeLimit();

      protected:
        string _text;
        MyVector2 _position;
        std::shared_ptr<IFont> _font;
        RColor _color;
        size_t _size;
        Rectangle _limit;
    };
}; // namespace raylib

#endif // TEXT_HPP