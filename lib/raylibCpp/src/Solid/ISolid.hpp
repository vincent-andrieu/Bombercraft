/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** ISolid
*/

#ifndef ISOLID_HPP
#define ISOLID_HPP

#include "../../include/include.hpp"

#include "../Texture/ITexture.hpp"

namespace raylib
{
    class ISolid
    {
        public :
            virtual ~ISolid() {};

            virtual void draw() = 0;

            virtual void setPosition(const MyVector3 position) = 0;
            virtual void setSize(const MyVector3 size) = 0;
            virtual void setColor(const RColor color) = 0;
            virtual void setTexture(const std::shared_ptr<ITexture> &texture) = 0;
    };
};

#endif // ISOLID_HPP