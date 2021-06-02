/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Camera
*/

#include "Camera.hpp"

raylib::Camera::Camera(const MyVector3 position, const MyVector3 target, const MyVector3 up,
const float fovy)
{
    _camera = { 0 };
    _camera.position = (Vector3){position.a, position.b, position.c};
    _camera.target = (Vector3){target.a, target.b, target.c};
    _camera.up = (Vector3){up.a, up.b, up.c};
    _camera.fovy = fovy;
    _camera.projection = CAMERA_PERSPECTIVE;
}

raylib::Camera::~Camera() {}

void raylib::Camera::begin3D()
{
    BeginMode3D(_camera);
}

void raylib::Camera::end3D()
{
    EndMode3D();
}

void raylib::Camera::setPosition(const MyVector3 position)
{
    _camera.position = (Vector3){position.a, position.b, position.c};
}

void raylib::Camera::setTarget(const MyVector3 target)
{
    _camera.target = (Vector3){target.a, target.b, target.c};
}

void raylib::Camera::setUp(const MyVector3 up)
{
    _camera.up = (Vector3){up.a, up.b, up.c};
}

void raylib::Camera::setFovy(const float fovy)
{
    _camera.fovy = fovy;
}