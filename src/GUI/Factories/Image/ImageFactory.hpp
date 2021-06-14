/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 09/06/2021 ImageFactory.hpp.h
*/

#ifndef IMAGEFACTORY_HPP
#define IMAGEFACTORY_HPP

#include "raylib.hpp"
#include <string>
#include "GameEngine.hpp"

namespace GUI
{
    using MyVector2 = raylib::MyVector2;

    class ImageFactory {
      public:
        virtual ~ImageFactory() = 0;

        static void create(Engine::EntityPack &entityPack, const MyVector2 &position, const MyVector2 &size,
            std::string const &filePath, const bool scale = false, std::string const &name = "", const raylib::MyVector2 &rectPos = raylib::MyVector2(-1, -1));
    };
} // namespace GUI

#endif // IMAGEFACTORY_HPP
