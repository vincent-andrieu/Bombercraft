/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Cuboid
*/

#ifndef CUBOID_HPP
#define CUBOID_HPP

#include "../../include/object.hpp"

#include "ISolid.hpp"

namespace raylib
{
    class Cuboid : public ISolid
    {
        public :
            Cuboid(const std::shared_ptr<ITexture> texture, const MyVector3 position,
            const MyVector3 size, const RColor color = RColor::RWHITE);
            ~Cuboid();

            void draw();

            void setPosition(const MyVector3 position);
            void setSize(const MyVector3 size);
            void setColor(const RColor color);
            void setTexture(const std::shared_ptr<ITexture> &texture);
        
        private :
            MyVector3 _position;
            MyVector3 _size;
            RColor _color;
            std::shared_ptr<ITexture> _texture;
    };
};

#endif // Cuboid_HPP