/*50
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 04/06/2021 MainMenuScene.cpp.cc
*/

#include "MainMenuScene.hpp"

using namespace Game;

MainMenuScene::MainMenuScene(Engine::SystemManager &systemManager)
    : Engine::AbstractScene(systemManager, *CoreData::entityManager)
{
}

void MainMenuScene::open()
{
    auto scene = CoreData::sceneManager->getCurrentScene();
    const auto &windowSize(Game::CoreData::settings->getMyVector2("WIN_SIZE"));
    const size_t fontSize = (size_t)Game::CoreData::settings->getInt("SUB_FONT_SIZE");
    const std::string bottomLeftText = Game::CoreData::settings->getString("HOME_BOTTOM_LEFT_TXT");
    const std::string bottomRightText = Game::CoreData::settings->getString("HOME_BOTTOM_RIGHT_TXT");

    ProportionUtilities my_utility(windowSize);
    const std::vector<raylib::MyVector2> buttonPosition = {
        my_utility.getProportion({25, 40}),
        my_utility.getProportion({25, 50}),
        my_utility.getProportion({25, 65}),
        my_utility.getProportion({50.5, 65}),
    };
    const GUI::ButtonConfig largeButton(GUI::ButtonFactory::getLargeButtonConfig());
    const GUI::ButtonConfig mediumButton(GUI::ButtonFactory::getMediumButtonConfig());

    raylib::MyVector2 logoSize(my_utility.getProportion({70, 25}));
    GUI::ImageFactory::create(scene->localEntities,
        raylib::MyVector2(0, 0),
        Game::CoreData::settings->getMyVector2("HOME_BACKGROUND_SIZE"),
        Game::CoreData::settings->getString("HOME_BACKGROUND"),
        false, "background",
        Game::CoreData::settings->getMyVector2("HOME_BACKGROUND_START")
    );
    Engine::Entity background = localEntities.getEntity("background");
    CoreData::entityManager->addComponent<Engine::Timer>(background, 0.01, *CoreData::entityManager, *CoreData::sceneManager, [](Engine::EntityManager &, Engine::SceneManager &, const Engine::Entity entity) {
        const raylib::MyVector2 backgroundSize = Game::CoreData::settings->getMyVector2("HOME_BACKGROUND_SIZE");
        raylib::Texture *pictureBg = static_cast<raylib::Texture *>(
            Game::CoreData::entityManager->getComponent<Component::Render2D>(entity).get("image").get());
        raylib::MyVector2 rect = pictureBg->getRect();
        if (rect.a > backgroundSize.a) {
            pictureBg->setRect(raylib::MyVector2(0, rect.b));
        } else {
            pictureBg->setRect(raylib::MyVector2((float)(rect.a + 0.8), rect.b));
        }
    });
    // GAME TITLE //340
    GUI::ImageFactory::create(scene->localEntities,
        my_utility.getProportion({50, 20}, logoSize, {50, 50}),
        logoSize,
        Game::CoreData::settings->getString("BOMBERCRAFT_LOGO"),
        true);
    // BUTTON
    GUI::ButtonFactory::create(scene->localEntities, buttonPosition[0], "play", largeButton, "Play", [](const Engine::Entity) {
        CoreData::sceneManager->setScene<GameScene>();
    });
    GUI::ButtonFactory::create(
        scene->localEntities, buttonPosition[1], "credit", largeButton, "Credit", [](const Engine::Entity) {
            std::cout << "Go to credit" << std::endl;
    });
    GUI::ButtonFactory::create(
        scene->localEntities, buttonPosition[2], "options", mediumButton, "Options...", [](const Engine::Entity) {
            CoreData::sceneManager->pushLastScene();
            CoreData::sceneManager->setScene<OptionsMenuScene>();
    });
    GUI::ButtonFactory::create(
        scene->localEntities, buttonPosition[3], "quit", mediumButton, "Quit Game", [](const Engine::Entity) {
            CoreData::quit();
    });
    raylib::MyVector2 bottomLeftPos(my_utility.getProportion({1, 95}));
    raylib::MyVector2 bottomRightPos(my_utility.getProportion({62, 95}));
    GUI::LabelFactory::create(scene->localEntities, bottomLeftPos, bottomLeftText, GUI::LabelFactory::getStandardLabelConfig(fontSize), "bottomleft");
    GUI::LabelFactory::create(scene->localEntities, bottomRightPos, bottomRightText, GUI::LabelFactory::getStandardLabelConfig(fontSize), "bottomright");
}

void Game::MainMenuScene::update()
{
    auto &render2D = this->_systemManager.getSystem<System::Render2DSystem>();
    auto &timer = this->_systemManager.getSystem<Engine::TimerSystem>();

    render2D.update();
    timer.update();
    this->eventDispatcher(this->_systemManager);
}