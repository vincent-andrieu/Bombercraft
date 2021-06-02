/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Font
*/

#ifndef FONT_HPP
#define FONT_HPP

#include "../../include/include.hpp"

#include "IFont.hpp"

namespace raylib
{
    class Font : public IFont {
      public:
        Font(const string path = "");
        ~Font();

        void setPath(const string &path);

        RFont getFont() const;

        void reset();

      private:
        string _path;
        RFont _font;
        bool _hasFont;
    };
}; // namespace raylib

#endif // FONT_HPP