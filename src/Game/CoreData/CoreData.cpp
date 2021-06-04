/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 04/06/2021 CoreData.cpp.cc
*/

#include "CoreData.hpp"

using namespace Game;

static const MyVector2 WIN_SIZE = {800, 600};
static const std::string WIN_TITLE = "BomberBlock";
static const RColor WIN_BACK = RColor::RBLACK;

static const MyVector3 CAM_POSITION = {300, 0, 100};
static const MyVector3 CAM_TARGET = {0, 0, 0};
static const MyVector3 CAM_UP = {0, 1, 0};

std::shared_ptr<raylib::Camera> CoreData::camera = nullptr;
std::shared_ptr<Engine::SystemManager> CoreData::_systemManager = nullptr;
std::shared_ptr<Engine::EntityManager> CoreData::entityManager = nullptr;
std::shared_ptr<Engine::SceneManager> CoreData::sceneManager = nullptr;
std::shared_ptr<raylib::Input> CoreData::eventManager = nullptr;

CoreData::CoreData() : _window(WIN_SIZE, WIN_TITLE, WIN_BACK)
{
    if (CoreData::_systemManager == nullptr)
        CoreData::_systemManager = std::make_unique<Engine::SystemManager>();
    if (CoreData::entityManager == nullptr)
        CoreData::entityManager = std::make_unique<Engine::EntityManager>(*CoreData::_systemManager);
    if (CoreData::sceneManager == nullptr)
        CoreData::sceneManager = std::make_unique<Engine::SceneManager>(*CoreData::entityManager);
    if (CoreData::eventManager == nullptr)
        CoreData::eventManager = std::make_unique<raylib::Input>();
    if (CoreData::camera == nullptr) {
        CoreData::camera = std::make_unique<raylib::Camera>(CAM_POSITION, CAM_TARGET, CAM_UP);
    }
}
