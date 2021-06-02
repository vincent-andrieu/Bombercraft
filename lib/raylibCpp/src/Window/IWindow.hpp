/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** IWindow
*/

#ifndef IWINDOW_HPP
#define IWINDOW_HPP

#include "../../include/include.hpp"

#include "../Camera/ICamera.hpp"

namespace raylib
{
    class IWindow
    {
        public :
            virtual ~IWindow() {};

            virtual void open() = 0;
            virtual void close() = 0;

            virtual void clear() = 0;
            virtual void refresh() = 0;

            virtual void setSize(MyVector2 size) = 0;
            virtual void setColor(RColor color) = 0;
            virtual void setTitle(const std::string &title) = 0;
            virtual void setCamera(std::shared_ptr<ICamera> &camera) = 0;
            virtual void setFPS(int fps) = 0;

            virtual std::shared_ptr<ICamera> getCamera() const = 0;

            virtual bool isOpen() const = 0;
    };
};

#endif // IWINDOW_HPP