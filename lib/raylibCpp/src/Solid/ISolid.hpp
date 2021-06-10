/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** ISolid
*/

#ifndef ISOLID_HPP
#define ISOLID_HPP

#include "../Texture/ITexture.hpp"
#include "../../include/object.hpp"
#include "../../include/IRenderable.hpp"
#include "I3DObject.hpp"

namespace raylib
{
    class ISolid : public I3DObject {
      public:
        virtual ~ISolid() = default;

        virtual void draw() = 0;

        virtual void setPosition(const MyVector3 position) = 0;
        virtual const MyVector3 &getPosition() const = 0;
        virtual void setSize(const MyVector3 size) = 0;
        virtual void setColor(const RColor color) = 0;
        virtual void setTexture(const std::shared_ptr<ITexture> &texture) = 0;
    };
}; // namespace raylib

#endif // ISOLID_HPP