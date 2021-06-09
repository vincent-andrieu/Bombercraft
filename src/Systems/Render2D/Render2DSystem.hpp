/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 02/06/2021 Render2DSystem.hpp.h
*/

#ifndef RENDER2DSYSTEM_HPP
#define RENDER2DSYSTEM_HPP

#include "GameEngine.hpp"
#include "Components/Render2D/Render2D.hpp"
#include "Components/Render2D/SingleRender2D.hpp"

namespace System
{
    class Render2DSystem : public Engine::AbstractSystem {
      public:
        Render2DSystem();

        void update();
    };
} // namespace System

#endif // RENDER2DSYSTEM_HPP