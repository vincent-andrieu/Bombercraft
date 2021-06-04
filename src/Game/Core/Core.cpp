/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 02/06/2021 Core.cpp.cc
*/

#include "Core.hpp"

using namespace Game;

static const std::string CONFIG_FILE = "bomberman.config";

Engine::SystemManager Core::_systemManager = Engine::SystemManager();
Engine::EntityManager Core::entityManager = Engine::EntityManager(Core::_systemManager);
Engine::SceneManager Core::sceneManager = Engine::SceneManager(Core::entityManager);
std::unique_ptr<raylib::Camera> Core::camera = nullptr;

Core::Core()
    : _settings(CONFIG_FILE), _window(_settings.getMyVector2("WIN_SIZE"), _settings.getString("WIN_TITLE"),
                                  static_cast<RColor>(_settings.getInt("WIN_BACK")))
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
    this->camera = std::make_unique<raylib::Camera>(
        _settings.getMyVector3("CAM_POSITION"), _settings.getMyVector3("CAM_TARGET"), _settings.getMyVector3("CAM_UP"));
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
