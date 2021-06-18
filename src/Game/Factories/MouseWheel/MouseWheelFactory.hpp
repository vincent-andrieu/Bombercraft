/*
 * EPITECH PROJECT, 2021
 * MouseWheelFactory
 * File description:
 * MouseWheelFactory.hpp - Created: 17/06/2021
 */

#ifndef BOMBERMAN_MOUSE_WHEEL_FACTORY_HPP
#define BOMBERMAN_MOUSE_WHEEL_FACTORY_HPP

#include "GameEngine.hpp"
#include "raylib.hpp"

#include "Components/AbstractEvent/AbstractEvent.hpp"

namespace Game
{
    using MouseEventScript = std::function<void(const float &)>;

    class MouseWheelFactory {
      public:
        virtual ~MouseWheelFactory() = 0;
        static void create(Engine::EntityPack &pack, MouseEventScript eventHandler);
    };
} // namespace Game

#endif // BOMBERMAN_MOUSE_WHEEL_FACTORY_HPP