/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Camera
*/

#include "Camera.hpp"

raylib::Camera::Camera(const MyVector3 position, const MyVector3 target, const MyVector3 up, const float fovy)
{
    this->_camera = {0};
    this->_camera.position = (Vector3){position.a, position.b, position.c};
    this->_camera.target = (Vector3){target.a, target.b, target.c};
    this->_camera.up = (Vector3){up.a, up.b, up.c};
    this->_camera.fovy = fovy;
    this->_camera.projection = CAMERA_PERSPECTIVE;
}

void raylib::Camera::begin3D()
{
    BeginMode3D(this->_camera);
}

void raylib::Camera::end3D()
{
    EndMode3D();
}

void raylib::Camera::setPosition(const MyVector3 position)
{
    this->_camera.position = (Vector3){position.a, position.b, position.c};
}

void raylib::Camera::setTarget(const MyVector3 target)
{
    this->_camera.target = (Vector3){target.a, target.b, target.c};
}

void raylib::Camera::setUp(const MyVector3 up)
{
    this->_camera.up = (Vector3){up.a, up.b, up.c};
}

void raylib::Camera::setFovy(const float fovy)
{
    this->_camera.fovy = fovy;
}