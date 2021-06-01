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

            virtual void setPosition(MyVector3 position) = 0;
            virtual void setSize(MyVector3 size) = 0;
            virtual void setColor(RColor color) = 0;
            virtual void setTexture(std::shared_ptr<ITexture> &texture) = 0;
    };
};

#endif // ISOLID_HPP