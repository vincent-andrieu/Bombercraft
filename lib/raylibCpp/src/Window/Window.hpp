/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Window
*/

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "../../include/object.hpp"

#include "IWindow.hpp"

namespace raylib
{
    class Window : public IWindow {
      public:
        Window(const MyVector2 size, const string &title, const RColor color, const int fps = 60);
        ~Window() = default;

        void open();
        void close();

        void clear();
        void refresh();

        void setSize(const MyVector2 size);
        void setColor(const RColor color);
        void setTitle(const string &title);
        void setCamera(const std::shared_ptr<ICamera> &camera);
        void setFPS(const int fps);

        [[nodiscard]] std::shared_ptr<ICamera> getCamera() const;

        [[nodiscard]] bool isOpen() const;

      private:
        MyVector2 _size;
        RColor _color;
        string _title;
        std::shared_ptr<ICamera> _camera;
        int _fps;
    };
}; // namespace raylib

#endif // WINDOW_HPP