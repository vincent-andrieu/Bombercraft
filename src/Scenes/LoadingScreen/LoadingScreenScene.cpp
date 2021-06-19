/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** LoadingScreenScene
*/

#include "LoadingScreenScene.hpp"
#include "Utilities/ProportionUtilities.hpp"

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
            {{"LoadingScreenBackgroundRectangle",
                 std::make_shared<raylib::Rectangle>(
                     raylib::MyVector2(0, 0), raylib::MyVector2(windowSize.a, windowSize.b), raylib::RColor::RWHITE)},
                {"Text",
                    std::make_shared<raylib::Texture>(CoreData::settings->getString("LOADING_SCREEN_TITLE"),
                        ProportionUtilities::getProportionWin(windowSize, {50, 30}),
                        ProportionUtilities::getProportionWin(windowSize, {25, 30})
                        )}}));
    Engine::Entity jauge = this->localEntities.createEntity("jauge");
    CoreData::entityManager->addComponent<Component::Render2D>(jauge,
        Component::render2dMapModels({
            {"rect",
                std::make_shared<raylib::Rectangle>(ProportionUtilities::getProportionWin(windowSize, {25, 70}),
                    raylib::MyVector2(0, 0),
                    raylib::RColor::RRED)},
        }));
}

void Game::LoadingScreenScene::update(std::size_t value)
{
    const raylib::MyVector2 windowSize(CoreData::settings->getMyVector2("WIN_SIZE"));

    // UPDATE JAUGE
    Engine::Entity entity = this->localEntities.getEntity("jauge");
    auto &render = CoreData::entityManager->getComponent<Component::Render2D>(entity);
    raylib::Rectangle &rect = *static_cast<raylib::Rectangle *>(render.get("rect").get());
    rect.setSize({(float)((float)value / 100) * (windowSize.a / 2), 30});
    // DISPLAY
    auto &render2D = this->_systemManager.getSystem<System::Render2DSystem>();
    render2D.update();
}