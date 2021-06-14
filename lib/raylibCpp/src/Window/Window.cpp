/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Window
*/

#include "Window.hpp"

raylib::Window::Window(const MyVector2 size, const string &title, const RColor color, const int fps)
{
    this->_size = size;
    this->_title = title;
    this->_color = color;
    this->_camera = nullptr;
    this->_fps = fps;
}

void raylib::Window::open()
{
    InitWindow(_size.a, _size.b, _title.data());
    InitAudioDevice();
    SetTargetFPS(_fps);
}

void raylib::Window::close()
{
    CloseAudioDevice();
    CloseWindow();
}

void raylib::Window::clear()
{
    if (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(_matchingColors.at(this->_color));
    }
}

void raylib::Window::refresh()
{
    if (!WindowShouldClose())
        EndDrawing();
}

void raylib::Window::setSize(const MyVector2 size)
{
    if (size.a <= 0 || size.b <= 0)
        return;
    this->_size = size;
    SetWindowSize(this->_size.a, this->_size.b);
}

void raylib::Window::setColor(const RColor color)
{
    this->_color = color;
}

void raylib::Window::setTitle(const string &title)
{
    this->_title = title;
    SetWindowTitle(this->_title.data());
}

void raylib::Window::setCamera(const std::shared_ptr<ICamera> &camera)
{
    this->_camera = camera;
}

void raylib::Window::setFPS(const int fps)
{
    this->_fps = fps;
    SetTargetFPS(this->_fps);
}

std::shared_ptr<raylib::ICamera> raylib::Window::getCamera() const
{
    return this->_camera;
}

bool raylib::Window::isOpen() const
{
    return !WindowShouldClose();
}

void raylib::Window::setExitKey(int key)
{
    SetExitKey(key);
}

void raylib::Window::setWindowIcon(const std::string &iconPath)
{
    Image img = LoadImage(iconPath.c_str());

    SetWindowIcon(img);
}

void raylib::Window::openURL(const std::string &url) const
{
    OpenURL(url.c_str());
}