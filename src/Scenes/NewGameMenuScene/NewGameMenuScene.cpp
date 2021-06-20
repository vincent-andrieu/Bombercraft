/*
** EPITECH PROJECT, 2021
** NewGameMenuScene.cpp
** File description:
** Implementation of scene to display previous games before choosing or creating one to play
*/

#include "NewGameMenuScene.hpp"
#include "Systems/Render2D/Render2DSystem.hpp"
#include "Utilities/ProportionUtilities.hpp"
#include "GUI/Factories/Button/ButtonFactory.hpp"
#include "Scenes/GameScene/GameScene.hpp"
#include "GUI/Factories/TextInput/TextInputFactory.hpp"

static const string my_button_prefix("button_");
static const string nbPlayersLabel("Number of Players: ");

extern std::unique_ptr<Game::Core> core;

static const Component::eventScript cancelButtonHandler = [](const Engine::Entity &) {
    Game::CoreData::sceneManager->setScene(Game::CoreData::sceneManager->peekLastScene());
};

static const Component::eventScript startButtonHandler = [](const Engine::Entity) {
    Engine::Entity optionEntity = core->globalEntities.getEntity("options");
    auto &options = Game::CoreData::entityManager->getComponent<Component::OptionComponent>(optionEntity);
    Engine::Entity textInputSeed = Game::CoreData::sceneManager->getCurrentScene()->localEntities.getEntity("textInputIASeed");
    Engine::Entity textInputName = Game::CoreData::sceneManager->getCurrentScene()->localEntities.getEntity("textInputGameName");
    auto &textInputRender2DSeed = Game::CoreData::entityManager->getComponent<Component::Render2D>(textInputSeed);
    auto &textInputRender2DName = Game::CoreData::entityManager->getComponent<Component::Render2D>(textInputName);
    auto &textSeed = *dynamic_cast<raylib::IText *>(textInputRender2DSeed.get("text").get());
    auto &textName = *dynamic_cast<raylib::IText *>(textInputRender2DName.get("text").get());
    std::string string = "";

    for (auto c : textSeed.getText())
        if (c != ' ')
            string += c;
    try {
        options.seed = std::stoul(string, nullptr, 36);
    } catch (...) {
        options.seed = 42;
    }
    options.saveName = textName.getText();
    Game::CoreData::sceneManager->popLastScene();
    Game::CoreData::sceneManager->setScene<Game::GameScene>();
};

Game::NewGameMenuScene::NewGameMenuScene(Engine::SystemManager &systemManager)
    : Engine::AbstractScene(systemManager, *CoreData::entityManager)
{
}

static void resetPlayerConfigs()
{
    Component::PlayerConfig *config[MAX_PLAYERS] = {
        &Game::CoreData::entityManager->getComponent<Component::PlayerConfig>(core->globalEntities.getEntity("config1")),
        &Game::CoreData::entityManager->getComponent<Component::PlayerConfig>(core->globalEntities.getEntity("config2")),
        &Game::CoreData::entityManager->getComponent<Component::PlayerConfig>(core->globalEntities.getEntity("config3")),
        &Game::CoreData::entityManager->getComponent<Component::PlayerConfig>(core->globalEntities.getEntity("config4"))};

    for (uint i = 0; i < MAX_PLAYERS; ++i) {
        config[i]->setStatus(Component::PlayerStatus::ALIVE);
        config[i]->setXP(0);
    }
}

void Game::NewGameMenuScene::setStandardOptions(Component::OptionComponent &options)
{
    size_t nbPlayers = 1;
    size_t gameTimerDuration = 300;
    uint seed = 0;
    size_t IARandomProb = 0;

    if (Game::CoreData::settings->isSetInFile("NB_PLAYERS")) {
        nbPlayers = (uint) CoreData::settings->getInt("NB_PLAYERS");
        if (nbPlayers > 4 || nbPlayers <= 0)
            nbPlayers = 1;
        options.nbPlayers = nbPlayers;
    }
    if (Game::CoreData::settings->isSetInFile("STANDARD_COUNTDOWN")) {
        gameTimerDuration = (size_t) CoreData::settings->getInt("STANDARD_COUNTDOWN");
        options.gameTimerDuration = gameTimerDuration;
    }
    if (Game::CoreData::settings->isSetInFile("SEED")) {
        seed = (uint) CoreData::settings->getInt("SEED");
        options.seed = seed;
    }
    if (Game::CoreData::settings->isSetInFile("IA_RANDOM_PROB")) {
        IARandomProb = (size_t) CoreData::settings->getInt("IA_RANDOM_PROB");
        options.IARandomProb = (IARandomProb * -1) + 100;
    }
    resetPlayerConfigs();
    options.loadName = "";
}

void Game::NewGameMenuScene::init()
{
    const Engine::Entity &optionEntity = core->globalEntities.getEntity("options");
    auto &options = Game::CoreData::entityManager->getComponent<Component::OptionComponent>(optionEntity);
    const auto &windowSize(Game::CoreData::settings->getMyVector2("WIN_SIZE"));
    const auto &buttonConfig = GUI::ButtonFactory::getMediumButtonConfig();
    const ProportionUtilities resizer(windowSize);

    setStandardOptions(options);
    GUI::ImageFactory::create(
        localEntities, raylib::MyVector2(0, 0), windowSize, CoreData::settings->getString("STANDARD_BACKGROUND"), false);
    GUI::LabelFactory::createCentered(this->localEntities, resizer(50, 4), "New game", GUI::LabelFactory::getStandardLabelConfig());

    GUI::LabelConfig labelConfig = GUI::LabelFactory::getStandardLabelConfig((size_t) windowSize.a / 32);
    labelConfig.fontColor = raylib::RColor::RDARKGRAY;
    GUI::TextInputFactory::create(this->localEntities,
        {
            resizer(50, 20),
            resizer(GUI::ButtonFactory::LargeProportions),
            "textInputGameName",
            "GameName",
        },
        labelConfig,
        true);

    GUI::ButtonFactory::create(
        localEntities, resizer(65, 90), my_button_prefix + "cancel", buttonConfig, "Cancel", cancelButtonHandler, true);

    GUI::ButtonFactory::create(
        localEntities, resizer(35, 90), my_button_prefix + "newGame", buttonConfig, "Start", startButtonHandler, true);
    GUI::ButtonFactory::create(
        localEntities,
        resizer(30, 40),
        my_button_prefix + "nb_players",
        buttonConfig,
        nbPlayersLabel + toString(options.nbPlayers),
        [&](const Engine::Entity entity) {
            options.nbPlayers++;
            if (options.nbPlayers > 4)
                options.nbPlayers = 1;

            // Change button label
            static_cast<raylib::Text *>(Game::CoreData::entityManager->getComponent<Component::Render2D>(entity).get("label").get())
                ->setText(nbPlayersLabel + toString(options.nbPlayers));
        },
        true);

    GUI::TextInputFactory::create(localEntities,
        {resizer(30, 55), resizer(GUI::ButtonFactory::MediumProportions), "textInputIASeed", "Seed"},
        GUI::TextInputFactory::getStandardConfig(),
        labelConfig,
        true);
    GUI::SliderFactory::create(
        localEntities,
        resizer(70, 40),
        [&](const Engine::Entity &, GUI::sliderValue gameDuration) {
            options.gameTimerDuration = gameDuration * 60;
        },
        "Game Duration: ",
        resizer(GUI::ButtonFactory::MediumProportions),
        0,
        60,
        (GUI::sliderValue) options.gameTimerDuration / 60,
        true);
    GUI::SliderFactory::create(
        localEntities,
        resizer(70, 55),
        [&](const Engine::Entity &, GUI::sliderValue IARandomProb) {
            options.IARandomProb = IARandomProb;
            options.smoothMode = IARandomProb < 90;
        },
        "AI difficulty: ",
        resizer(GUI::ButtonFactory::MediumProportions),
        0,
        100,
        (GUI::sliderValue) options.IARandomProb,
        true);
    // KEYS
    std::unordered_map<raylib::KeyBoard, Component::eventScript> keyTriggers;
    keyTriggers.emplace(std::make_pair(raylib::KeyBoard::IKEY_ESCAPE, cancelButtonHandler));
    keyTriggers.emplace(std::make_pair(raylib::KeyBoard::IKEY_ENTER, cancelButtonHandler));
    Game::KeyManagementFactory::create(this->localEntities, keyTriggers);
}

void Game::NewGameMenuScene::open()
{
    init();
}

void Game::NewGameMenuScene::update()
{
    auto &render2D = this->_systemManager.getSystem<System::Render2DSystem>();

    render2D.update();
    this->eventDispatcher(this->_systemManager);
}