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

static void setRessourcePack(const Engine::Entity &optionEntity, const Engine::Entity &buttonEntity, const uint index)
{
    CoreData::entityManager->getComponent<Component::OptionComponent>(optionEntity).ressourcePack = ressourcePackPaths[index];
    Component::Render2D &button = CoreData::entityManager->getComponent<Component::Render2D>(buttonEntity);
    CoreData::entityManager->foreachComponent<Component::Render2D>([buttonEntity](Component::Render2D &component) {
        if (component.doesGet("unavailable") && component.isSetToDraw("unavailable")) {
            component.setToDrawFirst("idle");
            component.unsetToDraw("unavailable");
        }
    });
    button.unsetToDraw("idle");
    button.unsetToDraw("hover");
    button.setToDrawFirst("unavailable");
}

void RessourcePackMenuScene::open()
{
    const MyVector2 &window_size = CoreData::settings->getMyVector2("WIN_SIZE");
    const ProportionUtilities resizer(window_size);
    GUI::ButtonConfig menuButtons = GUI::ButtonFactory::getBigButtonConfig();
    const Engine::Entity &optionEntity = core->globalEntities.getEntity("options");
    std::vector<Engine::Entity> buttonEntities;

    GUI::ImageFactory::create(
        this->localEntities, raylib::MyVector2(0, 0), window_size, CoreData::settings->getString("STANDARD_BACKGROUND"), false);
    GUI::LabelFactory::createCentered(
        this->localEntities, resizer(50, 4), "Ressource pack", GUI::LabelFactory::getStandardLabelConfig());

    buttonEntities.push_back(GUI::ButtonFactory::create(
        this->localEntities,
        resizer(25, 20),
        "desertButton",
        menuButtons,
        "Desert",
        [optionEntity](const Engine::Entity &entityButton) {
            setRessourcePack(optionEntity, entityButton, 0);
        },
        true));
    buttonEntities.push_back(GUI::ButtonFactory::create(
        this->localEntities,
        resizer(75, 20),
        "endButton",
        menuButtons,
        "End",
        [optionEntity](const Engine::Entity &entityButton) {
            setRessourcePack(optionEntity, entityButton, 1);
        },
        true));
    buttonEntities.push_back(GUI::ButtonFactory::create(
        this->localEntities,
        resizer(25, 30),
        "mountains",
        menuButtons,
        "Mountains",
        [optionEntity](const Engine::Entity &entityButton) {
            setRessourcePack(optionEntity, entityButton, 2);
        },
        true));
    buttonEntities.push_back(GUI::ButtonFactory::create(
        this->localEntities,
        resizer(75, 30),
        "mushroom",
        menuButtons,
        "Mushroom",
        [optionEntity](const Engine::Entity &entityButton) {
            setRessourcePack(optionEntity, entityButton, 3);
        },
        true));
    buttonEntities.push_back(GUI::ButtonFactory::create(
        this->localEntities,
        resizer(25, 40),
        "nether",
        menuButtons,
        "Nether",
        [optionEntity](const Engine::Entity &entityButton) {
            setRessourcePack(optionEntity, entityButton, 4);
        },
        true));
    buttonEntities.push_back(GUI::ButtonFactory::create(
        this->localEntities,
        resizer(75, 40),
        "ocean",
        menuButtons,
        "Ocean",
        [optionEntity](const Engine::Entity &entityButton) {
            setRessourcePack(optionEntity, entityButton, 5);
        },
        true));
    buttonEntities.push_back(GUI::ButtonFactory::create(
        this->localEntities,
        resizer(25, 50),
        "plains",
        menuButtons,
        "Plains",
        [optionEntity](const Engine::Entity &entityButton) {
            setRessourcePack(optionEntity, entityButton, 6);
        },
        true));
    buttonEntities.push_back(GUI::ButtonFactory::create(
        this->localEntities,
        resizer(75, 50),
        "snowyToundra",
        menuButtons,
        "Snowy",
        [optionEntity](const Engine::Entity &entityButton) {
            setRessourcePack(optionEntity, entityButton, 7);
        },
        true));

    const uint &selectedButtonIndex = this->_getSelectedRessourcePackIndex(optionEntity);
    const Engine::Entity &selectedButtonEntity = buttonEntities.at(selectedButtonIndex);
    setRessourcePack(optionEntity, selectedButtonEntity, selectedButtonIndex);

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