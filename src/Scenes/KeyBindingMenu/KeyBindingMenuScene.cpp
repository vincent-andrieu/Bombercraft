/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 03/06/2021 DebugScene.cpp.cc
*/

#include "KeyBindingMenuScene.hpp"

using namespace Game;
using namespace raylib;

KeyBindingMenuScene::KeyBindingMenuScene(Engine::SystemManager &systemManager)
    : AbstractScene(systemManager, *Game::CoreData::entityManager), _selectedPlayer(nullptr)
{
}

void KeyBindingMenuScene::open()
{
    this->_selectedPlayer = &Game::CoreData::systemManager->getSystem<System::PlayerConfigSystem>().update(0);

    GUI::LabelFactory::create(this->localEntities, this->_resizer(44, 1), "Controls", this->_defaultLabelConfig);

    // Change player
    GUI::ButtonFactory::create(this->localEntities,
        this->_resizer(47, 10),
        "playerNumberTitle",
        this->_buttonDefaultConfig,
        "Player " + toString(this->_selectedPlayer->getPlayerId()),
        [this](const Engine::Entity &entity) {
            this->_selectedPlayer =
                &Game::CoreData::systemManager->getSystem<System::PlayerConfigSystem>().update(*this->_selectedPlayer);
            static_cast<raylib::Text *>(
                Game::CoreData::entityManager->getComponent<Component::Render2D>(entity).get("label").get())
                ->setText("Player " + toString(this->_selectedPlayer->getPlayerId()));
            this->_refreshKeys();
        });

    this->_createKeysLabel();

    this->_createResetKeys();

    this->_createKeysInput();

    GUI::ButtonFactory::create(this->localEntities,
        this->_resizer(20, 90),
        "resetKeysButton",
        this->_buttonDefaultConfig,
        "Reset keys",
        [this](UNUSED const Engine::Entity &entity) {
            this->_selectedPlayer->resetAllKeyBindings();
            this->_refreshKeys();
        });
}

void KeyBindingMenuScene::update()
{
    auto &render2DSystem = CoreData::systemManager->getSystem<System::Render2DSystem>();

    render2DSystem.update();
    this->eventDispatcher(this->_systemManager);
}

void KeyBindingMenuScene::_createKeysLabel()
{
    GUI::LabelFactory::create(this->localEntities, this->_resizer(20, 23), "Move up", this->_defaultLabelConfig);
    GUI::LabelFactory::create(this->localEntities, this->_resizer(20, 33), "Move down", this->_defaultLabelConfig);
    GUI::LabelFactory::create(this->localEntities, this->_resizer(20, 43), "Move left", this->_defaultLabelConfig);
    GUI::LabelFactory::create(this->localEntities, this->_resizer(20, 53), "Move right", this->_defaultLabelConfig);
    GUI::LabelFactory::create(this->localEntities, this->_resizer(20, 63), "Pause", this->_defaultLabelConfig);
    GUI::LabelFactory::create(this->localEntities, this->_resizer(20, 73), "Place bomb", this->_defaultLabelConfig);
}

void KeyBindingMenuScene::_createResetKeys()
{
    this->_createResetKey(23, "resetMoveUp", [this](UNUSED const Engine::Entity &entity) {
        const auto &newKey = this->_selectedPlayer->getPlayerDefaultKeyBindings().moveUp;

        this->_selectedPlayer->setKeyMoveUp(newKey);
        this->_refreshKeys("keyInputMoveUp", newKey);
    });
    this->_createResetKey(33, "resetMoveDown", [this](UNUSED const Engine::Entity &entity) {
        const auto &newKey = this->_selectedPlayer->getPlayerDefaultKeyBindings().moveDown;

        this->_selectedPlayer->setKeyMoveDown(newKey);
        this->_refreshKeys("keyInputMoveDown", newKey);
    });
    this->_createResetKey(43, "resetMoveLeft", [this](UNUSED const Engine::Entity &entity) {
        const auto &newKey = this->_selectedPlayer->getPlayerDefaultKeyBindings().moveLeft;

        this->_selectedPlayer->setKeyMoveLeft(newKey);
        this->_refreshKeys("keyInputMoveLeft", newKey);
    });
    this->_createResetKey(53, "resetMoveRight", [this](UNUSED const Engine::Entity &entity) {
        const auto &newKey = this->_selectedPlayer->getPlayerDefaultKeyBindings().moveRight;

        this->_selectedPlayer->setKeyMoveRight(newKey);
        this->_refreshKeys("keyInputMoveRight", newKey);
    });
    this->_createResetKey(63, "resetPause", [this](UNUSED const Engine::Entity &entity) {
        const auto &newKey = this->_selectedPlayer->getPlayerDefaultKeyBindings().pause;

        this->_selectedPlayer->setKeyPause(newKey);
        this->_refreshKeys("keyInputPause", newKey);
    });
    this->_createResetKey(73, "resetPlaceBomb", [this](UNUSED const Engine::Entity &entity) {
        const auto &newKey = this->_selectedPlayer->getPlayerDefaultKeyBindings().placeBomb;

        this->_selectedPlayer->setKeyPlaceBomb(newKey);
        this->_refreshKeys("keyInputPlaceBomb", newKey);
    });
}

void KeyBindingMenuScene::_createResetKey(const float &y, const string &name, const Component::eventScript &eventHandler)
{
    GUI::ButtonFactory::create(
        this->localEntities, this->_resizer(60, y), name, this->_buttonDefaultConfig, "Reset", eventHandler);
}

void KeyBindingMenuScene::_createKeysInput()
{
    const auto &playerKeyBindings = this->_selectedPlayer->getPlayerKeyBindings();

    GUI::KeyInputFactory::create(this->localEntities,
        {this->_resizer(42, 23), "keyInputMoveUp", playerKeyBindings.moveUp},
        this->_defaultLabelConfig,
        this->_keyInputDefaultConfig,
        [this](UNUSED const Engine::Entity &entity, const std::pair<const raylib::KeyBoard, string> &key) {
            this->_selectedPlayer->setKeyMoveUp(key.first);
        });
    GUI::KeyInputFactory::create(this->localEntities,
        {this->_resizer(42, 33), "keyInputMoveDown", playerKeyBindings.moveDown},
        this->_defaultLabelConfig,
        this->_keyInputDefaultConfig,
        [this](UNUSED const Engine::Entity &entity, const std::pair<const raylib::KeyBoard, string> &key) {
            this->_selectedPlayer->setKeyMoveDown(key.first);
        });
    GUI::KeyInputFactory::create(this->localEntities,
        {this->_resizer(42, 43), "keyInputMoveLeft", playerKeyBindings.moveLeft},
        this->_defaultLabelConfig,
        this->_keyInputDefaultConfig,
        [this](UNUSED const Engine::Entity &entity, const std::pair<const raylib::KeyBoard, string> &key) {
            this->_selectedPlayer->setKeyMoveLeft(key.first);
        });
    GUI::KeyInputFactory::create(this->localEntities,
        {this->_resizer(42, 53), "keyInputMoveRight", playerKeyBindings.moveRight},
        this->_defaultLabelConfig,
        this->_keyInputDefaultConfig,
        [this](UNUSED const Engine::Entity &entity, const std::pair<const raylib::KeyBoard, string> &key) {
            this->_selectedPlayer->setKeyMoveRight(key.first);
        });
    GUI::KeyInputFactory::create(this->localEntities,
        {this->_resizer(42, 63), "keyInputPause", playerKeyBindings.pause},
        this->_defaultLabelConfig,
        this->_keyInputDefaultConfig,
        [this](UNUSED const Engine::Entity &entity, const std::pair<const raylib::KeyBoard, string> &key) {
            this->_selectedPlayer->setKeyPause(key.first);
        });
    GUI::KeyInputFactory::create(this->localEntities,
        {this->_resizer(42, 73), "keyInputPlaceBomb", playerKeyBindings.placeBomb},
        this->_defaultLabelConfig,
        this->_keyInputDefaultConfig,
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
    this->_refreshKeys("keyInputPause", playerKeyBindings.pause);
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