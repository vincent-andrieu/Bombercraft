/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Animation
*/

#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include "../../include/object.hpp"

#include "IModel.hpp"

namespace raylib
{
    class Animation : public IModel {
      public:
        Animation(const std::string &texturePath, const std::string &dirpath, const MyVector3 position, const RColor color);
        ~Animation();

        void draw();

        void setPosition(const MyVector3 position);
        void setRotation(const MyVector3 rotation);
        void setScale(const float scale);
        void setColor(const RColor color);
        void setPath(const std::string &path);
        void setTexture(const std::string &texturePath);

        [[nodiscard]] std::string getPath() const;

      private:
        MyVector3 _position;
        MyVector3 _rotation;
        float _scale;
        RColor _color;
        std::vector<Texture2D> _textures;
        std::string _path;
        std::vector<RModel> _models;
        size_t _currentFrame;
        std::chrono::system_clock::time_point _start;
    };
}; // namespace raylib

#endif // ANIMATION_HPP