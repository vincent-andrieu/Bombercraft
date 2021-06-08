/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 03/06/2021 SceneWithEvents.hpp.h
*/

#ifndef SCENEWITHEVENTS_HPP
#define SCENEWITHEVENTS_HPP

#include "raylib.h"
#include "Systems/Event/EventSystem.hpp"
#include "GameEngine.hpp"

namespace Game
{
    class SceneWithEvents {
      public:
        SceneWithEvents() = default;
        ~SceneWithEvents() = default;

      protected:
        void eventDispatcher(Engine::SystemManager &systemManager);
    };
} // namespace Game

#endif // SCENEWITHEVENTS_HPP
