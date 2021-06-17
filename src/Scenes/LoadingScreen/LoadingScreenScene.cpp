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
    std::cerr << "\tOPEN\n";
    const raylib::MyVector2 windowSize(CoreData::settings->getMyVector2("WIN_SIZE"));

    auto background = this->localEntities.createEntity("LoadingScreenBackground");
    CoreData::entityManager->addComponent<Component::Render2D>(background,
        Component::render2dMapModels(
            {{"LoadingScreenBackgroundRectangle",
                 std::make_shared<raylib::Rectangle>(
                     raylib::MyVector2(0, 0), raylib::MyVector2(windowSize.a, windowSize.b), raylib::RColor::RWHITE)},
                {"Text",
                    std::make_shared<raylib::Text>("EPIJANG",
                        "Asset/Font/Code-Bold.ttf",
                        ProportionUtilities::getProportionWin(windowSize, {50, 50}, {500, 100}),
                        130,
                        raylib::RColor::RBLACK)}}));
    Engine::Entity jauge = this->localEntities.createEntity("jauge");
    CoreData::entityManager->addComponent<Component::Render2D>(jauge,
        Component::render2dMapModels({
            {"rect",
                std::make_shared<raylib::Rectangle>(ProportionUtilities::getProportionWin(windowSize, {50, 70}, {800, 10}),
                    raylib::MyVector2(0, 0),
                    raylib::RColor::RRED)},
        }));
}

void Game::LoadingScreenScene::update(std::size_t value)
{
    // UPDATE JAUGE
    Engine::Entity entity = this->localEntities.getEntity("jauge");
    auto &render = CoreData::entityManager->getComponent<Component::Render2D>(entity);
    raylib::Rectangle &rect = *static_cast<raylib::Rectangle *>(render.get("rect").get());
    rect.setSize({(float)(value * 8), 30});
    // DISPLAY
    auto &render2D = this->_systemManager.getSystem<System::Render2DSystem>();
    render2D.update();
}