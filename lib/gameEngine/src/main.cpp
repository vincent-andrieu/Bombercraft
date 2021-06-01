/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 27/05/2021 main.cpp.c
*/

#include <iostream>
#include "GameEngine.hpp"

class RenderSystem : public Engine::AbstractSystem {
  public:
    RenderSystem(Engine::EntityManager &entityManager) : AbstractSystem(entityManager)
    {
        this->setRequirements<Engine::Position, Engine::Velocity>();
    }

    void update()
    {
        for (const Engine::Entity &entity : this->getManagedEntities()) {
            auto [position, velocity] = this->_entityManager.getComponents<Engine::Position, Engine::Velocity>(entity);

            std::cout << "Position: " << position.x << " - " << position.y << std::endl;
            std::cout << "Velocity: " << velocity.x << " - " << velocity.y << std::endl << std::endl;
        }
    }

    void onManagedEntityAdded(Engine::Entity entity)
    {
    }

    void onManagedEntityRemoved(Engine::Entity entity)
    {
    }
};

int main(void)
{
    // MANAGER
    auto systemManager = Engine::SystemManager();
    auto entityManager = Engine::EntityManager(systemManager);
    entityManager.registerComponent<Engine::Position>();
    entityManager.registerComponent<Engine::Velocity>();
    // SYSTEM
    auto system = systemManager.createSystem<Engine::PhysicsSystem>(entityManager);
    auto renderSystem = systemManager.createSystem<RenderSystem>(entityManager);
    // ENTITY
    for (auto i = 0; i < 10; ++i)
    {
        auto entity = entityManager.createEntity();
        entityManager.addComponent<Engine::Position>(entity);
        entityManager.addComponent<Engine::Velocity>(entity);
    }
    // LOOP
    auto dt = 1.0f / 60.0f;
    for (std::size_t i = 0; i < 1000; i++) {
        system->update(dt);
        renderSystem->update();

    }
    return EXIT_SUCCESS;
}