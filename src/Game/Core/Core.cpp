/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 02/06/2021 Core.cpp.cc
*/

#include "Core.hpp"

using namespace Game;

static const std::string CONFIG_FILE = "bomberman.config";

std::unique_ptr<raylib::Camera> Core::camera = nullptr;

Core::Core()
    : _settings(CONFIG_FILE), _window(_settings.getMyVector2("WIN_SIZE"), _settings.getString("WIN_TITLE"), static_cast<RColor>(_settings.getInt("WIN_BACK"))),
    _entityManager(_systemManager), _sceneManager(_entityManager)
{
    /// COMPONENTS - DEFINITION
    _entityManager.registerComponent<Component::Render2D>();
    _entityManager.registerComponent<Component::Render3D>();
    _entityManager.registerComponent<Component::ClickEvent>();
    _entityManager.registerComponent<Component::KeyEvent>();
    _entityManager.registerComponent<Component::MouseMoveEvent>();
    /// SYSTEMS - CREATION
    _systemManager.createSystem<System::Render3DSystem>(_entityManager);
    _systemManager.createSystem<System::Render2DSystem>(_entityManager);
    _systemManager.createSystem<System::ClickEventSystem>(_entityManager);
    _systemManager.createSystem<System::KeyEventSystem>(_entityManager);
    _systemManager.createSystem<System::MouseEventSystem>(_entityManager);
    // SCENES - CREATION
    _sceneManager.createScene<DebugScene>(_systemManager, _entityManager, _eventManager);
    this->camera = std::make_unique<raylib::Camera>(_settings.getMyVector3("CAM_POSITION"), _settings.getMyVector3("CAM_TARGET"), _settings.getMyVector3("CAM_UP"));
}

Core::~Core()
{
}

void Core::loop()
{
    this->_window.open();
    while (this->_window.isOpen()) {
        this->_window.clear();
        this->_sceneManager.run();
        this->_window.refresh();
    }
    this->_window.close();
}
