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
static const EventRequirement clickHandlerRequirements(evtMouse::LEFT | evtMouse::RIGHT);
static Component::eventScript clickHandler = [](const Engine::Entity) {
    // CoreData::entityManager
    // CoreData::sceneManager
    // CoreData::eventManager
    std::cout << "Clicked!!!" << std::endl;
};

static const EventRequirement keyHandlerRequirements(0, false, {raylib::KeyBoard::IKEY_S}, {});
static Component::eventScript keyHandler = [](const Engine::Entity) {
    auto scene = CoreData::sceneManager->getCurrentScene();
    auto entity = scene->createLocalEntity();

    CoreData::entityManager->addComponent<Component::Render2D>(
        entity, std::make_shared<raylib::Rectangle>((raylib::MyVector2){100, 100}, (raylib::MyVector2){20, 30}));
    std::cout << "Key S pressed !!!" << std::endl;
};

DebugScene::DebugScene(Engine::SystemManager &systemManager, Engine::EntityManager &entityManager, raylib::Input &eventManager)
    : AbstractScene(systemManager, entityManager), SceneWithEvents(eventManager)
{
    /// ENTITIES - CREATION
    auto rect = this->createLocalEntity();
    _entityManager.addComponent<Component::Render2D>(
        rect, std::make_shared<raylib::Rectangle>((raylib::MyVector2){10, 10}, (raylib::MyVector2){20, 20}));

    auto block = this->createLocalEntity();
    raylib::MyVector3 blockPos(0, 20, 0);
    _entityManager.addComponent<Component::Render3D>(block,
        std::make_shared<raylib::Cuboid>(
            nullptr, blockPos, (raylib::MyVector3){50, 50, 50}, raylib::RColor::RRED));
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
    // Events
    _entityManager.addComponent<Component::ClickEvent>(block, clickHandler, clickHandlerRequirements);
    _entityManager.addComponent<Component::KeyEvent>(block, keyHandler, keyHandlerRequirements);
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