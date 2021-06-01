/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 27/05/2021 main.cpp.c
*/

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cstdlib>
#include "GameEngine.hpp"
#include "raylib.hpp"

struct CubeComponent : public Engine::Component<CubeComponent>
{
    CubeComponent() : render(nullptr, {0, 0, 0}, {10, 10, 5}, raylib::RColor::RRED) {
    }

    raylib::Cuboid render;
};

class RenderSystem : public Engine::AbstractSystem {
  public:
    RenderSystem(Engine::EntityManager &entityManager) : AbstractSystem(entityManager)
    {
        this->setRequirements<Engine::Position, Engine::Velocity>();
    }

    void update()
    {
        for (const Engine::Entity &entity : this->getManagedEntities()) {
            auto [position, cube] = this->_entityManager.getComponents<Engine::Position, CubeComponent>(entity);

            cube.render.setPosition({position.x, position.y, 0});
            cube.render.draw();
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
    srand(time(NULL));
    raylib::Window window({800, 400}, "Debug", raylib::RColor::RWHITE);
    raylib::Camera camera({300, 0, 300}, {0, 100, 0}, {0, 1, 0});
    window.open();

    // MANAGER
    auto systemManager = Engine::SystemManager();
    auto entityManager = Engine::EntityManager(systemManager);
    entityManager.registerComponent<Engine::Position>();
    entityManager.registerComponent<Engine::Velocity>();
    entityManager.registerComponent<CubeComponent>();
    // SYSTEM
    auto system = systemManager.createSystem<Engine::PhysicsSystem>(entityManager);
    auto renderSystem = systemManager.createSystem<RenderSystem>(entityManager);
    renderSystem->setRequirements<CubeComponent, Engine::Position>();
    // ENTITY
    for (auto i = 0; i < 10; ++i)
    {
        auto entity = entityManager.createEntity();
        float pos = static_cast<float>(rand() % 2000);
        entityManager.addComponent<Engine::Position>(entity, pos, 0);
        entityManager.addComponent<CubeComponent>(entity);
        entityManager.addComponent<Engine::Velocity>(entity, 0, 1);
    }
    // LOOP
    auto dt = 1.0f / 100.0f;
    while (window.isOpen()) {
        system->update(dt);
        window.clear();
        camera.start();
        renderSystem->update();
        camera.stop();

        window.refresh();
    }
    window.close();
    return EXIT_SUCCESS;
}