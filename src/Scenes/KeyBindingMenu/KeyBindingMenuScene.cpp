/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 03/06/2021 DebugScene.cpp.cc
*/

#include "KeyBindingMenuScene.hpp"
#include "Scenes/OptionsMenu/OptionsMenuScene.hpp"
#include "Game/Factories/KeyManagementFactory/KeyManagementFactory.hpp"

using namespace Game;
using namespace raylib;

static const Component::eventScript doneButtonHandler = [](UNUSED const Engine::Entity &entity) {
    CoreData::sceneManager->setScene(CoreData::sceneManager->peekLastScene());
};

KeyBindingMenuScene::KeyBindingMenuScene(Engine::SystemManager &systemManager)
    : AbstractScene(systemManager, *Game::CoreData::entityManager), _selectedPlayer(nullptr)
{
    this->_buttonDefaultConfig.fontSize = 30;
}

void KeyBindingMenuScene::open()
{
    this->_selectedPlayer =
        &Game::CoreData::systemManager->getSystem<System::PlayerConfigSystem>().getPlayerFromID(Component::PlayerID::ALPHA);

    GUI::ImageFactory::create(this->localEntities,
        raylib::MyVector2(0, 0),
        CoreData::settings->getMyVector2("WIN_SIZE"),
        CoreData::settings->getString("STANDARD_BACKGROUND"),
        false);
    GUI::LabelFactory::createCentered(
        this->localEntities, this->_resizer(50, 4), "Controls", GUI::LabelFactory::getStandardLabelConfig());

    // Change player
    GUI::ButtonFactory::create(this->localEntities,
        this->_resizer(44, 10),
        "playerNumberTitle",
        this->_buttonDefaultConfig,
        "Player " + toString(this->_selectedPlayer->getPlayerId() + 1),
        [this](const Engine::Entity &entity) {
            this->_selectedPlayer =
                &Game::CoreData::systemManager->getSystem<System::PlayerConfigSystem>().getNextPlayer(*this->_selectedPlayer);
            static_cast<raylib::Text *>(
                Game::CoreData::entityManager->getComponent<Component::Render2D>(entity).get("label").get())
                ->setText("Player " + toString(this->_selectedPlayer->getPlayerId() + 1));
            this->_refreshKeys();
        });

    this->_createKeysLabel();

    this->_createResetKeys();

    this->_createKeysInput();

    GUI::ButtonConfig bottomButtonsConfig = GUI::ButtonFactory::getMediumButtonConfig();
    GUI::ButtonFactory::create(this->localEntities,
        this->_resizer(50.5, 90),
        "resetKeysButton",
        bottomButtonsConfig,
        "Reset keys",
        [this](const Engine::Entity &) {
            this->_selectedPlayer->resetAllKeyBindings();
            this->_refreshKeys();
        });

    GUI::ButtonFactory::create(
        this->localEntities, this->_resizer(25, 90), "doneButton", bottomButtonsConfig, "Done", doneButtonHandler);

    // KEYS
    std::unordered_map<raylib::KeyBoard, Component::eventScript> keyTriggers;
    keyTriggers.emplace(std::make_pair(raylib::KeyBoard::IKEY_ESCAPE, doneButtonHandler));
    Game::KeyManagementFactory::create(this->localEntities, keyTriggers);
}

void KeyBindingMenuScene::update()
{
    auto &render2DSystem = CoreData::systemManager->getSystem<System::Render2DSystem>();

    render2DSystem.update();
    this->eventDispatcher(this->_systemManager);
}

void KeyBindingMenuScene::_createKeysLabel()
{
    GUI::LabelFactory::create(this->localEntities,
        this->_resizer(20, 27),
        this->_buttonDefaultConfig.size - 10,
        "Move up",
        this->_defaultLabelConfig,
        "",
        true);
    GUI::LabelFactory::create(this->localEntities,
        this->_resizer(20, 37),
        this->_buttonDefaultConfig.size - 10,
        "Move down",
        this->_defaultLabelConfig,
        "",
        true);
    GUI::LabelFactory::create(this->localEntities,
        this->_resizer(20, 47),
        this->_buttonDefaultConfig.size - 10,
        "Move left",
        this->_defaultLabelConfig,
        "",
        true);
    GUI::LabelFactory::create(this->localEntities,
        this->_resizer(20, 57),
        this->_buttonDefaultConfig.size - 10,
        "Move right",
        this->_defaultLabelConfig,
        "",
        true);
    GUI::LabelFactory::create(this->localEntities,
        this->_resizer(20, 67),
        this->_buttonDefaultConfig.size - 10,
        "Place bomb",
        this->_defaultLabelConfig,
        "",
        true);
}

void KeyBindingMenuScene::_createResetKeys()
{
    this->_createResetKey(27, "resetMoveUp", [this](UNUSED const Engine::Entity &entity) {
        const auto &newKey = this->_selectedPlayer->getPlayerDefaultKeyBindings().moveUp;

        this->_selectedPlayer->setKeyMoveUp(newKey);
        this->_refreshKeys("keyInputMoveUp", newKey);
    });
    this->_createResetKey(37, "resetMoveDown", [this](UNUSED const Engine::Entity &entity) {
        const auto &newKey = this->_selectedPlayer->getPlayerDefaultKeyBindings().moveDown;

        this->_selectedPlayer->setKeyMoveDown(newKey);
        this->_refreshKeys("keyInputMoveDown", newKey);
    });
    this->_createResetKey(47, "resetMoveLeft", [this](UNUSED const Engine::Entity &entity) {
        const auto &newKey = this->_selectedPlayer->getPlayerDefaultKeyBindings().moveLeft;

        this->_selectedPlayer->setKeyMoveLeft(newKey);
        this->_refreshKeys("keyInputMoveLeft", newKey);
    });
    this->_createResetKey(57, "resetMoveRight", [this](UNUSED const Engine::Entity &entity) {
        const auto &newKey = this->_selectedPlayer->getPlayerDefaultKeyBindings().moveRight;

        this->_selectedPlayer->setKeyMoveRight(newKey);
        this->_refreshKeys("keyInputMoveRight", newKey);
    });
    this->_createResetKey(67, "resetPlaceBomb", [this](UNUSED const Engine::Entity &entity) {
        const auto &newKey = this->_selectedPlayer->getPlayerDefaultKeyBindings().placeBomb;

        this->_selectedPlayer->setKeyPlaceBomb(newKey);
        this->_refreshKeys("keyInputPlaceBomb", newKey);
    });
}

void KeyBindingMenuScene::_createResetKey(const float &y, const string &name, const Component::eventScript &eventHandler)
{
    GUI::ButtonFactory::create(
        this->localEntities, this->_resizer(65, y), name, this->_buttonDefaultConfig, "Reset", eventHandler);
}

void KeyBindingMenuScene::_createKeysInput()
{
    const auto &playerKeyBindings = this->_selectedPlayer->getPlayerKeyBindings();
    const GUI::KeyInputConfig keyInputDefaultConfig =
        GUI::KeyInputFactory::getStandardConfig(GUI::ButtonFactory::getStandardButtonConfig(this->_resizer(20, 8)).size);

    GUI::KeyInputFactory::create(this->localEntities,
        {this->_resizer(40, 27), "keyInputMoveUp", playerKeyBindings.moveUp},
        this->_defaultLabelConfig,
        keyInputDefaultConfig,
        [this](UNUSED const Engine::Entity &entity, const std::pair<const raylib::KeyBoard, string> &key) {
            this->_selectedPlayer->setKeyMoveUp(key.first);
        });
    GUI::KeyInputFactory::create(this->localEntities,
        {this->_resizer(40, 37), "keyInputMoveDown", playerKeyBindings.moveDown},
        this->_defaultLabelConfig,
        keyInputDefaultConfig,
        [this](UNUSED const Engine::Entity &entity, const std::pair<const raylib::KeyBoard, string> &key) {
            this->_selectedPlayer->setKeyMoveDown(key.first);
        });
    GUI::KeyInputFactory::create(this->localEntities,
        {this->_resizer(40, 47), "keyInputMoveLeft", playerKeyBindings.moveLeft},
        this->_defaultLabelConfig,
        keyInputDefaultConfig,
        [this](UNUSED const Engine::Entity &entity, const std::pair<const raylib::KeyBoard, string> &key) {
            this->_selectedPlayer->setKeyMoveLeft(key.first);
        });
    GUI::KeyInputFactory::create(this->localEntities,
        {this->_resizer(40, 57), "keyInputMoveRight", playerKeyBindings.moveRight},
        this->_defaultLabelConfig,
        keyInputDefaultConfig,
        [this](UNUSED const Engine::Entity &entity, const std::pair<const raylib::KeyBoard, string> &key) {
            this->_selectedPlayer->setKeyMoveRight(key.first);
        });
    GUI::KeyInputFactory::create(this->localEntities,
        {this->_resizer(40, 67), "keyInputPlaceBomb", playerKeyBindings.placeBomb},
        this->_defaultLabelConfig,
        keyInputDefaultConfig,
        [this](UNUSED const Engine::Entity &entity, const std::pair<const raylib::KeyBoard, string> &key) {
            this->_selectedPlayer->setKeyPlaceBomb(key.first);
        });
}

void KeyBindingMenuScene::_refreshKeys()
{
    const Component::PlayerKeyBindings &playerKeyBindings = this->_selectedPlayer->getPlayerKeyBindings();

    this->_refreshKeys("keyInputMoveUp", playerKeyBindings.moveUp);
    this->_refreshKeys("keyInputMoveDown", playerKeyBindings.moveDown);
    this->_refreshKeys("keyInputMoveLeft", playerKeyBindings.moveLeft);
    this->_refreshKeys("keyInputMoveRight", playerKeyBindings.moveRight);
    this->_refreshKeys("keyInputPlaceBomb", playerKeyBindings.placeBomb);
}

void KeyBindingMenuScene::_refreshKeys(const string &name, const raylib::KeyBoard &defaultKey)
{
    raylib::Text *text = dynamic_cast<raylib::Text *>(
        Game::CoreData::entityManager->getComponent<Component::Render2D>(this->localEntities.getEntity(name)).get("text").get());

    text->setText(GUI::KeyInputFactory::keyToStr.at(defaultKey));
}

void KeyBindingMenuScene::_refreshKeys(const Engine::Entity &entity, const raylib::KeyBoard &defaultKey)
{
    raylib::Text *text =
        dynamic_cast<raylib::Text *>(Game::CoreData::entityManager->getComponent<Component::Render2D>(entity).get("text").get());

    text->setText(GUI::KeyInputFactory::keyToStr.at(defaultKey));
}