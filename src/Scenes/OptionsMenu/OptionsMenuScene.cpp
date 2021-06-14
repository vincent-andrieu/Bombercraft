/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** OptionsMenuScene
*/

#include <sstream>
#include "OptionsMenuScene.hpp"
#include "Scenes/SoundOption/SoundOptionScene.hpp"
#include "Scenes/SkinChoice/SkinChoiceScene.hpp"
#include "Utilities/ProportionUtilities.hpp"

using namespace Game;

static void handlerDefaultButton(Engine::Entity entity)
{
    static std::size_t counter = 1;

    auto &render = CoreData::entityManager->getComponent<Component::Render2D>(entity);
    raylib::Text &label = *static_cast<raylib::Text *>(render.get("label").get());

    std::ostringstream os;
    for (std::size_t i = 0; i < counter; i++) {
        os << "Nope.";
    }
    label.setText(os.str());
    counter = (counter == 6) ? 0 : counter + 1;
}

OptionsMenuScene::OptionsMenuScene(Engine::SystemManager &systemManager)
    : Engine::AbstractScene(systemManager, *CoreData::entityManager)
{
}

void OptionsMenuScene::open()
{
    auto scene = CoreData::sceneManager->getCurrentScene();
    const raylib::MyVector2 &window_size = CoreData::settings->getMyVector2("WIN_SIZE");
    const ProportionUtilities resizer(window_size);
    const GUI::ButtonConfig &menuButtons = GUI::ButtonFactory::getMediumButtonConfig();
    const GUI::ButtonConfig &doneButton = GUI::ButtonFactory::getLargeButtonConfig();
    const std::vector<raylib::MyVector2> buttonPosition = {
        resizer(raylib::MyVector2(25, 25)),
        resizer(raylib::MyVector2(50.5, 25)),
        resizer(raylib::MyVector2(25, 35)),
        resizer(raylib::MyVector2(50.5, 35)),
        resizer(raylib::MyVector2(25, 45)),
        resizer(raylib::MyVector2(50.5, 45)),
    };

    // BACKGROUND
    GUI::ImageFactory::create(
        scene->localEntities, raylib::MyVector2(0, 0), window_size, CoreData::settings->getString("DEF_BACKGROUND"), false);
    GUI::ButtonFactory::create(
        scene->localEntities, buttonPosition[0], "skin", menuButtons, "Skin Customization...", [](const Engine::Entity) {
            CoreData::sceneManager->setScene<SkinChoiceScene>();
        });
    GUI::ButtonFactory::create(
        scene->localEntities, buttonPosition[1], "music", menuButtons, "Music & Sounds", [](const Engine::Entity) {
            CoreData::sceneManager->setScene<SoundOptionScene>();
            std::cout << "Music & Sounds" << std::endl;
        });
    GUI::ButtonFactory::create(
        scene->localEntities, buttonPosition[2], "video settings", menuButtons, "Video Settings", handlerDefaultButton);
    GUI::ButtonFactory::create(
        scene->localEntities, buttonPosition[3], "controls", menuButtons, "Controls...", [](const Engine::Entity) {
            CoreData::sceneManager->setScene<KeyBindingMenuScene>();
        });
    GUI::ButtonFactory::create(
        scene->localEntities, buttonPosition[4], "resourcePack", menuButtons, "Resource Pack", handlerDefaultButton);
    GUI::SliderFactory::create(
        this->localEntities,
        buttonPosition[5],
        [](const Engine::Entity entity, GUI::sliderValue &value) {
            std::cout << "Slider: entity=" << entity << ", value=" << value << std::endl;
        },
        "FOV: ",
        menuButtons.size,
        0,
        200,
        60);
    GUI::ButtonFactory::create(scene->localEntities,
        resizer(raylib::MyVector2(50, 80), doneButton.size, raylib::MyVector2(50, 0)),
        "done",
        doneButton,
        "Done",
        [](const Engine::Entity) {
            CoreData::sceneManager->setScene<MainMenuScene>();
        });
}

void Game::OptionsMenuScene::update()
{
    auto &render2D = this->_systemManager.getSystem<System::Render2DSystem>();

    render2D.update();
    this->eventDispatcher(this->_systemManager);
}