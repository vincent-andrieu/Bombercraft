/*
** EPITECH PROJECT, 2021
** PauseMenuScene.cpp
** File description:
** Implementation of scene : pause menu, during a game
*/

#include "PauseMenuScene.hpp"
#include "GUI/Factories/Button/ButtonFactory.hpp"
#include "Systems/Render2D/Render2DSystem.hpp"
#include "Utilities/ProportionUtilities.hpp"
#include "Scenes/MainMenu/MainMenuScene.hpp"
#include "Game/Factories/Map/MapFactory.hpp"

extern std::unique_ptr<Game::Core> core;
extern const std::unordered_map<Component::PlayerID, std::string> Game::PLAYER_ID_TO_NAME;

using namespace Game;

Game::PauseMenuScene::PauseMenuScene(Engine::SystemManager &systemManager)
    : AbstractScene(systemManager, *Game::CoreData::entityManager)
{
}

static void goGameScene(const Engine::Entity)
{
    Engine::Entity optionEntity = core->globalEntities.getEntity("options");
    auto &options = Game::CoreData::entityManager->getComponent<Component::OptionComponent>(optionEntity);
    const std::vector<Component::PlayerID> ids = {Component::ALPHA, Component::BRAVO, Component::CHARLIE, Component::DELTA};
    Component::PlayerConfig *config[4] = {
        &Game::CoreData::entityManager->getComponent<Component::PlayerConfig>(core->globalEntities.getEntity("config1")),
        &Game::CoreData::entityManager->getComponent<Component::PlayerConfig>(core->globalEntities.getEntity("config2")),
        &Game::CoreData::entityManager->getComponent<Component::PlayerConfig>(core->globalEntities.getEntity("config3")),
        &Game::CoreData::entityManager->getComponent<Component::PlayerConfig>(core->globalEntities.getEntity("config4"))};

    Game::CoreData::camera->setFovy((float) options.fov);
    Game::CoreData::moveCamera(
        Game::CoreData::settings->getMyVector3("CAM_POSITION"), Game::CoreData::settings->getMyVector3("CAM_TARGET"));
    Game::CoreData::camera->setUp(Game::CoreData::settings->getMyVector3("CAM_UP"));
    Game::CoreData::systemManager->getSystem<Engine::TimerSystem>().resume();
    Game::CoreData::sceneManager->setScene<Game::GameScene>(true, false);

    auto scene = Game::Core::sceneManager->peekLastScene();
    try {
        if (scene->localEntities.entityIsSet("gameMap")) {
            const std::string &resourcePackRoot = options.ressourcePack;
            Engine::Entity map = scene->localEntities.getEntity("gameMap");
            for (size_t i = 0; i < 4; i++) {
                if (scene->localEntities.entityIsSet(Game::PLAYER_ID_TO_NAME.at(ids[i]))) {
                    Engine::Entity player = scene->localEntities.getEntity(Game::PLAYER_ID_TO_NAME.at(ids[i]));
                    /// Update skin
                    auto &modelList = Game::CoreData::entityManager->getComponent<Component::ModelList>(player);
                    const std::string &texturePath = (*config[i]).getSkinPath();
                    modelList.setTexture(texturePath);
                    /// Update keybiding
                    if (Game::CoreData::entityManager->hasComponent<Component::KeyEvent>(player)) {
                        const Engine::EntityBox &inventoryEntityBox =
                            Game::CoreData::entityManager->getComponent<Engine::EntityBox>(player);
                        const Component::PlayerInventory &inventory =
                            Game::CoreData::entityManager->getComponent<Component::PlayerInventory>(inventoryEntityBox.entity);
                        const Component::PlayerInventoryInfo &info = inventory.getPlayerInventoryInfo();
                        if (info.config != nullptr) {
                            const Component::PlayerKeyBindings &keys = info.config->getPlayerKeyBindings();
                            const Game::EventRequirement requirements(
                                info.config->getPlayerKeyList(), {keys.moveRight, keys.moveLeft, keys.moveDown, keys.moveUp});
                            Game::CoreData::entityManager->getComponent<Component::KeyEvent>(player).setRequirements(requirements);
                        }
                    }
                    /// Update map textures
                    GUI::MapFactory::updateMapTextures(resourcePackRoot, map);
                }
            }
        }
    } catch (std::invalid_argument const &e) {
        std::cerr << "Warning: fail to apply options " << e.what() << std::endl;
    }
}

void Game::PauseMenuScene::open()
{
    const raylib::MyVector2 windowSize(CoreData::settings->getMyVector2("WIN_SIZE"));
    ProportionUtilities my_utility(CoreData::settings->getMyVector2("WIN_SIZE"));
    auto my_buttonConfig(GUI::ButtonFactory::getLargeButtonConfig());
    const std::string my_buttonNamePrefix("button_");

    GUI::ImageFactory::create(
        this->localEntities, raylib::MyVector2(0, 0), windowSize, CoreData::settings->getString("GAME_SCREENSHOT"), false);
    auto background = this->localEntities.createEntity("PauseBackground");
    CoreData::entityManager->addComponent<Component::Render2D>(background,
        Component::render2dMapModels({{"PauseBackgroundRectangle",
            std::make_shared<raylib::Rectangle>(raylib::MyVector2(0, 0), windowSize, raylib::RColor::RSHADOW)}}));
    GUI::LabelFactory::createCentered(localEntities,
        my_utility.getProportion(raylib::MyVector2(50, 20)),
        "Game Menu",
        GUI::LabelFactory::getStandardLabelConfig(CoreData::settings->getInt("STANDARD_FONT_SIZE")));

    GUI::ButtonFactory::create(localEntities,
        my_utility.getProportion({50, 40}, my_buttonConfig.size),
        my_buttonNamePrefix + "continue",
        my_buttonConfig,
        "Back to Game",
        goGameScene);
    GUI::ButtonFactory::create(localEntities,
        my_utility.getProportion({50, 60}, my_buttonConfig.size),
        my_buttonNamePrefix + "options",
        my_buttonConfig,
        "Options...",
        [](const Engine::Entity) {
            CoreData::sceneManager->pushLastScene();
            CoreData::sceneManager->setScene<OptionsMenuScene>();
        });
    GUI::ButtonFactory::create(localEntities,
        my_utility.getProportion({50, 70}, my_buttonConfig.size),
        my_buttonNamePrefix + "quit",
        my_buttonConfig,
        "Save and quit to title",
        [](const Engine::Entity) {
            auto my_gameScene(std::dynamic_pointer_cast<GameScene>(CoreData::sceneManager->getLastScene()));
            Engine::Entity optionEntity = core->globalEntities.getEntity("options");
            const auto &options = Game::CoreData::entityManager->getComponent<Component::OptionComponent>(optionEntity);
            if (!options.saveName.empty())
                my_gameScene->saveGame(options.saveName);
            CoreData::sceneManager->closeLastUnclosedScene();
            CoreData::sceneManager->setScene<Game::MainMenuScene>();
        });

    std::unordered_map<raylib::KeyBoard, Component::eventScript> my_keyTriggers;
    my_keyTriggers.emplace(std::make_pair(raylib::KeyBoard::IKEY_ESCAPE, goGameScene));
    Game::KeyManagementFactory::create(localEntities, my_keyTriggers);
}

void Game::PauseMenuScene::update()
{
    auto &render2D = this->_systemManager.getSystem<System::Render2DSystem>();

    render2D.update();
    this->eventDispatcher(this->_systemManager);
}