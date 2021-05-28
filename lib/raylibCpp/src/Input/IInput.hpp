/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** IInput
*/

#ifndef IINPUT_HPP
#define IINPUT_HPP

#include "Data/Enum.hpp"
#include "Data/MyVector/MyVector2.hpp"

namespace raylib
{
    class IInput
    {
        virtual ~IInput() = default;
        virtual bool isKeyPressed(KeyBoard key) const = 0;
        virtual bool isKeyReleased(KeyBoard key) const = 0;
        virtual MyVector2 getMousePos(void) const = 0;
        virtual bool isMouseLeftPressed(void) const = 0;
        virtual bool isMouseRightPressed(void) const = 0;
        virtual bool isMouseMiddlePressed(void) const = 0;
        virtual bool isMouseMoved(void) = 0;
        virtual bool MouseIsOver(MyVector2 pos, MyVector2 size) const = 0;
        virtual bool MouseIsOverClicked(MyVector2 pos, MyVector2 size) const = 0;
    };
};

#endif