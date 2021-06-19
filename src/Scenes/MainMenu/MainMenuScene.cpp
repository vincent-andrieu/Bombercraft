/*50
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 04/06/2021 MainMenuScene.cpp.cc
*/

#include "MainMenuScene.hpp"

#include "Game/Factories/Sound/AudioFactory.hpp"

using namespace Game;

extern std::unique_ptr<Game::Core> core;

MainMenuScene::MainMenuScene(Engine::SystemManager &systemManager)
    : Engine::AbstractScene(systemManager, *CoreData::entityManager)
{
}

void MainMenuScene::open()
{
    const auto &windowSize(Game::CoreData::settings->getMyVector2("WIN_SIZE"));
    const size_t fontSize = (size_t) Game::CoreData::settings->getInt("SUB_FONT_SIZE");
    const std::string bottomLeftText = Game::CoreData::settings->getString("HOME_BOTTOM_LEFT_TXT");
    const std::string bottomRightText = Game::CoreData::settings->getString("HOME_BOTTOM_RIGHT_TXT");
    GUI::LabelConfig splashConf = {fontSize, raylib::RColor::RGOLD, Game::CoreData::settings->getString("STANDARD_FONT")};
    std::vector<std::string> splashMsg = Game::CoreData::settings->getTabString("SPLASH_MSG");
    size_t splashMsgIdx = 0;

    if (splashMsg.size())
        splashMsgIdx = std::rand() % splashMsg.size();
    else {
        splashMsg.push_back("Serieux Julien?????");
    }
    ProportionUtilities my_utility(windowSize);
    const std::vector<raylib::MyVector2> buttonPosition = {
        my_utility.getProportion({25, 40}),
        my_utility.getProportion({25, 50}),
        my_utility.getProportion({25, 65}),
        my_utility.getProportion({50.5, 65}),
    };
    const GUI::ButtonConfig largeButton(GUI::ButtonFactory::getLargeButtonConfig());
    const GUI::ButtonConfig mediumButton(GUI::ButtonFactory::getMediumButtonConfig());

    // BACKGROUND
    const raylib::MyVector2 logoSize(my_utility.getProportion({70, 15}));
    raylib::MyVector2 backgroundSize(Game::CoreData::settings->getMyVector2("HOME_BACKGROUND_SIZE"));
    const float my_multiplier(my_utility.getProportion({0, 100}).b / backgroundSize.b);
    backgroundSize = backgroundSize * my_multiplier;

    Engine::Entity background = GUI::ImageFactory::create(this->localEntities,
        raylib::MyVector2(0, 0),
        backgroundSize,
        Game::CoreData::settings->getString("HOME_BACKGROUND"),
        true,
        "background",
        raylib::MyVector2(0, 0));
    CoreData::entityManager->addComponent<Engine::Timer>(background,
        0.01,
        *CoreData::entityManager,
        *CoreData::sceneManager,
        [](Engine::EntityManager &, Engine::SceneManager &scene, const Engine::Entity entity) {
            raylib::Texture *pictureBg = static_cast<raylib::Texture *>(
                Game::CoreData::entityManager->getComponent<Component::Render2D>(entity).get("image").get());
            const raylib::MyVector2 pictureRect(pictureBg->getRect());
            const raylib::MyVector2 pictureSize(pictureBg->getSize());
            auto other(scene.getCurrentScene()->localEntities.getEntity("background2"));
            raylib::Texture *otherPictureBg = static_cast<raylib::Texture *>(
                Game::CoreData::entityManager->getComponent<Component::Render2D>(other).get("image").get());
            const auto panoSpeed(Game::CoreData::settings->getFloat("PANORAMA_SPEED"));

            if (pictureRect.a <= pictureSize.a * -1) {
                pictureBg->setRect(raylib::MyVector2(otherPictureBg->getRect().a + pictureSize.a - panoSpeed, pictureRect.b));
            } else {
                pictureBg->setRect(raylib::MyVector2((float) (pictureRect.a - panoSpeed), pictureRect.b));
            }
        });

    Engine::Entity background2 = GUI::ImageFactory::create(this->localEntities,
        raylib::MyVector2(0, 0),
        backgroundSize,
        Game::CoreData::settings->getString("HOME_BACKGROUND"),
        true,
        "background2",
        raylib::MyVector2(backgroundSize.a, 0));
    CoreData::entityManager->addComponent<Engine::Timer>(background2,
        0.01,
        *CoreData::entityManager,
        *CoreData::sceneManager,
        [](Engine::EntityManager &, Engine::SceneManager &scene, const Engine::Entity entity) {
            raylib::Texture *pictureBg = static_cast<raylib::Texture *>(
                Game::CoreData::entityManager->getComponent<Component::Render2D>(entity).get("image").get());
            const raylib::MyVector2 pictureRect(pictureBg->getRect());
            const raylib::MyVector2 pictureSize(pictureBg->getSize());

            auto other(scene.getCurrentScene()->localEntities.getEntity("background"));
            raylib::Texture *otherPictureBg = static_cast<raylib::Texture *>(
                Game::CoreData::entityManager->getComponent<Component::Render2D>(other).get("image").get());
            const auto panoSpeed(Game::CoreData::settings->getFloat("PANORAMA_SPEED"));

            if (pictureRect.a <= pictureSize.a * -1) {
                pictureBg->setRect(raylib::MyVector2(otherPictureBg->getRect().a + pictureSize.a, pictureRect.b));
            } else {
                pictureBg->setRect(raylib::MyVector2((float) (pictureRect.a - panoSpeed), pictureRect.b));
            }
        });

    // GAME LOGO
    GUI::ImageFactory::create(this->localEntities,
        my_utility.getProportion({50, 20}, logoSize, {50, 50}),
        logoSize,
        Game::CoreData::settings->getString("BOMBERCRAFT_LOGO"),
        true);

    // BUTTON
    GUI::ButtonFactory::create(this->localEntities, buttonPosition[0], "play", largeButton, "Play", [](const Engine::Entity) {
        CoreData::sceneManager->pushLastScene();
        CoreData::sceneManager->setScene<SaveMenuScene>();
    });
    GUI::ButtonFactory::create(this->localEntities, buttonPosition[1], "credit", largeButton, "Credit", [](const Engine::Entity) {
        CoreData::sceneManager->setScene<CreditScene>();
    });
    GUI::ButtonFactory::create(
        this->localEntities, buttonPosition[2], "options", mediumButton, "Options...", [](const Engine::Entity) {
            CoreData::sceneManager->pushLastScene();
            CoreData::sceneManager->setScene<OptionsMenuScene>();
        });
    GUI::ButtonFactory::create(
        this->localEntities, buttonPosition[3], "quit", mediumButton, "Quit Game", [](const Engine::Entity) {
            CoreData::quit();
        });

    // TEXT
    raylib::MyVector2 bottomLeftPos(my_utility(1, 94));
    raylib::MyVector2 bottomRightPos(my_utility(71, 94));
    raylib::MyVector2 splashPos(my_utility({65, 30}));
    GUI::LabelFactory::create(this->localEntities,
        bottomLeftPos,
        my_utility.getProportion(GUI::ButtonFactory::SmallProportions),
        bottomLeftText,
        GUI::LabelFactory::getStandardLabelConfig(fontSize),
        "bottomleft");
    GUI::LabelFactory::create(this->localEntities,
        bottomRightPos,
        my_utility.getProportion(GUI::ButtonFactory::MediumProportions),
        bottomRightText,
        GUI::LabelFactory::getStandardLabelConfig(fontSize),
        "bottomright");
    auto &audioSystem = CoreData::systemManager->getSystem<System::AudioSystem>();
    if (!audioSystem.isPlaying("MENU", core->globalEntities))
        audioSystem.play("MENU", core->globalEntities);
    GUI::LabelFactory::create(this->localEntities, splashPos, splashMsg[splashMsgIdx], splashConf, "splash");
    Engine::Entity splashTxt = localEntities.getEntity("splash");
    CoreData::entityManager->addComponent<Engine::Timer>(splashTxt,
        0.07,
        *CoreData::entityManager,
        *CoreData::sceneManager,
        [](Engine::EntityManager &, Engine::SceneManager &, const Engine::Entity entity) {
            static bool grow = true;
            const size_t fontSize = (size_t) Game::CoreData::settings->getInt("SUB_FONT_SIZE");
            raylib::Text *text = static_cast<raylib::Text *>(
                Game::CoreData::entityManager->getComponent<Component::Render2D>(entity).get("text").get());

            if (grow) {
                text->setFontSize(text->getFontSize() + 1);
            } else {
                text->setFontSize(text->getFontSize() - 1);
            }
            if (text->getFontSize() >= fontSize + 5) {
                grow = false;
            } else if (text->getFontSize() <= fontSize) {
                grow = true;
            }
        });

    //    KEYS
    std::unordered_map<raylib::KeyBoard, Component::eventScript> my_keyTriggers;
    my_keyTriggers.emplace(std::make_pair(raylib::KeyBoard::IKEY_ESCAPE, [](Engine::Entity) {
        CoreData::quit();
    }));
    Game::KeyManagementFactory::create(this->localEntities, my_keyTriggers);
}

void Game::MainMenuScene::update()
{
    auto &render2D = this->_systemManager.getSystem<System::Render2DSystem>();
    auto &timer = this->_systemManager.getSystem<Engine::TimerSystem>();

    render2D.update();
    timer.update();
    this->eventDispatcher(this->_systemManager);
}