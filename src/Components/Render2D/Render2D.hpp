/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 02/06/2021 Render2D.hpp.h
*/

#ifndef RENDER2D_HPP
#define RENDER2D_HPP

#include "GameEngine.hpp"
#include "raylib.hpp"
#include <memory>

namespace Component
{
    class Render2D : public Engine::Component<Render2D> {
      public:
        Render2D(std::shared_ptr<raylib::IRenderable> object);
        ~Render2D() = default;

        bool save(Engine::SaveManager &saver) const override;
        bool load(Engine::SaveManager &saver) override;

        std::shared_ptr<raylib::IRenderable> modele;
    };
} // namespace Component

#endif // RENDER2D_HPP