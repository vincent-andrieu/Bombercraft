/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Text
*/

#ifndef TEXT_HPP
#define TEXT_HPP

#include "../../include/include.hpp"

#include "IText.hpp"

namespace raylib
{
    class Text : public IText
    {
        public :
            Text(const std::string &text, const MyVector2 position = {0, 0},
            const size_t size = 1, const RColor color = RColor::RWHITE);
            ~Text();

            void draw();

            void setText(const std::string &text);
            void setPosition(const MyVector2 position);
            void setFont(const std::string &font);
            void setColor(const RColor color);
            void setFontSize(const size_t size);
            void setLimit(const MyVector4 limit);

            void removeFont();
            void removeLimit();

        private :
            std::string _text;
            MyVector2 _position;
            std::shared_ptr<IFont> _font;
            RColor _color;
            size_t _size;
            Rectangle _limit;
    };
};

#endif // TEXT_HPP