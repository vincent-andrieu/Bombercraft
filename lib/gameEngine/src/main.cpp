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
    auto manager = EntityManager<MAX_COMPONENT, MAX_SYSTEM>();
    manager.registerComponent<Position>();
    manager.registerComponent<Velocity>();
    // SYSTEM
    auto system = manager.createSystem<PhysicsSystem>(manager);
    // ENTITY
    for (auto i = 0; i < 10; ++i)
    {
        auto entity = manager.createEntity();
        manager.addComponent<Position>(entity);
        manager.addComponent<Velocity>(entity);
    }
    // LOOP
    auto dt = 1.0f / 60.0f;
    while (true) {
        system->update(dt);
    }
    return EXIT_SUCCESS;
}