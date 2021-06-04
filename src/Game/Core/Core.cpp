/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 02/06/2021 Core.cpp.cc
*/

#include "Core.hpp"

using namespace Game;

static const MyVector2 WIN_SIZE = {800, 600};
static const std::string WIN_TITLE = "BomberBlock";
static const RColor WIN_BACK = RColor::RBLACK;

static const MyVector3 CAM_POSITION = {200, 0, 200};
static const MyVector3 CAM_TARGET = {0, 0, 0};
static const MyVector3 CAM_UP = {0, 1, 0};

std::unique_ptr<raylib::Camera> Core::camera = std::make_unique<raylib::Camera>(CAM_POSITION, CAM_TARGET, CAM_UP);
Engine::SystemManager Core::_systemManager = Engine::SystemManager();
Engine::EntityManager Core::entityManager = Engine::EntityManager(Core::_systemManager);
Engine::SceneManager Core::sceneManager = Engine::SceneManager(Core::entityManager);

Core::Core() : _window(WIN_SIZE, WIN_TITLE, WIN_BACK)
{
    /// COMPONENTS - DEFINITION
    this->entityManager.registerComponent<Component::Render2D>();
    this->entityManager.registerComponent<Component::Render3D>();
    this->entityManager.registerComponent<Engine::Position>();
    this->entityManager.registerComponent<Engine::Velocity>();
    this->entityManager.registerComponent<Component::Hitbox>();
    /// SYSTEMS - CREATION
    this->_systemManager.createSystem<Engine::PhysicsSystem>(this->entityManager);
    this->_systemManager.createSystem<System::HitboxSystem>();
    this->_systemManager.createSystem<System::Render3DSystem>(this->entityManager);
    this->_systemManager.createSystem<System::Render2DSystem>(this->entityManager);
    // SCENES - CREATION
    this->sceneManager.createScene<DebugScene>(this->_systemManager, this->entityManager);
}

void Core::loop()
{
    this->_window.open();
    while (this->_window.isOpen()) {
        this->_window.clear();
        this->sceneManager.run();
        this->_window.refresh();
    }
    this->_window.close();
}
