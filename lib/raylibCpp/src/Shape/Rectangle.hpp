/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Rectangle
*/

#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "../../include/include.hpp"

#include "IShape.hpp"

namespace raylib
{
    class Rectangle : public IShape
    {
        public :
            Rectangle(MyVector2 position,
            MyVector2 size, RColor color = RColor::RWHITE);
            ~Rectangle();

            void draw();

            void setPosition(MyVector2 position);
            void setSize(MyVector2 size);
            void setColor(RColor color);

        private :
            MyVector2 _position;
            MyVector2 _size;
            RColor _color;
    };
};

#endif // RECTANGLE_HPP