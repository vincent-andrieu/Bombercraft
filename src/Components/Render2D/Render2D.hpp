/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 02/06/2021 Render2D.hpp.h
*/

#ifndef RENDER2D_HPP
#define RENDER2D_HPP

#include "ARender2D.hpp"

namespace Component
{
    class Render2D : public ARender2D, public Engine::Component<Render2D> {
      public:
        explicit Render2D(render2dMapModels const &models);
        ~Render2D() = default;

        void draw() override;

        bool save(Engine::SaveManager &saver) const override;
        bool load(Engine::SaveManager &saver) override;
    };
} // namespace Component

#endif // RENDER2D_HPP