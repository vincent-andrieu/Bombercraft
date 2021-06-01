/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Window
*/

#include "Window.hpp"

raylib::Window::Window(MyVector2 size, const std::string &title, RColor color)
{
    _size = size;
    _title = title;
    _color = color;
    _camera = nullptr;
}

raylib::Window::~Window() {}

void raylib::Window::open()
{
    InitWindow(_size.a, _size.b, _title.data());
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

std::shared_ptr<raylib::ICamera> raylib::Window::getCamera() const
{
    return _camera;
}

bool raylib::Window::isOpen() const
{
    return WindowShouldClose();
}