/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** IFont
*/

#ifndef IFONT_HPP
#define IFONT_HPP

#include "../../include/object.hpp"

#include "export.hpp"

typedef Font RFont;

namespace raylib
{
    class EXPORT IFont {
      public:
        virtual ~IFont(){};

        virtual void setPath(const string &path) = 0;

        virtual RFont getFont() const = 0;

        virtual void reset() = 0;
    };
}; // namespace raylib

#endif // IFONT_HPP