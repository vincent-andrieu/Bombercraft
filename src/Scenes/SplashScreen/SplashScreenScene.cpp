/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 03/06/2021 SplashScreenScene.cpp.cc
*/

#include "SplashScreenScene.hpp"
#include "Systems/Hitbox/HitboxSystem.hpp"
#include "Components/Hitbox/Hitbox.hpp"
#include "GUI/Factories/Checkbox/CheckboxFactory.hpp"
#include "GUI/Factories/Countdown/CountdownFactory.hpp"
#include "GUI/Factories/Image/ImageFactory.hpp"
#include "GUI/Factories/Image/ImageSequenceFactory.hpp"
#include <thread>

using namespace Game;

/// [Test] - Event Handler
static const EventRequirement clickHandlerRequirements(evtMouse::LEFT | evtMouse::RIGHT);
static Component::eventScript clickHandler = [](const Engine::Entity) {
    // CoreData::entityManager
    // CoreData::sceneManager
    // CoreData::eventManager
    std::cout << "Clicked!!!" << std::endl;
};
static GUI::checkboxHandler checkboxHandler = [](UNUSED Engine::Entity, bool &value) {
    std::cout << "Checkbox: " << std::boolalpha << value << std::endl;
};

static const EventRequirement keyHandlerRequirements(0, false, {raylib::KeyBoard::IKEY_S}, {});
static Component::eventScript keyHandler = [](const Engine::Entity) {
    auto scene = CoreData::sceneManager->getCurrentScene();
    auto entity = scene->localEntities.createAnonymousEntity();

    CoreData::entityManager->addComponent<Component::Render2D>(entity,
        Component::render2dMapModels(
            {{"rect1", std::make_shared<raylib::Rectangle>(raylib::MyVector2(100, 100), raylib::MyVector2(20, 30))}}));
    std::cout << "Key S pressed !!!" << std::endl;
    // Change color of the cube:
    auto block = scene->localEntities.getEntity("redBlock");
    static_cast<raylib::Cuboid *>(CoreData::entityManager->getComponent<Component::Render3D>(block).modele.get())
        ->setColor(raylib::RColor::RGREEN);
};

/// --------------------------------------------------------------------------------------------

SplashScreenScene::SplashScreenScene(Engine::SystemManager &systemManager)
    : AbstractScene(systemManager, *Game::CoreData::entityManager)
{
}

static void task1(std::string msg)
{
    std::cout << "\tTASK 1 = " << msg << std::endl;
}

void SplashScreenScene::open()
{
    ///// FACTORIES
    GUI::ImageSequenceFactory::create(this->localEntities, {0, 0}, {800, 600}, "Asset/SplashScreen", "splashScreen", 0.05f);
}

void SplashScreenScene::update()
{
    try {
        auto &render2D = this->_systemManager.getSystem<System::Render2DSystem>();
        auto physics = this->_systemManager.getSystem<System::PhysicsSystem>();
        auto &timer = this->_systemManager.getSystem<Engine::TimerSystem>();
        auto render3D = this->_systemManager.getSystem<System::Render3DSystem>();
        auto hitbox = this->_systemManager.getSystem<System::HitboxSystem>();

        float dt = 1.0f / 10.0f;
        physics.update(dt);
        render3D.update();
        render2D.update();
        hitbox.update();
        timer.update();
        this->eventDispatcher(this->_systemManager);
    } catch (std::invalid_argument const &e) {
        std::cerr << e.what() << std::endl;
        exit(84); // TEMPORARY
    }
}