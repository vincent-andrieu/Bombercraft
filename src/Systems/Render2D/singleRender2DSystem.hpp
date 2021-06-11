/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 02/06/2021 singleRender2DSystem.hpp
*/

#ifndef SINGLERENDER2DSYSTEM_HPP
#define SINGLERENDER2DSYSTEM_HPP

#include "GameEngine.hpp"
#include "Components/Render2D/Render2D.hpp"
#include "Components/Render2D/SingleRender2D.hpp"

namespace System
{
    class singleRender2DSystem : public Engine::AbstractSystem {
      public:
        singleRender2DSystem();

        void update();
    };
} // namespace System

#endif // SINGLERENDER2DSYSTEM_HPP