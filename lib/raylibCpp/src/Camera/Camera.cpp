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
    this->_camera.position = MyVector3::makeVector3(position);
    this->_camera.target = MyVector3::makeVector3(target);
    this->_camera.up = MyVector3::makeVector3(up);
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
    this->_camera.position = MyVector3::makeVector3(position);
}

void raylib::Camera::setTarget(const MyVector3 target)
{
    this->_camera.target = MyVector3::makeVector3(target);
}

void raylib::Camera::setUp(const MyVector3 up)
{
    this->_camera.up = MyVector3::makeVector3(up);
}

void raylib::Camera::setFovy(const float fovy)
{
    this->_camera.fovy = fovy;
}

const float &raylib::Camera::getFovy() const
{
    return this->_camera.fovy;
}