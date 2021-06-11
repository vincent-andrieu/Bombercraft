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
        });

    this->_createKeysLabel();

    this->_createResetKeys();
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
        this->_selectedPlayer->setKeyMoveUp(this->_selectedPlayer->getPlayerDefaultKeyBindings().moveUp);
    });
    this->_createResetKey(33, "resetMoveDown", [this](UNUSED const Engine::Entity &entity) {
        this->_selectedPlayer->setKeyMoveDown(this->_selectedPlayer->getPlayerDefaultKeyBindings().moveDown);
    });
    this->_createResetKey(43, "resetMoveLeft", [this](UNUSED const Engine::Entity &entity) {
        this->_selectedPlayer->setKeyMoveLeft(this->_selectedPlayer->getPlayerDefaultKeyBindings().moveLeft);
    });
    this->_createResetKey(53, "resetMoveRight", [this](UNUSED const Engine::Entity &entity) {
        this->_selectedPlayer->setKeyMoveRight(this->_selectedPlayer->getPlayerDefaultKeyBindings().moveRight);
    });
    this->_createResetKey(63, "resetPause", [this](UNUSED const Engine::Entity &entity) {
        this->_selectedPlayer->setKeyPause(this->_selectedPlayer->getPlayerDefaultKeyBindings().pause);
    });
    this->_createResetKey(73, "resetPlaceBomb", [this](UNUSED const Engine::Entity &entity) {
        this->_selectedPlayer->setKeyPlaceBomb(this->_selectedPlayer->getPlayerDefaultKeyBindings().placeBomb);
    });
}

void KeyBindingMenuScene::_createResetKey(const float &y, const string &name, const Component::eventScript &eventHandler)
{
    GUI::ButtonFactory::create(
        this->localEntities, this->_resizer(60, y), name, this->_buttonDefaultConfig, "Reset", eventHandler);
}