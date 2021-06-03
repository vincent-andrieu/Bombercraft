/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Font
*/

#ifndef FONT_HPP
#define FONT_HPP

#include "../../include/object.hpp"

#include "IFont.hpp"

#include "export.hpp"

namespace raylib
{
    class EXPORT Font : public IFont {
      public:
        Font(const string path = "");
        ~Font();

        void setPath(const string &path);

        [[nodiscard]] RFont getFont() const;

        void reset();

      private:
        string _path;
        RFont _font;
        bool _hasFont;
    };
}; // namespace raylib

#endif // FONT_HPP