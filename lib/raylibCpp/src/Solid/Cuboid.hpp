/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Cuboid
*/

#ifndef CUBOID_HPP
#define CUBOID_HPP

#include "../../include/include.hpp"

#include "ISolid.hpp"

namespace raylib
{
    class Cuboid : public ISolid
    {
        public :
            Cuboid(std::shared_ptr<ITexture> texture, MyVector3 position,
            MyVector3 size, RColor color = RColor::RWHITE);
            ~Cuboid();

            void draw();

            void setPosition(MyVector3 position);
            void setSize(MyVector3 size);
            void setColor(RColor color);
            void setTexture(std::shared_ptr<ITexture> &texture);
        
        private :
            MyVector3 _position;
            MyVector3 _size;
            RColor _color;
            std::shared_ptr<ITexture> _texture;
    };
};

#endif // Cuboid_HPP