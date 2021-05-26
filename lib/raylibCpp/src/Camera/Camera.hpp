/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Camera
*/

#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "../../include/include.hpp"

#include "ICamera.hpp"

namespace raylib
{
    class Camera : public ICamera
    {
        public :
            Camera(MyVector3 position, MyVector3 target, MyVector3 up,
            float fovy);
            ~Camera();

            void start();
            void stop();

            void setPosition(MyVector3 position);
            void setTarget(MyVector3 target);
            void setUp(MyVector3 up);
            void setFovy(float fovy);
        
        private :
            Camera3D _camera;
    };
};

#endif // CAMERA_HPP