/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 27/05/2021 main.cpp.c
*/

#include <iostream>
#include "GameEngine.hpp"

int main(void)
{
    // MANAGER
    auto systemManager = Engine::SystemManager();
    auto manager = Engine::EntityManager<MAX_COMPONENT>(systemManager);
    manager.registerComponent<Engine::Position>();
    manager.registerComponent<Engine::Velocity>();
    // SYSTEM
    auto system = systemManager.createSystem<Engine::PhysicsSystem>(manager);
    // ENTITY
    for (auto i = 0; i < 10; ++i)
    {
        auto entity = manager.createEntity();
        manager.addComponent<Engine::Position>(entity);
        manager.addComponent<Engine::Velocity>(entity);
    }
    // LOOP
    auto dt = 1.0f / 60.0f;
    for (std::size_t i = 0; i < 1000; i++) {
        system->update(dt);
    }
    return EXIT_SUCCESS;
}