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
        explicit Text(string text,
            MyVector2 position = {0, 0},
            size_t size = 1,
            RColor color = RColor::RWHITE,
            const std::shared_ptr<raylib::Font> &font = std::make_shared<raylib::Font>());
        explicit Text(string text,
            MyVector2 position = {0, 0},
            size_t size = 1,
            RColor color = RColor::RWHITE,
            const string &fontPath = "");
        ~Text() override
        {
            _font = nullptr;
        };

        void draw() override;

        void setText(const string &text) override;
        [[nodiscard]] std::string getText() const override;
        void setPosition(MyVector2 position) override;
        void setFont(std::shared_ptr<raylib::IFont> &font) override;
        void setFont(const string &font) override;
        void setColor(RColor color) override;
        void setFontSize(size_t size) override;
        void setLimit(MyVector4 limit) override;

        void removeFont() override;
        void removeLimit() override;

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