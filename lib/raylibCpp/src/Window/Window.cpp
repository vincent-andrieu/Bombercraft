/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Window
*/

#include "Window.hpp"

raylib::Window::Window(MyVector2 size, const std::string &title, RColor color,
int fps)
{
    _size = size;
    _title = title;
    _color = color;
    _camera = nullptr;
    _fps = fps;
}

raylib::Window::~Window() {}

void raylib::Window::open()
{
    InitWindow(_size.a, _size.b, _title.data());
    SetTargetFPS(_fps);
}

void raylib::Window::close()
{
    CloseWindow();
}

void raylib::Window::clear()
{
    BeginDrawing();
    ClearBackground(_matchingColors.at(_color));
}

void raylib::Window::refresh()
{
    EndDrawing();
}

void raylib::Window::setSize(MyVector2 size)
{
    if (size.a <= 0 || size.b <= 0)
        return;
    _size = size;
    SetWindowSize(_size.a, _size.b);
}

void raylib::Window::setColor(RColor color)
{
    _color = color;
}

void raylib::Window::setTitle(const std::string &title)
{
    _title = title;
    SetWindowTitle(_title.data());
}

void raylib::Window::setCamera(std::shared_ptr<ICamera> &camera)
{
    _camera = camera;
}

void raylib::Window::setFPS(int fps)
{
    _fps = fps;
    SetTargetFPS(_fps);
}


std::shared_ptr<raylib::ICamera> raylib::Window::getCamera() const
{
    return _camera;
}

bool raylib::Window::isOpen() const
{
    return !WindowShouldClose();
}