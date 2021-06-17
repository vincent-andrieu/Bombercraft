/*
** EPITECH PROJECT, 2021
** Indie Studio
** File description:
** Image Sequence Factory
*/

#ifndef IMAGESEQUENCEFACTORY_HPP
#define IMAGESEQUENCEFACTORY_HPP

#include "raylib.hpp"
#include <string>
#include "GameEngine.hpp"

#define DEFAULT_IMAGE_SEQUENCE_FRAME_RATE 1.0f

namespace GUI
{
    using MyVector2 = raylib::MyVector2;

    class ImageSequenceFactory {
      public:
        virtual ~ImageSequenceFactory() = 0;

        static void create(Engine::EntityPack &entityPack,
            const MyVector2 &position,
            const MyVector2 &size,
            std::string const &directoryPath,
            std::string const &name = "",
            const double frameRate = DEFAULT_IMAGE_SEQUENCE_FRAME_RATE,
            bool loop = true);
    };
} // namespace GUI

#endif // IMAGESEQUENCEFACTORY_HPP
