/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Model
*/

#ifndef MODEL_HPP
#define MODEL_HPP

#include "../../include/object.hpp"

#include "IModel.hpp"

#include "export.hpp"

namespace raylib
{
    class EXPORT Model : public IModel {
      public:
        Model(const std::string &texturePath, const string &filepath, const MyVector3 position, const RColor color);
        ~Model();

        void draw();

        void setPosition(const MyVector3 position);
        void setRotation(const MyVector3 rotation);
        void setScale(const float scale);
        void setColor(const RColor color);
        void setPath(const string &path);
        void setTexture(const std::string &texturePath);

        [[nodiscard]] string getPath() const;

      private:
        MyVector3 _position;
        MyVector3 _rotation;
        float _scale;
        RColor _color;
        Texture2D _texture;
        std::string _texturePath;
        string _path;
        RModel _model;
    };
}; // namespace raylib

#endif // MODEL_HPP