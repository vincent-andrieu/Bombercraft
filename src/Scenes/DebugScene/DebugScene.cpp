/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 03/06/2021 DebugScene.cpp.cc
*/

#include "DebugScene.hpp"
#include "Systems/Hitbox/HitboxSystem.hpp"
#include "Components/Hitbox/Hitbox.hpp"

using namespace Game;

/// [Test] - Event Handler
static Component::eventScript clickHandler = [](const Engine::Entity){
    // DataCore::entityManager
    // DataCore::sceneManager
    // DataCore::eventManager
    std::cout << "Clicked!!!\n";
};

DebugScene::DebugScene(Engine::SystemManager &systemManager,
    Engine::EntityManager &entityManager, raylib::Input &eventManager)
    : AbstractScene(systemManager, entityManager), SceneWithEvents(eventManager)
{
    /// ENTITIES - CREATION
    auto rect = this->createLocalEntity();
    _entityManager.addComponent<Component::Render2D>(rect,
        std::make_shared<raylib::Rectangle>((raylib::MyVector2){10, 10}, (raylib::MyVector2){20, 20})
    );
    auto block = this->createLocalEntity();
    raylib::MyVector3 blockPos(0, 20, 0);
    _entityManager.addComponent<Component::Render3D>(block,
        std::make_shared<raylib::Cuboid>(nullptr, blockPos, (raylib::MyVector3){50, 50, 50}, raylib::RColor::RRED)
    );
    _entityManager.addComponent<Component::Hitbox>(
        block, blockPos, (raylib::MyVector3){50, 50, 50}, [](const Engine::Entity &fromEntity, const Engine::Entity &toEntity) {
          auto cubeComponent = Game::Core::entityManager.getComponent<Component::Render3D>(fromEntity);
          auto cube = static_cast<raylib::Cuboid *>(cubeComponent.modele.get());

          cube->setColor(raylib::RColor::RBLUE);
        });
    auto moveableEntity = this->createLocalEntity();
    raylib::MyVector3 moveableEntityPos(20, 20, 0);
    this->_entityManager.addComponent<Component::Render3D>(moveableEntity,
        std::make_shared<raylib::Cuboid>(nullptr, moveableEntityPos, (raylib::MyVector3){50, 50, 50}, raylib::RColor::RMAGENTA));
    this->_entityManager.addComponent<Engine::Position>(moveableEntity, 100, 20);
    this->_entityManager.addComponent<Engine::Velocity>(moveableEntity, 20, 0);
    this->_entityManager.addComponent<Component::Hitbox>(moveableEntity, moveableEntityPos, (raylib::MyVector3){50, 50, 50},
         [](const Engine::Entity &fromEntity, const Engine::Entity &toEntity) {
     });
    _entityManager.addComponent<Component::ClickEvent>(block, clickHandler,
        std::make_shared<EventRequirement>(evtMouse::LEFT | evtMouse::RIGHT));
}

void DebugScene::update()
{
    auto physics = this->_systemManager.getSystem<Engine::PhysicsSystem>();
    auto render2D = this->_systemManager.getSystem<System::Render2DSystem>();
    auto render3D = this->_systemManager.getSystem<System::Render3DSystem>();
    auto hitbox = this->_systemManager.getSystem<System::HitboxSystem>();

    float dt = 1.0f / 10.0f;
    physics.update(dt);
    render3D.update();
    render2D.update();
    hitbox.update();
    this->eventDispatcher(_systemManager);
}