/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 04/06/2021 CoreData.cpp.cc
*/

#include "CoreData.hpp"

using namespace Game;

std::unique_ptr<raylib::Camera> CoreData::camera = nullptr;
std::unique_ptr<Engine::SystemManager> CoreData::systemManager = nullptr;
std::shared_ptr<Engine::EntityManager> CoreData::entityManager = nullptr;
std::shared_ptr<Engine::SceneManager> CoreData::sceneManager = nullptr;
std::shared_ptr<raylib::Input> CoreData::eventManager = nullptr;
std::unique_ptr<ConfigFile> CoreData::settings = nullptr;

std::unique_ptr<raylib::Window> CoreData::window = nullptr;
bool CoreData::_loop = true;

static const raylib::MyVector2 minimalWinSize(600, 400);
static const raylib::MyVector2 maximalWinSize(5000, 2500);

void CoreData::initWindow()
{
    const raylib::MyVector2 winSize(CoreData::settings->getMyVector2("WIN_SIZE"));

    if (winSize.a < minimalWinSize.a || winSize.b < minimalWinSize.b || winSize.a > maximalWinSize.a
        || winSize.b > maximalWinSize.b)
        throw ParserExceptions("Window size too extreme");
    CoreData::window = std::make_unique<raylib::Window>(
        winSize, CoreData::settings->getString("WIN_TITLE"), static_cast<raylib::RColor>(CoreData::settings->getInt("WIN_BACK")));
}

CoreData::CoreData()
{
    CoreData::settings = std::make_unique<ConfigFile>(CONFIG_FILE);

    CoreData::initWindow();
    CoreData::window->open();
    if (CoreData::systemManager == nullptr)
        CoreData::systemManager = std::make_unique<Engine::SystemManager>();
    if (CoreData::entityManager == nullptr)
        CoreData::entityManager = std::make_shared<Engine::EntityManager>(*CoreData::systemManager);
    if (CoreData::sceneManager == nullptr)
        CoreData::sceneManager = std::make_shared<Engine::SceneManager>();
    if (CoreData::eventManager == nullptr)
        CoreData::eventManager = std::make_shared<raylib::Input>();
    if (CoreData::camera == nullptr) {
        CoreData::camera = std::make_unique<raylib::Camera>(CoreData::settings->getMyVector3("CAM_POSITION"),
            CoreData::settings->getMyVector3("CAM_TARGET"),
            CoreData::settings->getMyVector3("CAM_UP"));
    }
}

void CoreData::quit()
{
    CoreData::_loop = false;
}

CoreData::~CoreData()
{
    CoreData::settings.reset();
    CoreData::sceneManager.reset();
    CoreData::entityManager.reset();
    CoreData::systemManager.reset();
    CoreData::camera.reset();
    CoreData::eventManager.reset();
    raylib::Font::_loaderManager.reset();
    raylib::Model::_loaderManager.reset();
    raylib::Texture::_loaderManager.reset();
    CoreData::window->close();
}

void CoreData::moveCamera(const raylib::MyVector3 &position, const raylib::MyVector3 &target)
{
    CoreData::camera->setPosition(position);
    CoreData::camera->setTarget(target);
}