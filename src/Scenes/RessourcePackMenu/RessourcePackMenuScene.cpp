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

static const uint nbrRessourcePacks = 8;
static const std::array<string, nbrRessourcePacks> ressourcePackPaths({
    "Asset/Texture/Desert/",
    "Asset/Texture/End/",
    "Asset/Texture/Mountains/",
    "Asset/Texture/MushroomFields/",
    "Asset/Texture/Nether/",
    "Asset/Texture/Ocean/",
    "Asset/Texture/Plains/",
    "Asset/Texture/SnowyToundra/",
});

static const std::array<raylib::MyVector2, nbrRessourcePacks> ressourcePackPositions({
    raylib::MyVector2(25, 20),
    raylib::MyVector2(75, 20),
    raylib::MyVector2(25, 30),
    raylib::MyVector2(75, 30),
    raylib::MyVector2(25, 40),
    raylib::MyVector2(75, 40),
    raylib::MyVector2(25, 50),
    raylib::MyVector2(75, 50),
});

static void setRessourcePack(const Engine::Entity &optionEntity,
    const Engine::Entity &selectedEntity,
    const ProportionUtilities &resizer,
    const uint index)
{
    CoreData::entityManager->getComponent<Component::OptionComponent>(optionEntity).ressourcePack = ressourcePackPaths[index];
    static_cast<raylib::Texture *>(CoreData::entityManager->getComponent<Component::Render2D>(selectedEntity).get("image").get())
        ->setPosition(resizer(ressourcePackPositions[index])
            + raylib::MyVector2(150, -1 * (GUI::ButtonFactory::getMediumButtonConfig().size.b / 2 + 10)));
}

void RessourcePackMenuScene::open()
{
    const MyVector2 &window_size = CoreData::settings->getMyVector2("WIN_SIZE");
    const ProportionUtilities resizer(window_size);
    GUI::ButtonConfig menuButtons = GUI::ButtonFactory::getMediumButtonConfig();
    const Engine::Entity optionEntity = core->globalEntities.getEntity("options");

    GUI::ImageFactory::create(
        this->localEntities, raylib::MyVector2(0, 0), window_size, CoreData::settings->getString("STANDARD_BACKGROUND"), false);
    GUI::LabelFactory::createCentered(
        this->localEntities, resizer(50, 4), "Ressource pack", GUI::LabelFactory::getStandardLabelConfig());
    Engine::Entity selectedEntity = GUI::ImageFactory::create(this->localEntities,
        resizer(ressourcePackPositions[this->_getSelectedRessourcePackIndex(optionEntity)])
            + raylib::MyVector2(150, -1 * (menuButtons.size.b / 2 + 10)),
        raylib::MyVector2(menuButtons.size.b + 60, menuButtons.size.b + 10),
        "Asset/Interface/check.png",
        true,
        "selected");

    GUI::ButtonFactory::create(
        this->localEntities,
        resizer(ressourcePackPositions[0]),
        "desertButton",
        menuButtons,
        "Desert",
        [optionEntity, selectedEntity, resizer](const Engine::Entity &) {
            setRessourcePack(optionEntity, selectedEntity, resizer, 0);
        },
        true);
    GUI::ButtonFactory::create(
        this->localEntities,
        resizer(ressourcePackPositions[1]),
        "endButton",
        menuButtons,
        "End",
        [optionEntity, selectedEntity, resizer](const Engine::Entity &) {
            setRessourcePack(optionEntity, selectedEntity, resizer, 1);
        },
        true);
    GUI::ButtonFactory::create(
        this->localEntities,
        resizer(ressourcePackPositions[2]),
        "mountains",
        menuButtons,
        "Mountains",
        [optionEntity, selectedEntity, resizer](const Engine::Entity &) {
            setRessourcePack(optionEntity, selectedEntity, resizer, 2);
        },
        true);
    GUI::ButtonFactory::create(
        this->localEntities,
        resizer(ressourcePackPositions[3]),
        "mushroom",
        menuButtons,
        "Mushroom",
        [optionEntity, selectedEntity, resizer](const Engine::Entity &) {
            setRessourcePack(optionEntity, selectedEntity, resizer, 3);
        },
        true);
    GUI::ButtonFactory::create(
        this->localEntities,
        resizer(ressourcePackPositions[4]),
        "nether",
        menuButtons,
        "Nether",
        [optionEntity, selectedEntity, resizer](const Engine::Entity &) {
            setRessourcePack(optionEntity, selectedEntity, resizer, 4);
        },
        true);
    GUI::ButtonFactory::create(
        this->localEntities,
        resizer(ressourcePackPositions[5]),
        "ocean",
        menuButtons,
        "Ocean",
        [optionEntity, selectedEntity, resizer](const Engine::Entity &) {
            setRessourcePack(optionEntity, selectedEntity, resizer, 5);
        },
        true);
    GUI::ButtonFactory::create(
        this->localEntities,
        resizer(ressourcePackPositions[6]),
        "plains",
        menuButtons,
        "Plains",
        [optionEntity, selectedEntity, resizer](const Engine::Entity &) {
            setRessourcePack(optionEntity, selectedEntity, resizer, 6);
        },
        true);
    GUI::ButtonFactory::create(
        this->localEntities,
        resizer(ressourcePackPositions[7]),
        "snowyToundra",
        menuButtons,
        "Snowy",
        [optionEntity, selectedEntity, resizer](const Engine::Entity &) {
            setRessourcePack(optionEntity, selectedEntity, resizer, 7);
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

uint RessourcePackMenuScene::_getSelectedRessourcePackIndex(const Engine::Entity &optionEntity)
{
    const string &selectedRessourcePack =
        CoreData::entityManager->getComponent<Component::OptionComponent>(optionEntity).ressourcePack;

    for (uint i = 0; i < nbrRessourcePacks; i++)
        if (ressourcePackPaths[i] == selectedRessourcePack)
            return i;

    return 0;
}