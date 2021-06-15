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
        explicit Text(const string &text,
            MyVector2 position = {0, 0},
            size_t size = 1,
            RColor color = RColor::RWHITE,
            const std::shared_ptr<raylib::Font> &font = std::make_shared<raylib::Font>());
        explicit Text(const string &text,
            const string &fontPath = "",
            MyVector2 position = {0, 0},
            size_t size = 1,
            RColor color = RColor::RWHITE);
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

        /**
         * @brief Set text size fit to vector2
         * @param text The text to be adapted
         * @param size The size at which the text should correspond
         */
        static void setFontSize(raylib::Text &text, const raylib::MyVector2 &size);
        void setLimit(MyVector4 limit) override;

        void removeFont() override;
        void removeLimit() override;

        [[nodiscard]] raylib::MyVector2 getSize() const;
        [[nodiscard]] size_t getFontSize() const;
        [[nodiscard]] MyVector2 getPosition() const;

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