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
        Texture(const string &path,
            const MyVector2 size = {-1, -1},
            const MyVector2 position = {0, 0},
            const RColor color = RColor::RWHITE,
            const bool scaleMode = true,
            const MyVector2 rectSize = {0, 0});
        ~Texture();

        void draw();
        void update();

        void setPosition(const MyVector2 position);
        void setColor(const RColor color);
        void setPath(const string &path);
        void setSize(const MyVector2 size);
        void setScaleMode(const bool mode);
        void setRect(const MyVector2 rect);
        void setTruncateSize(const MyVector2 &size);

        [[nodiscard]] Texture2D getTexture() const;
        [[nodiscard]] string getPath() const;
        [[nodiscard]] MyVector2 getRect() const;
        [[nodiscard]] MyVector2 getSize() const;
        [[nodiscard]] MyVector2 getPosition() const;

        void setLoaderManager();
        std::shared_ptr<raylib::LoaderManager<Texture2D, std::string>> getLoaderManager() const;

        static std::shared_ptr<raylib::LoaderManager<Texture2D, std::string>> _loaderManager;

        static Texture2D myTextureLoad(const std::string &str);
        static void myTextureUnload(Texture2D &texture);

      private:
        MyVector2 _position;
        RColor _color;
        string _path;
        MyVector2 _size;
        Texture2D _texture;
        Rectangle _destRect;
        bool _scaleMode;
        MyVector2 _truncateSize;
        MyVector2 _truncateCoef;
    };
}; // namespace raylib

#endif // TEXTURE_HPP