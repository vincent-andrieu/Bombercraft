/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** ICamera
*/

#ifndef ICAMERA_HPP
#define ICAMERA_HPP

#include "../../include/include.hpp"

namespace raylib
{
    class ICamera
    {
        public :
            virtual ~ICamera() {};

            virtual void begin3D() = 0;
            virtual void end3D() = 0;

            virtual void setPosition(MyVector3 position) = 0;
            virtual void setTarget(MyVector3 position) = 0;
            virtual void setUp(MyVector3 position) = 0;
            virtual void setFovy(float fovy) = 0;
    };
};

#endif // ICAMERA_HPP