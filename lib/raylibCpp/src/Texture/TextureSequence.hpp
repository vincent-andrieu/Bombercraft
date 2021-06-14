/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Texture Sequence
*/

#ifndef TEXTURE_SEQUENCE_HPP
#define TEXTURE_SEQUENCE_HPP

#include "../../include/object.hpp"

#include "Texture.hpp"

namespace raylib
{
    class TextureSequence : public ITexture {
      public:
        TextureSequence(const string &path,
            const MyVector2 size = {-1, -1},
            const MyVector2 position = {0, 0},
            const RColor color = RColor::RWHITE);
        ~TextureSequence();

        void draw();
        void update();

        void setPosition(const MyVector2 position);
        void setColor(const RColor color);
        void setPath(const string &path);
        void setSize(const MyVector2 size);
        void setScaleMode(const bool mode);
        void setRect(const MyVector2 rect);

        [[nodiscard]] Texture2D getTexture() const;
        [[nodiscard]] string getPath() const;
        [[nodiscard]]  MyVector2 getRect() const;

      private:
        MyVector2 _position;
        RColor _color;
        string _path;
        std::vector<Texture2D> _textures;
        size_t _currentFrame;
        size_t _frameNumber;
        Rectangle _size;
        bool _scaleMode;
    };
}; // namespace raylib

#endif // TEXTURE_SEQUENCE_HPP