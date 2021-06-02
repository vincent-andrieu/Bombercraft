/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Window
*/

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "../../include/include.hpp"

#include "IWindow.hpp"

namespace raylib
{
    class Window : public IWindow
    {
        public :
            Window(const MyVector2 size, const std::string &title, const RColor color,
            const int fps = 60);
            ~Window();

            void open();
            void close();

            void clear();
            void refresh();

            void setSize(const MyVector2 size);
            void setColor(const RColor color);
            void setTitle(const std::string &title);
            void setCamera(const std::shared_ptr<ICamera> &camera);
            void setFPS(const int fps);

            std::shared_ptr<ICamera> getCamera() const;

            bool isOpen() const;

        private :
            MyVector2 _size;
            RColor _color;
            std::string _title;
            std::shared_ptr<ICamera> _camera;
            int _fps;
    };
};

#endif // WINDOW_HPP