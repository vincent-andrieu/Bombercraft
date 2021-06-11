/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 11/06/2021 SkinChoiceScene.cpp.cc
*/

#include "SkinChoiceScene.hpp"
#include "Game/CoreData/CoreData.hpp"
#include "Systems/Render2D/Render2DSystem.hpp"
#include "Systems/Render3D/Render3DSystem.hpp"
#include "raylib.hpp"
#include "GUI/Factories/Button/ButtonFactory.hpp"
#include "GUI/Factories/Image/ImageFactory.hpp"
#include "Components/Render3D/Render3D.hpp"
#include "Components/StringChoice/StringChoice.hpp"
#include "Utilities/ProportionUtilities.hpp"
#include "Scenes/OptionsMenu/OptionsMenuScene.hpp"

using namespace Game;

const std::vector<std::string> SKINS{"Asset/Skin/Basic_Test.png",
    "Asset/Skin/Bloody_White.png",
    "Asset/Skin/Deep_Blue.png",
    "Asset/Skin/Cyber_White.png",
    "Asset/Skin/Happy_White.png",
    "Asset/Skin/Lava_Orange.png",
    "Asset/Skin/Prince_Gold.png",
    "Asset/Skin/Pure_Green.png",
    "Asset/Skin/Rebel_Black.png",
    "Asset/Skin/Revenge_Red.png",
    "Asset/Skin/Simple_Steve.png"};

static void previousHandler(Engine::Entity const)
{
    auto scene = CoreData::sceneManager->getCurrentScene();
    Engine::Entity model = scene->localEntities.getEntity("skin");
    Component::StringChoice &choice = CoreData::entityManager->getComponent<Component::StringChoice>(model);
    Component::Render3D &render = CoreData::entityManager->getComponent<Component::Render3D>(model);

    choice.prev();
    static_cast<raylib::Model *>(render.modele.get())->setTexture(choice.get());
}

static void nextHandler(Engine::Entity const)
{
    auto scene = CoreData::sceneManager->getCurrentScene();
    Engine::Entity model = scene->localEntities.getEntity("skin");
    Component::StringChoice &choice = CoreData::entityManager->getComponent<Component::StringChoice>(model);
    Component::Render3D &render = CoreData::entityManager->getComponent<Component::Render3D>(model);

    choice.next();
    static_cast<raylib::Model *>(render.modele.get())->setTexture(choice.get());
}

static void rotateHandler(Engine::EntityManager &em, Engine::SceneManager &, const Engine::Entity entity)
{
    Component::Render3D &render = em.getComponent<Component::Render3D>(entity);
    raylib::Model &model = *static_cast<raylib::Model *>(render.modele.get());

    raylib::MyVector3 rotation = model.getRotation();
    model.setRotation({rotation.a, rotation.b + 1, rotation.c});
}

static void applyHandler(Engine::Entity const)
{
    // TODO : apply change
    CoreData::sceneManager->setScene<OptionsMenuScene>();
}

Game::SkinChoiceScene::SkinChoiceScene() : Engine::AbstractScene(*CoreData::systemManager, *CoreData::entityManager)
{
}

void Game::SkinChoiceScene::open()
{
    ProportionUtilities my_utility(CoreData::settings->getMyVector2("WIN_SIZE"));
    CoreData::moveCamera(raylib::MyVector3(12, 0, 0), raylib::MyVector3(0, 0, 0));
    std::string modelPath = CoreData::settings->getString("CHARACTER_MODEL");
    const GUI::ButtonConfig buttonConfig = GUI::ButtonFactory::getStandardButtonConfig(raylib::MyVector2(80, 55));

    GUI::ImageFactory::create(this->localEntities, {0, 0}, {1280, 720}, "Asset/Background/skinchoice.png", true);
    GUI::ButtonFactory::create(
        this->localEntities, my_utility.getProportion({20, 80}), "leftButton", buttonConfig, "PREV", previousHandler);
    GUI::ButtonFactory::create(
        this->localEntities, my_utility.getProportion({80, 80}), "rightButton", buttonConfig, "NEXT", nextHandler);
    GUI::ButtonFactory::create(this->localEntities,
        my_utility.getProportion({50, 80}, {12, 1}, {100, 100}),
        "applyButton",
        buttonConfig,
        "APPLY",
        applyHandler);
    Engine::Entity skin = this->localEntities.createEntity("skin");
    CoreData::entityManager->addComponent<Component::Render3D>(
        skin, std::make_shared<raylib::Model>(SKINS[0], modelPath, raylib::MyVector3(0, -2, 0)));
    CoreData::entityManager->addComponent<Component::StringChoice>(skin, std::vector<std::string>(SKINS));
    CoreData::entityManager->addComponent<Engine::Timer>(
        skin, 0.005f, *CoreData::entityManager, *CoreData::sceneManager, rotateHandler);
}

void Game::SkinChoiceScene::update()
{
    auto &render2D = this->_systemManager.getSystem<System::Render2DSystem>();
    auto &render3D = this->_systemManager.getSystem<System::Render3DSystem>();
    auto &timer = this->_systemManager.getSystem<Engine::TimerSystem>();

    render2D.update();
    render3D.update();
    timer.update();
    this->eventDispatcher(this->_systemManager);
}
