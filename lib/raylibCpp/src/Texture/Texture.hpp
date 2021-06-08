/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Texture
*/

#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "../../include/object.hpp"

#include "ITexture.hpp"

namespace raylib
{
    class Texture : public ITexture {
      public:
        Texture(const string &path, const MyVector2 size = {-1, -1}, const MyVector2 position = {0, 0},
            const RColor color = RColor::RWHITE);
        ~Texture();

        void draw();

        void setPosition(const MyVector2 position);
        void setColor(const RColor color);
        void setPath(const string &path);
        void setSize(const MyVector2 size);

        [[nodiscard]] Texture2D getTexture() const;
        [[nodiscard]] string getPath() const;

      private:
        MyVector2 _position;
        RColor _color;
        string _path;
        Texture2D _texture;
        Rectangle _size;
    };
}; // namespace raylib

#endif // TEXTURE_HPP