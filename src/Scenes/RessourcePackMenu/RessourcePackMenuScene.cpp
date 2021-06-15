/*
 * EPITECH PROJECT, 2021
 * RessourcePackMenu
 * File description:
 * RessourcePackMenuScene.cpp - Created: 15/06/2021
 */

#include <array>
#include "RessourcePackMenuScene.hpp"
#include "Scenes/OptionsMenu/OptionsMenuScene.hpp"
#include "Game/Factories/KeyManagementFactory/KeyManagementFactory.hpp"
#include "Components/Option/OptionComponent.hpp"

using namespace Game;
using namespace raylib;

extern std::unique_ptr<Game::Core> core;

static const Component::eventScript doneButtonHandler = [](const Engine::Entity &) {
    CoreData::sceneManager->setScene(CoreData::sceneManager->peekLastScene());
};

RessourcePackMenuScene::RessourcePackMenuScene(Engine::SystemManager &systemManager)
    : AbstractScene(systemManager, *Game::CoreData::entityManager)
{
}

static const std::array<string, 8> ressourcePackPaths({
    "Asset/Texture/Desert/",
    "Asset/Texture/End/",
    "Asset/Texture/Mountains/",
    "Asset/Texture/MushroomFields/",
    "Asset/Texture/Nether/",
    "Asset/Texture/Ocean/",
    "Asset/Texture/Plains/",
    "Asset/Texture/SnowyToundra/",
});

void RessourcePackMenuScene::open()
{
    const MyVector2 &window_size = CoreData::settings->getMyVector2("WIN_SIZE");
    const ProportionUtilities resizer(window_size);
    GUI::ButtonConfig menuButtons = GUI::ButtonFactory::getMediumButtonConfig();
    const Engine::Entity &optionEntity = core->globalEntities.getEntity("options");

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
        [optionEntity](const Engine::Entity &) {
            CoreData::entityManager->getComponent<Component::OptionComponent>(optionEntity).ressourcePack = ressourcePackPaths[0];
        },
        true);
    GUI::ButtonFactory::create(
        this->localEntities,
        resizer(75, 20),
        "endButton",
        menuButtons,
        "End",
        [optionEntity](const Engine::Entity &) {
            CoreData::entityManager->getComponent<Component::OptionComponent>(optionEntity).ressourcePack = ressourcePackPaths[1];
        },
        true);
    GUI::ButtonFactory::create(
        this->localEntities,
        resizer(25, 30),
        "mountains",
        menuButtons,
        "Mountains",
        [optionEntity](const Engine::Entity &) {
            CoreData::entityManager->getComponent<Component::OptionComponent>(optionEntity).ressourcePack = ressourcePackPaths[2];
        },
        true);
    GUI::ButtonFactory::create(
        this->localEntities,
        resizer(75, 30),
        "mushroom",
        menuButtons,
        "Mushroom",
        [optionEntity](const Engine::Entity &) {
            CoreData::entityManager->getComponent<Component::OptionComponent>(optionEntity).ressourcePack = ressourcePackPaths[3];
        },
        true);
    GUI::ButtonFactory::create(
        this->localEntities,
        resizer(25, 40),
        "nether",
        menuButtons,
        "Nether",
        [optionEntity](const Engine::Entity &) {
            CoreData::entityManager->getComponent<Component::OptionComponent>(optionEntity).ressourcePack = ressourcePackPaths[4];
        },
        true);
    GUI::ButtonFactory::create(
        this->localEntities,
        resizer(75, 40),
        "ocean",
        menuButtons,
        "Ocean",
        [optionEntity](const Engine::Entity &) {
            CoreData::entityManager->getComponent<Component::OptionComponent>(optionEntity).ressourcePack = ressourcePackPaths[5];
        },
        true);
    GUI::ButtonFactory::create(
        this->localEntities,
        resizer(25, 50),
        "plains",
        menuButtons,
        "Plains",
        [optionEntity](const Engine::Entity &) {
            CoreData::entityManager->getComponent<Component::OptionComponent>(optionEntity).ressourcePack = ressourcePackPaths[6];
        },
        true);
    GUI::ButtonFactory::create(
        this->localEntities,
        resizer(75, 50),
        "snowyToundra",
        menuButtons,
        "Snowy",
        [optionEntity](const Engine::Entity &) {
            CoreData::entityManager->getComponent<Component::OptionComponent>(optionEntity).ressourcePack = ressourcePackPaths[7];
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