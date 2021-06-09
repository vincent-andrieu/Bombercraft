/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 03/06/2021 DebugScene.cpp.cc
*/

#include "DebugScene.hpp"
#include "Systems/Hitbox/HitboxSystem.hpp"
#include "Components/Hitbox/Hitbox.hpp"
#include "GUI/Factories/Button/ButtonFactory.hpp"
#include "GUI/Factories/Checkbox/CheckboxFactory.hpp"
#include "GUI/Factories/Countdown/CountdownFactory.hpp"

using namespace Game;

/// [Test] - Event Handler
static const EventRequirement clickHandlerRequirements(evtMouse::LEFT | evtMouse::RIGHT);
static Component::eventScript clickHandler = [](const Engine::Entity) {
    // CoreData::entityManager
    // CoreData::sceneManager
    // CoreData::eventManager
    std::cout << "Clicked!!!" << std::endl;
};
static Component::eventScript checkboxHandler = [](const Engine::Entity) {
    std::cout << "Checkbox!!!" << std::endl;
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

DebugScene::DebugScene(Engine::SystemManager &systemManager) : AbstractScene(systemManager, *Game::CoreData::entityManager)
{
}

void DebugScene::open()
{
    std::cout << "----OPEN\n";
    /// ENTITIES - CREATION
    auto rect = this->localEntities.createEntity("whiteRectangle");
    this->_entityManager.addComponent<Component::Render2D>(rect,
           Component::render2dMapModels{
            {"recTest", std::make_shared<raylib::Rectangle>(raylib::MyVector2(10, 10), raylib::MyVector2(20, 20))}
    });
    // ------------
    auto block = this->localEntities.createEntity("redBlock");
    raylib::MyVector3 blockPos(0, 20, 0);
    this->_entityManager.addComponent<Component::Render3D>(
        block, std::make_shared<raylib::Cuboid>(nullptr, blockPos, raylib::MyVector3(50, 50, 50), raylib::RColor::RRED));
    this->_entityManager.addComponent<Component::Hitbox>(block, blockPos, raylib::MyVector3(50, 50, 50),
        [](const Engine::Entity &fromEntity, UNUSED const Engine::Entity &toEntity) {
            auto cubeComponent = Game::Core::entityManager->getComponent<Component::Render3D>(fromEntity);
            auto cube = static_cast<raylib::Cuboid *>(cubeComponent.modele.get());

            cube->setColor(raylib::RColor::RBLUE);
        });
    // ------------
    auto moveableEntity = this->localEntities.createEntity("movableEntity");
    raylib::MyVector3 moveableEntityPos(20, 20, 0);
    this->_entityManager.addComponent<Component::Render3D>(moveableEntity,
       std::make_shared<raylib::Cuboid>(nullptr, moveableEntityPos, raylib::MyVector3(50, 50, 50), raylib::RColor::RMAGENTA));
    this->_entityManager.addComponent<Engine::Position>(moveableEntity, 100.0f, 20.0f);
    this->_entityManager.addComponent<Engine::Velocity>(moveableEntity, 20.0f, 0.0f);
    this->_entityManager.addComponent<Component::Hitbox>(moveableEntity, moveableEntityPos, raylib::MyVector3(50, 50, 50),
        [](UNUSED const Engine::Entity &fromEntity, UNUSED const Engine::Entity &toEntity) {
        });
    // Events
    this->_entityManager.addComponent<Component::ClickEvent>(block, clickHandler, clickHandlerRequirements);
    this->_entityManager.addComponent<Component::KeyEvent>(block, keyHandler, keyHandlerRequirements);

    ///// FACTORIES
    GUI::CheckboxFactory::create(this->localEntities, raylib::MyVector2(50, 50), checkboxHandler);
    GUI::CountdownFactory::create(this->localEntities, {350, 0}, 60, "test");
    GUI::ButtonFactory::create(
        this->localEntities, {20, 20}, "my_button_label", GUI::ButtonFactory::getStandardButtonConfig(), "my_button_text");
}

void DebugScene::update()
{
    try {
        auto &render2D = this->_systemManager.getSystem<System::Render2DSystem>();
        auto physics = this->_systemManager.getSystem<Engine::PhysicsSystem>();
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