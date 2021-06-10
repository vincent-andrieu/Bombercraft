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
#include "GUI/Factories/Image/ImageFactory.hpp"
#include "GUI/Factories/Label/LabelFactory.hpp"
#include "GUI/Factories/TextInput/TextInputFactory.hpp"
#include "GUI/Factories/KeyInput/KeyInputFactory.hpp"
#include "GUI/Factories/Checkbox/CheckboxFactory.hpp"
#include "GUI/Factories/Slider/SliderFactory.hpp"
#include "Components/FocusEvent/ClickFocusEvent.hpp"
#include "GUI/Factories/Countdown/CountdownFactory.hpp"
#include "utilities.hpp"

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

    Engine::Entity chrono = scene->localEntities.getEntity("chrono");
    Engine::Timer &timer = CoreData::entityManager->getComponent<Engine::Timer>(chrono);

    if (timer.isPaused()) {
        timer.resume();
        std::cout << "Resume counter" << std::endl;
    } else {
        timer.pause();
        std::cout << "Pause counter" << std::endl;
    }
};

/// --------------------------------------------------------------------------------------------

DebugScene::DebugScene(Engine::SystemManager &systemManager) : AbstractScene(systemManager, *Game::CoreData::entityManager)
{
}

void DebugScene::open()
{
    std::cout << "----OPEN\n";
    const raylib::MyVector2 position(10, 70);
    GUI::LabelConfig config = {
        .fontSize = 24, .fontColor = raylib::RColor::RBLUE, .fontPath = "./Asset/Font/MinecraftItalic.ttf"};
    GUI::TextInputConfig TextInputConfig = {.size = raylib::MyVector2(152, 27),
        .color = raylib::RColor::RBLACK,
        .borderSize = 2,
        .borderColor = raylib::RColor::RGRAY,
        .maxChar = 16,
        .textPositionOffset = raylib::MyVector2(5, 5)};
    GUI::LabelConfig labelTextInput = {
        .fontSize = 16, .fontColor = raylib::RColor::RWHITE, .fontPath = "./Asset/Font/MinecraftRegular.ttf"};
    GUI::TextInputDynConf input1 = {.position = raylib::MyVector2(300, 75), .name = "input1", "player name"};
    GUI::TextInputDynConf input2 = {.position = raylib::MyVector2(500, 75), .name = "input2", "save name"};
    GUI::KeyInputDynConf keyInput1 = {.position = raylib::MyVector2(300, 175), .name = "keyinput1"};

    /// ENTITIES - CREATION
    auto rect = this->localEntities.createEntity("whiteRectangle");
    this->_entityManager.addComponent<Component::Render2D>(rect,
        Component::render2dMapModels{
            {"recTest", std::make_shared<raylib::Rectangle>(raylib::MyVector2(10, 10), raylib::MyVector2(20, 20))}});
    // ------------
    auto block = this->localEntities.createEntity("redBlock");
    raylib::MyVector3 blockPos(-40, -50, 0);
    this->_entityManager.addComponent<Component::Render3D>(
        block, std::make_shared<raylib::Cuboid>(nullptr, blockPos, raylib::MyVector3(10, 10, 10), raylib::RColor::RRED));
    this->_entityManager.addComponent<Component::Hitbox>(block,
        blockPos,
        raylib::MyVector3(10, 10, 10),
        [](const Engine::Entity &fromEntity, UNUSED const Engine::Entity &toEntity) {
            auto cubeComponent = Game::Core::entityManager->getComponent<Component::Render3D>(fromEntity);

            cubeComponent.modele->setColor(raylib::RColor::RBLUE);
        });
    // ------------
    auto moveableEntity = this->localEntities.createEntity("movableEntity");
    raylib::MyVector3 moveableEntityPos(-70, -50, 0);
    this->_entityManager.addComponent<Component::Render3D>(moveableEntity,
        std::make_shared<raylib::Cuboid>(nullptr, moveableEntityPos, raylib::MyVector3(10, 10, 10), raylib::RColor::RMAGENTA));
    this->_entityManager.addComponent<Engine::Position>(moveableEntity, 100.0f, 20.0f);
    this->_entityManager.addComponent<Engine::Velocity>(moveableEntity, 1.0f, 0.0f);
    this->_entityManager.addComponent<Component::Hitbox>(moveableEntity,
        moveableEntityPos,
        raylib::MyVector3(10, 10, 10),
        [](UNUSED const Engine::Entity &fromEntity, UNUSED const Engine::Entity &toEntity) {
        });
    // Events
    this->_entityManager.addComponent<Component::ClickEvent>(block, clickHandler, clickHandlerRequirements);
    this->_entityManager.addComponent<Component::KeyEvent>(block, keyHandler, keyHandlerRequirements);

    ///// FACTORIES
    GUI::CheckboxFactory::create(this->localEntities, raylib::MyVector2(50, 50), checkboxHandler);
    GUI::CountdownFactory::create(this->localEntities, raylib::MyVector2(350, 0), 60, "chrono");
    GUI::ImageFactory::create(this->localEntities,
        raylib::MyVector2(200, 200),
        raylib::MyVector2(50, 50),
        "Asset/Interface/PowerUpBox.png",
        "testImage");
    GUI::LabelFactory::create(this->localEntities, raylib::MyVector2(200, 200), "Hello World", config);
    GUI::TextInputFactory::create(this->localEntities, input1, labelTextInput);
    GUI::TextInputFactory::create(this->localEntities, input2, TextInputConfig, labelTextInput);
    GUI::KeyInputFactory::create(this->localEntities, keyInput1, labelTextInput);
    std::cout << "---- BLOCK\n";
    GUI::BlockFactory::create(
        this->localEntities, raylib::MyVector3(0, 0, 0), GUI::BlockFactory::BlockType::BLOCK_BOMB, "myBlock");
    GUI::SliderFactory::create(
        this->localEntities,
        raylib::MyVector2(500, 160),
        [](const Engine::Entity entity, GUI::sliderValue &value) {
            std::cout << "Slider: entity=" << entity << ", value=" << value << std::endl;
        },
        "Value: ",
        raylib::MyVector2(60, 10),
        0,
        100,
        60);
    GUI::ButtonFactory::create(localEntities, {20, 20}, "my_label", GUI::ButtonFactory::getStandardButtonConfig(), "button_text");
}

void DebugScene::update()
{
    try {
        auto &render2D = this->_systemManager.getSystem<System::Render2DSystem>();
        auto &singleRender2D = this->_systemManager.getSystem<System::singleRender2DSystem>();
        //        auto physics = this->_systemManager.getSystem<Engine::PhysicsSystem>();
        auto &timer = this->_systemManager.getSystem<Engine::TimerSystem>();
        auto render3D = this->_systemManager.getSystem<System::Render3DSystem>();
        auto hitbox = this->_systemManager.getSystem<System::HitboxSystem>();

        float dt = 1.0f / 10.0f;
        //        physics.update(dt);
        render3D.update();
        singleRender2D.update();
        render2D.update();
        hitbox.update();
        timer.update();
        this->eventDispatcher(this->_systemManager);
    } catch (std::invalid_argument const &e) {
        std::cerr << e.what() << std::endl;
        exit(84); // TEMPORARY
    }
}