/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Camera
*/

#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "../../include/object.hpp"

#include "ICamera.hpp"

namespace raylib
{
    class Camera : public ICamera {
      public:
        Camera(const MyVector3 position, const MyVector3 target, const MyVector3 up, const float fovy = 90);
        ~Camera() = default;

        void begin3D();
        void end3D();

        void setPosition(const MyVector3 position);
        void setTarget(const MyVector3 target);
        void setUp(const MyVector3 up);
        void setFovy(const float fovy);

      private:
        Camera3D _camera;
    };
}; // namespace raylib

#endif // CAMERA_HPP