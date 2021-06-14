/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** LoadingScreenScene
*/

#include "LoadingScreenScene.hpp"

using namespace Game;

LoadingScreenScene::LoadingScreenScene(Engine::SystemManager &systemManager)
    : Engine::AbstractScene(systemManager, *CoreData::entityManager)
{
}

void LoadingScreenScene::open()
{
    const raylib::MyVector2 windowSize(CoreData::settings->getMyVector2("WIN_SIZE"));

    auto background = this->localEntities.createEntity("LoadingScreenBackground");
    CoreData::entityManager->addComponent<Component::Render2D>(background,
        Component::render2dMapModels(
            {
                {"LoadingScreenBackgroundRectangle", std::make_shared<raylib::Rectangle>(raylib::MyVector2(0, 0),
                raylib::MyVector2(windowSize.a, windowSize.b), raylib::RColor::RRED)}
            }
        )
    );
}

void Game::LoadingScreenScene::update()
{
    auto &render2D = this->_systemManager.getSystem<System::Render2DSystem>();

    render2D.update();
    this->eventDispatcher(this->_systemManager);
}