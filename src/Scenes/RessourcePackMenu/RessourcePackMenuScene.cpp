/*
 * EPITECH PROJECT, 2021
 * RessourcePackMenu
 * File description:
 * RessourcePackMenuScene.cpp - Created: 15/06/2021
 */

#include "RessourcePackMenuScene.hpp"
#include "Scenes/OptionsMenu/OptionsMenuScene.hpp"
#include "Game/Factories/KeyManagementFactory/KeyManagementFactory.hpp"

using namespace Game;
using namespace raylib;

static const Component::eventScript doneButtonHandler = [](const Engine::Entity &) {
    CoreData::sceneManager->setScene(CoreData::sceneManager->peekLastScene());
};

RessourcePackMenuScene::RessourcePackMenuScene(Engine::SystemManager &systemManager)
    : AbstractScene(systemManager, *Game::CoreData::entityManager)
{
}

void RessourcePackMenuScene::open()
{
    const MyVector2 &window_size = CoreData::settings->getMyVector2("WIN_SIZE");
    const ProportionUtilities resizer(window_size);
    GUI::ButtonConfig menuButtons = GUI::ButtonFactory::getMediumButtonConfig();

    GUI::ImageFactory::create(
        this->localEntities, raylib::MyVector2(0, 0), window_size, CoreData::settings->getString("STANDARD_BACKGROUND"), false);
    GUI::LabelFactory::createCentered(
        this->localEntities, resizer(50, 4), "Ressource pack", GUI::LabelFactory::getStandardLabelConfig());

    GUI::ButtonFactory::create(
        this->localEntities,
        resizer(25, 20),
        "desertButton",
        menuButtons,
        "Desert",
        [this](UNUSED const Engine::Entity &entity) {
            std::cout << "Desert" << std::endl;
        },
        true);
    GUI::ButtonFactory::create(
        this->localEntities,
        resizer(75, 20),
        "endButton",
        menuButtons,
        "End",
        [this](UNUSED const Engine::Entity &entity) {
            std::cout << "End" << std::endl;
        },
        true);
    GUI::ButtonFactory::create(
        this->localEntities,
        resizer(25, 30),
        "mountains",
        menuButtons,
        "Mountains",
        [this](UNUSED const Engine::Entity &entity) {
            std::cout << "Mountains" << std::endl;
        },
        true);
    GUI::ButtonFactory::create(
        this->localEntities,
        resizer(75, 30),
        "mushroom",
        menuButtons,
        "Mushroom",
        [this](UNUSED const Engine::Entity &entity) {
            std::cout << "Mushroom" << std::endl;
        },
        true);
    GUI::ButtonFactory::create(
        this->localEntities,
        resizer(25, 40),
        "nether",
        menuButtons,
        "Nether",
        [this](UNUSED const Engine::Entity &entity) {
            std::cout << "Nether" << std::endl;
        },
        true);
    GUI::ButtonFactory::create(
        this->localEntities,
        resizer(75, 40),
        "ocean",
        menuButtons,
        "Ocean",
        [this](UNUSED const Engine::Entity &entity) {
            std::cout << "Ocean" << std::endl;
        },
        true);
    GUI::ButtonFactory::create(
        this->localEntities,
        resizer(25, 50),
        "plains",
        menuButtons,
        "Plains",
        [this](UNUSED const Engine::Entity &entity) {
            std::cout << "Plains" << std::endl;
        },
        true);
    GUI::ButtonFactory::create(
        this->localEntities,
        resizer(75, 50),
        "snowyToundra",
        menuButtons,
        "Snowy",
        [this](UNUSED const Engine::Entity &entity) {
            std::cout << "Snowy" << std::endl;
        },
        true);

    GUI::ButtonFactory::create(this->localEntities, resizer(50, 90), "doneButton", menuButtons, "Done", doneButtonHandler, true);

    // KEYS
    std::unordered_map<raylib::KeyBoard, Component::eventScript> keyTriggers;
    keyTriggers.emplace(std::make_pair(raylib::KeyBoard::IKEY_ESCAPE, doneButtonHandler));
    Game::KeyManagementFactory::create(this->localEntities, keyTriggers);
}

void RessourcePackMenuScene::update()
{
    auto &render2DSystem = CoreData::systemManager->getSystem<System::Render2DSystem>();

    render2DSystem.update();
    this->eventDispatcher(this->_systemManager);
}