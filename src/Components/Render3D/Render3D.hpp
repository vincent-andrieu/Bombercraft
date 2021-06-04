/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 02/06/2021 Render2DSystem.hpp.h
*/

#ifndef RENDER3D_HPP
#define RENDER3D_HPP

#include "GameEngine.hpp"
#include "raylib.hpp"
#include <memory>

namespace Component
{
    class Render3D : public Engine::Component<Render3D> {
      public:
        Render3D(std::shared_ptr<raylib::IRenderable> object);
        ~Render3D() = default;

        void save(Engine::SaveManager &saver) const override;
        void load(Engine::SaveManager &saver) override;

        std::shared_ptr<raylib::IRenderable> modele;
    };
} // namespace Component

#endif // RENDER3D_HPP