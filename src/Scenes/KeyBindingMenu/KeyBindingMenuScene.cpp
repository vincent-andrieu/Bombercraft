/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 03/06/2021 DebugScene.cpp.cc
*/

#include "KeyBindingMenuScene.hpp"
#include "GUI/Factories/Button/ButtonFactory.hpp"
#include "GUI/Factories/Label/LabelFactory.hpp"

using namespace Game;
using namespace raylib;

KeyBindingMenuScene::KeyBindingMenuScene(Engine::SystemManager &systemManager)
    : AbstractScene(systemManager, *Game::CoreData::entityManager), _selectedPlayer(nullptr)
{
}

void KeyBindingMenuScene::open()
{
    this->_selectedPlayer = &Game::CoreData::systemManager->getSystem<System::PlayerConfigSystem>().update(0);
    this->_playerNumberTitle = "Player " + toString(this->_selectedPlayer->getPlayerId());
    GUI::LabelFactory::create(this->localEntities,
        this->_resizer(44, 1),
        "Controls",
        {
            static_cast<size_t>(CoreData::settings->getInt("DEF_FONT_SIZE")),
            RColor::RWHITE,
            CoreData::settings->getString("DEF_FONT"),
        });

    const Component::eventScript changePlayerHandler = [this](const Engine::Entity &entity) {
        this->_selectedPlayer =
            &Game::CoreData::systemManager->getSystem<System::PlayerConfigSystem>().update(*this->_selectedPlayer);
        this->_playerNumberTitle = "Player " + toString(this->_selectedPlayer->getPlayerId());
        std::cout << this->_playerNumberTitle << std::endl;
        Game::CoreData::entityManager->getComponent<raylib>(entity).
    };
    GUI::ButtonFactory::create(this->localEntities,
        this->_resizer(47, 10),
        "playerNumberTitle",
        GUI::ButtonFactory::getStandardButtonConfig(),
        this->_playerNumberTitle,
        changePlayerHandler);
}

void KeyBindingMenuScene::update()
{
    auto &render2DSystem = CoreData::systemManager->getSystem<System::Render2DSystem>();

    std::cout << this->_playerNumberTitle << std::endl;
    render2DSystem.update();
    this->eventDispatcher(this->_systemManager);
}