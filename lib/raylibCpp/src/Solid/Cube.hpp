/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Cube
*/

#ifndef CUBE_HPP
#define CUBE_HPP

#include "../../include/include.hpp"

#include "ISolid.hpp"

namespace raylib
{
    class Cube : public ISolid
    {
        public :
            Cube(std::shared_ptr<ITexture> texture, MyVector3 position,
            MyVector3 size, RColor color);
            ~Cube();

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

#endif // CUBE_HPP