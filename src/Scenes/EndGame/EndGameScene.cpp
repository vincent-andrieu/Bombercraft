/*
** EPITECH PROJECT, 2021
** Scenes
** File description:
** 03/06/2021 EndGameScene.cpp.cc
*/

#include "EndGameScene.hpp"
#include "Systems/Hitbox/HitboxSystem.hpp"
#include "Components/Hitbox/Hitbox.hpp"
#include "GUI/Factories/Checkbox/CheckboxFactory.hpp"
#include "GUI/Factories/Countdown/CountdownFactory.hpp"
#include "GUI/Factories/Image/ImageFactory.hpp"
#include "GUI/Factories/Image/ImageSequenceFactory.hpp"

using namespace Game;

extern std::unique_ptr<Game::Core> core;

EndGameScene::EndGameScene(Engine::SystemManager &systemManager) : AbstractScene(systemManager, *Game::CoreData::entityManager)
{
}

static void goToGameScene(const Engine::Entity)
{
    Engine::Entity optionEntity = core->globalEntities.getEntity("options");
    auto &options = CoreData::entityManager->getComponent<Component::OptionComponent>(optionEntity);

    Game::CoreData::camera->setFovy((float) options.fov);
    Game::CoreData::sceneManager->setScene<Game::GameScene>();
}

static void goToMainMenuScene(const Engine::Entity)
{
    Game::CoreData::sceneManager->setScene<Game::MainMenuScene>();
}

void EndGameScene::open()
{
    const raylib::MyVector2 windowSize(CoreData::settings->getMyVector2("WIN_SIZE"));
    ProportionUtilities myUtility(CoreData::settings->getMyVector2("WIN_SIZE"));
    auto myButtonConfig(GUI::ButtonFactory::getMediumButtonConfig());
    std::string animDefeat = "Asset/Animation/Anim_Defeat_20";
    std::string animVictory = "Asset/Animation/Anim_Victory_32";
    std::shared_ptr<raylib::Animation> raylibAnimation = nullptr;
    raylib::MyVector3 rotation = {0, -90, 0};
    size_t nbPlayers = 2;
    Component::PlayerConfig *playerConfig = nullptr;
    const std::vector<Component::PlayerID> ids = {
        Component::PlayerID::ALPHA, Component::PlayerID::BRAVO, Component::PlayerID::CHARLIE, Component::PlayerID::DELTA};
    const std::vector<std::vector<float>> playerZPosition = {{0}, {7, -7}, {10, 0, -10}, {11, 4, -4, -11}};
    const raylib::MyVector2 xpBarSize = {182.0f * (windowSize.a / 640.0f), 5.0f * (windowSize.b / 360.0f)};
    raylib::MyVector2 xpBarPosition = {windowSize.a / 2.0f - xpBarSize.a / 2.0f, windowSize.b * 0.75f};

    CoreData::moveCamera(raylib::MyVector3(12, 0, 0), raylib::MyVector3(0, 0, 0));
    // BACKGROUND
    GUI::ImageFactory::create(
        this->localEntities, raylib::MyVector2(0, 0), windowSize, CoreData::settings->getString("GAME_SCREENSHOT"), false);
    auto background = this->localEntities.createEntity("EndGameBackground");
    CoreData::entityManager->addComponent<Component::Render2D>(background,
        Component::render2dMapModels({{"EndGameBackgroundRectangle",
            std::make_shared<raylib::Rectangle>(raylib::MyVector2(0, 0), windowSize, raylib::RColor::RSHADOW)}}));

    // BUTTONS
    GUI::ButtonFactory::create(localEntities,
        myUtility.getProportion({30, 90}, myButtonConfig.size),
        "EndGameRestartButton",
        myButtonConfig,
        "Restart",
        goToGameScene);
    GUI::ButtonFactory::create(localEntities,
        myUtility.getProportion({70, 90}, myButtonConfig.size),
        "EndGameMainMenuButton",
        myButtonConfig,
        "Main Menu",
        goToMainMenuScene);

    // TEXT
    GUI::LabelFactory::createCentered(localEntities,
        myUtility.getProportion(raylib::MyVector2(50, 10)),
        "End Of Game",
        GUI::LabelFactory::getStandardLabelConfig(CoreData::settings->getInt("STANDARD_FONT_SIZE")));

    // MODEL + XP
    CoreData::camera->setUp(CoreData::settings->getMyVector3("MENU_CAM_UP"));
    for (size_t i = 0; i < nbPlayers; i++) {
        Engine::Entity player = this->localEntities.createEntity("PlayerEndGame" + toString(i + 1));
        playerConfig = &Game::CoreData::systemManager->getSystem<System::PlayerConfigSystem>().getPlayerFromID(ids[i]);
        raylibAnimation = std::make_shared<raylib::Animation>(
            playerConfig->getSkinPath(), animDefeat, raylib::MyVector3(0, -4, playerZPosition[nbPlayers - 1][i]));
        raylibAnimation->setRotation(rotation);
        CoreData::entityManager->addComponent<Component::Render3D>(player, raylibAnimation);
        GUI::XPBarFactory::create(xpBarPosition,
            xpBarSize,
            CoreData::settings->getTabString("XP_BAR"),
            ids[i],
            this->localEntities,
            *playerConfig,
            "XPBarEndGame" + toString(i + 1));
        xpBarPosition.b += xpBarSize.b * 2.0f;
    }
}

void EndGameScene::update()
{
    try {
        auto &render2D = this->_systemManager.getSystem<System::Render2DSystem>();
        auto &render3D = this->_systemManager.getSystem<System::Render3DSystem>();
        auto &timer = this->_systemManager.getSystem<Engine::TimerSystem>();

        render2D.update();
        render3D.update();
        timer.update();
        this->eventDispatcher(this->_systemManager);
    } catch (std::invalid_argument const &e) {
        std::cerr << e.what() << std::endl;
        exit(84); // TEMPORARY
    }
}