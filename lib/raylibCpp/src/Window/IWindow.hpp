/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** IWindow
*/

#ifndef IWINDOW_HPP
#define IWINDOW_HPP

#include "../../include/object.hpp"

#include "../Camera/ICamera.hpp"

namespace raylib
{
    class IWindow {
      public:
        virtual ~IWindow() = default;

        virtual void open() = 0;
        virtual void close() = 0;

        virtual void clear() = 0;
        virtual void refresh() = 0;

        virtual void setSize(const MyVector2 size) = 0;
        virtual void setColor(const RColor color) = 0;
        virtual void setTitle(const string &title) = 0;
        virtual void setCamera(const std::shared_ptr<ICamera> &camera) = 0;
        virtual void setFPS(const int fps) = 0;
        virtual void setExitKey(int key) = 0;

        virtual std::shared_ptr<ICamera> getCamera() const = 0;

        virtual bool isOpen() const = 0;
    };
}; // namespace raylib

#endif // IWINDOW_HPP