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
            Window(MyVector2 size, const std::string &title, RColor color);
            ~Window();

            void open();
            void close();

            void start();
            void stop();

            void setSize(MyVector2 size);
            void setColor(RColor color);
            void setTitle(const std::string &title);
            void setCamera(std::shared_ptr<ICamera> &camera);

            std::shared_ptr<ICamera> getCamera() const;

            bool isOpen() const;

        private :
            MyVector2 _size;
            RColor _color;
            std::string _title;
            std::shared_ptr<ICamera> _camera;
    };
};

#endif // WINDOW_HPP