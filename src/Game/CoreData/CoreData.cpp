/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 04/06/2021 CoreData.cpp.cc
*/

#include "CoreData.hpp"

using namespace Game;

std::shared_ptr<raylib::Camera> CoreData::camera = nullptr;
std::shared_ptr<Engine::SystemManager> CoreData::_systemManager = nullptr;
std::shared_ptr<Engine::EntityManager> CoreData::entityManager = nullptr;
std::shared_ptr<Engine::SceneManager> CoreData::sceneManager = nullptr;
std::shared_ptr<raylib::Input> CoreData::eventManager = nullptr;

std::unique_ptr<ConfigFile> CoreData::settings = nullptr;
std::unique_ptr<raylib::Window> CoreData::_window = nullptr;

CoreData::CoreData()
{
    CoreData::settings = std::make_unique<ConfigFile>(CONFIG_FILE);
    CoreData::_window = std::make_unique<raylib::Window>(CoreData::settings->getMyVector2("WIN_SIZE"),
        CoreData::settings->getString("WIN_TITLE"), static_cast<raylib::RColor>(CoreData::settings->getInt("WIN_BACK")));
    if (CoreData::_systemManager == nullptr)
        CoreData::_systemManager = std::make_unique<Engine::SystemManager>();
    if (CoreData::entityManager == nullptr)
        CoreData::entityManager = std::make_unique<Engine::EntityManager>(*CoreData::_systemManager);
    if (CoreData::sceneManager == nullptr)
        CoreData::sceneManager = std::make_unique<Engine::SceneManager>();
    if (CoreData::eventManager == nullptr)
        CoreData::eventManager = std::make_unique<raylib::Input>();
    if (CoreData::camera == nullptr) {
        CoreData::camera = std::make_unique<raylib::Camera>(CoreData::settings->getMyVector3("CAM_POSITION"),
            CoreData::settings->getMyVector3("CAM_TARGET"), CoreData::settings->getMyVector3("CAM_UP"));
    }
}

CoreData::~CoreData()
{
    CoreData::settings.reset();
    CoreData::sceneManager.reset();
    CoreData::entityManager.reset();
    CoreData::_systemManager.reset();
    CoreData::camera.reset();
    CoreData::eventManager.reset();
}
