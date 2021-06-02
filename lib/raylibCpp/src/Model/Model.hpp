/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Model
*/

#ifndef MODEL_HPP
#define MODEL_HPP

#include "../../include/include.hpp"

#include "IModel.hpp"

typedef Model RModel;

namespace raylib
{
    class Model : public IModel {
      public:
        Model(const std::shared_ptr<ITexture> texture, const string &filepath, const MyVector3 position, const RColor color);
        ~Model();

        void draw();

        void setPosition(const MyVector3 position);
        void setRotation(const MyVector3 rotation);
        void setScale(const float scale);
        void setColor(const RColor color);
        void setPath(const string &path);
        void setTexture(const std::shared_ptr<ITexture> &texture);

        string getPath() const;

      private:
        MyVector3 _position;
        MyVector3 _rotation;
        float _scale;
        RColor _color;
        std::shared_ptr<ITexture> _texture;
        string _path;
        RModel _model;
    };
}; // namespace raylib

#endif // MODEL_HPP