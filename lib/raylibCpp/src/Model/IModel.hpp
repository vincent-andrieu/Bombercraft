/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** IModel
*/

#ifndef IMODEL_HPP
#define IMODEL_HPP

#include "../Texture/ITexture.hpp"
#include "../../include/object.hpp"
#include "../../include/IRenderable.hpp"
#include "../../include/I3DObject.hpp"

typedef Model RModel;

namespace raylib
{
    class IModel : public I3DObject {
      public:
        virtual ~IModel() = default;

        virtual void draw() = 0;

        virtual void restartAnimation() = 0;

        virtual void setPosition(const MyVector3 position) = 0;
        virtual const MyVector3 &getPosition() const = 0;
        virtual void setRotation(const MyVector3 rotation) = 0;
        virtual const MyVector3 &getRotation() const = 0;
        virtual void setScale(const float scale) = 0;
        virtual void setColor(const RColor color) = 0;
        virtual void setPath(const string &path) = 0;
        virtual void setTexture(const string &texture) = 0;

        virtual string getPath() const = 0;
    };
}; // namespace raylib

#endif // IMODEL_HPP