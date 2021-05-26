/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Camera
*/

#include "Camera.hpp"

raylib::Camera::Camera(MyVector3 position, MyVector3 target, MyVector3 up,
float fovy)
{
    _camera = { 0 };
    _camera.position = (Vector3){position.a, position.b, position.c};
    _camera.target = (Vector3){target.a, target.b, target.c};
    _camera.up = (Vector3){up.a, up.b, up.c};
    _camera.fovy = fovy;
    _camera.projection = CAMERA_PERSPECTIVE;
}

raylib::Camera::~Camera() {}

void raylib::Camera::start()
{
    BeginMode3D(_camera);
}

void raylib::Camera::stop()
{
    EndMode3D;
}

void raylib::Camera::setPosition(MyVector3 position)
{
    _camera.position = (Vector3){position.a, position.b, position.c};
}

void raylib::Camera::setTarget(MyVector3 target)
{
    _camera.target = (Vector3){target.a, target.b, target.c};
}

void raylib::Camera::setUp(MyVector3 up)
{
    _camera.up = (Vector3){up.a, up.b, up.c};
}

void raylib::Camera::setFovy(float fovy)
{
    _camera.fovy = fovy;
}