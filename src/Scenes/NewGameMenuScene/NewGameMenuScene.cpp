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

Game::NewGameMenuScene::NewGameMenuScene(Engine::SystemManager &systemManager)
    : Engine::AbstractScene(systemManager, *CoreData::entityManager)
{
}

void Game::NewGameMenuScene::setStandardOptions(Component::OptionComponent &options)
{
    size_t nbPlayers;
    size_t gameTimerDuration;
    uint seed;
    size_t IARandomProb;

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
}

void Game::NewGameMenuScene::init()
{
    Engine::Entity optionEntity = core->globalEntities.getEntity("options");
    auto &options = Game::CoreData::entityManager->getComponent<Component::OptionComponent>(optionEntity);
    const auto &windowSize(Game::CoreData::settings->getMyVector2("WIN_SIZE"));
    ProportionUtilities my_utility(windowSize);
    GUI::ButtonConfig my_smallButtonConfig(GUI::ButtonFactory::getSmallButtonConfig());
    GUI::ButtonConfig my_mediumButtonConfig(GUI::ButtonFactory::getMediumButtonConfig());

    setStandardOptions(options);
    GUI::ImageFactory::create(
        localEntities, raylib::MyVector2(0, 0), windowSize, CoreData::settings->getString("STANDARD_BACKGROUND"), false);

    GUI::LabelConfig labelConfig = GUI::LabelFactory::getStandardLabelConfig((size_t) windowSize.a / 32);
    labelConfig.fontColor = raylib::RColor::RDARKGRAY;
    GUI::TextInputFactory::create(this->localEntities,
        {
            my_utility(50, 20),
            my_utility(GUI::ButtonFactory::LargeProportions),
            "gameInputName",
            "Game name",
        },
        labelConfig,
        true);

    GUI::ButtonFactory::create(localEntities,
        my_utility.getProportion(67, 85),
        my_button_prefix + "cancel",
        my_smallButtonConfig,
        "Cancel",
        [](const Engine::Entity) {
            CoreData::sceneManager->setScene(CoreData::sceneManager->peekLastScene());
        });

    GUI::ButtonFactory::create(localEntities,
        my_utility.getProportion({55.5, 75}),
        my_button_prefix + "newGame",
        my_mediumButtonConfig,
        "Create New Game",
        [](const Engine::Entity) {
            Engine::Entity optionEntity = core->globalEntities.getEntity("options");
            auto &options = Game::CoreData::entityManager->getComponent<Component::OptionComponent>(optionEntity);
            Engine::Entity textInput =
                Game::CoreData::sceneManager->getCurrentScene()->localEntities.getEntity("textInputIASeed");
            auto &textInputRender2D = Game::CoreData::entityManager->getComponent<Component::Render2D>(textInput);
            auto &text = *dynamic_cast<raylib::IText *>(textInputRender2D.get("text").get());
            std::string string = "";

            for (auto c : text.getText())
                if (c != ' ')
                    string += c;
            try {
                options.seed = std::stoul(string, nullptr, 36);
            } catch (...) {
                options.seed = 42;
            }
            Game::CoreData::camera->setFovy(options.fov);
            CoreData::sceneManager->popLastScene();
            CoreData::sceneManager->setScene<GameScene>();
        });
    GUI::ButtonFactory::create(localEntities,
        my_utility.getProportion({20, 55}),
        my_button_prefix + "nb_players",
        my_mediumButtonConfig,
        nbPlayersLabel + std::to_string(options.nbPlayers),
        [&](const Engine::Entity entity) {
            options.nbPlayers++;
            if (options.nbPlayers > 4)
                options.nbPlayers = 1;

            // Change button label
            static_cast<raylib::Text *>(
                Game::CoreData::entityManager->getComponent<Component::Render2D>(entity).get("label").get())
                ->setText(nbPlayersLabel + toString(options.nbPlayers));
        });

    // TODO set IA seed from text input
    // TODO add eventHandler to textInputFactory
    // TODO set textRec, to limit the input inside the borders
    GUI::TextInputFactory::create(localEntities,
        {my_utility.getProportion({20, 65}),
            my_utility.getProportion(GUI::ButtonFactory::MediumProportions),
            "textInputIASeed",
            "Seed"},
        GUI::TextInputFactory::getStandardConfig(),
        labelConfig);
    GUI::SliderFactory::create(
        localEntities,
        my_utility.getProportion({20, 75}),
        [&](const Engine::Entity &, GUI::sliderValue gameDuration) {
            options.gameTimerDuration = gameDuration * 60;
        },
        "Game Duration: ",
        my_utility.getProportion(GUI::ButtonFactory::MediumProportions),
        0,
        60,
        (int) options.gameTimerDuration / 60,
        false);
    GUI::SliderFactory::create(
        localEntities,
        my_utility.getProportion({20, 85}),
        [&](const Engine::Entity &, GUI::sliderValue IARandomProb) {
            options.IARandomProb = IARandomProb;
            options.smoothMode = IARandomProb < 90;
        },
        "AI difficulty: ",
        my_utility.getProportion(GUI::ButtonFactory::MediumProportions),
        0,
        100,
        (int) options.IARandomProb,
        false); // TODO apply it gameScene
    // KEYS
    std::unordered_map<raylib::KeyBoard, Component::eventScript> keyTriggers;
    keyTriggers.emplace(std::make_pair(raylib::KeyBoard::IKEY_ESCAPE, [](Engine::Entity) {
        CoreData::sceneManager->setScene(CoreData::sceneManager->peekLastScene());
    }));
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