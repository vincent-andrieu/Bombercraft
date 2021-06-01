/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** IFont
*/

#ifndef IFONT_HPP
#define IFONT_HPP

#include "../../include/include.hpp"

typedef Font RFont;

namespace raylib
{
    class IFont
    {
        public :
            virtual ~IFont() {};

            virtual void setPath(const std::string &path) = 0;

            virtual RFont getFont() const = 0;

            virtual void reset() = 0;
    };
};

#endif // IFONT_HPP