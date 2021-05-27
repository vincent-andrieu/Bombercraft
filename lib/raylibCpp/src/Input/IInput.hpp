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
        virtual bool isKeyPressed(KeyBoard key) const = 0;
        virtual bool isKeyReleased(KeyBoard key) const = 0;
        virtual MyVector2 getMousePos(void) const = 0;
        virtual bool isMousseLeftPressed(void) const = 0;
        virtual bool isMousseRightPressed(void) const = 0;
        virtual bool isMousseMiddlePressed(void) const = 0;
    };
};

#endif