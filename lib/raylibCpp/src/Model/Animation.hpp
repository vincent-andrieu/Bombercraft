/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Animation
*/

#ifndef MODEL_HPP
#define MODEL_HPP

#include "../../include/include.hpp"

#include "IModel.hpp"

typedef Model RModel;

namespace raylib
{
    class Animation : public IModel
    {
        public :
            Animation(std::shared_ptr<ITexture> texture, const std::string &path,
            MyVector3 position, RColor color);
            ~Animation();

            void draw();

            void setPosition(MyVector3 position);
            void setRotation(MyVector3 rotation);
            void setScale(float scale);
            void setColor(RColor color);
            void setPath(const std::string &path);
            void setTexture(std::shared_ptr<ITexture> &texture);

            std::string getPath() const;

        private :
            MyVector3 _position;
            MyVector3 _rotation;
            float _scale;
            RColor _color;
            std::shared_ptr<ITexture> _texture;
            std::string _path;
            std::vector<RModel> _models;
            size_t _currentFrame;
    };
};

#endif // MODEL_HPP