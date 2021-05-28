/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Font
*/

#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "../../include/include.hpp"

#include "IFont.hpp"

namespace raylib
{
    class Font : public IFont
    {
        public :
            Font(std::string path = "");
            ~Font();

            void setPath(const std::string &path);

            RFont getFont() const;

            void reset();
        
        private :
            std::string _path;
            RFont _font;
            bool _hasFont;

    };
};

#endif // TEXTURE_HPP