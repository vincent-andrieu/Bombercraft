/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 02/06/2021 Render3DSystem.hpp.h
*/

#ifndef RENDER3DSYSTEM_HPP
#define RENDER3DSYSTEM_HPP

#include "GameEngine.hpp"
#include "Components/Render3D/Render3D.hpp"
#include "Game/Core/Core.hpp"

namespace System
{
    class Render3DSystem : public Engine::AbstractSystem {
      public:
        Render3DSystem();

        void update();
    };
} // namespace System

#endif // RENDER3DSYSTEM_HPP
