/*
** EPITECH PROJECT, 2021
** KeyManagementFactory.hpp
** File description:
** Class KeyManagementFactory that allows to easily create keyManager, in order to handle key events as an entity
*/

#ifndef BOMBERMAN_KEYMANAGEMENTFACTORY_HPP
#define BOMBERMAN_KEYMANAGEMENTFACTORY_HPP

#include <unordered_map>

#include "GameEngine.hpp"
#include "raylib.hpp"

#include "Components/AbstractEvent/AbstractEvent.hpp"

namespace Game
{
    class keyManagementFactory {
      public:
        virtual ~keyManagementFactory() = 0;
        static void create(Engine::EntityPack &pack, std::unordered_map<raylib::KeyBoard, Component::eventScript> keyTrigger);
    };
} // namespace Game

#endif // BOMBERMAN_KEYMANAGEMENTFACTORY_HPP