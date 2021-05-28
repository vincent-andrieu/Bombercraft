/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Texture
*/

#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "../../include/include.hpp"

#include "ITexture.hpp"

namespace raylib
{
    class Texture : public ITexture
    {
        public :
            Texture(const std::string &path, MyVector2 position = {0, 0},
            RColor color = RColor::RWHITE);
            ~Texture();

            void draw();

            void setPosition(MyVector2 position);
            void setColor(RColor color);
            void setPath(const std::string &path);

            Texture2D getTexture() const;
            std::string getPath() const;
        
        private :
            MyVector2 _position;
            RColor _color;
            std::string _path;
            Texture2D _texture;

    };
};

#endif // TEXTURE_HPP