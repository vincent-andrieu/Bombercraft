/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** OptionsMenuScene
*/

#include "OptionsMenuScene.hpp"
#include "Scenes/SoundOption/SoundOptionScene.hpp"
#include <sstream>

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

static const std::vector<raylib::MyVector2> buttonPosition = {raylib::MyVector2(50, 150),
    raylib::MyVector2(650, 150),
    raylib::MyVector2(50, 210),
    raylib::MyVector2(650, 210),
    raylib::MyVector2(50, 270),
    raylib::MyVector2(650, 270)};

void OptionsMenuScene::open()
{
    auto scene = CoreData::sceneManager->getCurrentScene();
    const GUI::ButtonConfig largeButton = GUI::ButtonFactory::getStandardButtonConfig(raylib::MyVector2(570, 55));
    const GUI::ButtonConfig doneButton = GUI::ButtonFactory::getStandardButtonConfig(raylib::MyVector2(600, 55));

    // BACKGROUND
    GUI::ImageFactory::create(scene->localEntities,
        raylib::MyVector2(0, 0),
        CoreData::settings->getMyVector2("WIN_SIZE"),
        CoreData::settings->getString("STANDARD_BACKGROUND"),
        false);
    GUI::ButtonFactory::create(
        scene->localEntities, buttonPosition[0], "skin", largeButton, "Skin Customization", [](const Engine::Entity) {
            std::cout << "Skin Customization" << std::endl;
        });
    GUI::ButtonFactory::create(
        scene->localEntities, buttonPosition[1], "music", largeButton, "Music & Sounds", [](const Engine::Entity) {
            CoreData::sceneManager->setScene<SoundOptionScene>();
            std::cout << "Music & Sounds" << std::endl;
        });
    GUI::ButtonFactory::create(
        scene->localEntities, buttonPosition[2], "video settings", largeButton, "Video Settings", handlerDefaultButton);
    GUI::ButtonFactory::create(
        scene->localEntities, buttonPosition[3], "controls", largeButton, "Controls...", [](const Engine::Entity) {
            CoreData::sceneManager->setScene<KeyBindingMenuScene>();
        });
    GUI::ButtonFactory::create(
        scene->localEntities, buttonPosition[4], "resourcePack", largeButton, "Resource Pack", handlerDefaultButton);
    GUI::SliderFactory::create(
        this->localEntities,
        buttonPosition[5],
        [](const Engine::Entity entity, GUI::sliderValue &value) {
            std::cout << "Slider: entity=" << entity << ", value=" << value << std::endl;
        },
        "FOV: ",
        raylib::MyVector2(60, 10),
        Game::CoreData::settings->getMyVector2(SLIDER_CONFIG_SIZE),
        0,
        200,
        60);
    GUI::ButtonFactory::create(
        scene->localEntities, raylib::MyVector2(310, 660), "done", doneButton, "Done", [](const Engine::Entity) {
            CoreData::sceneManager->setScene(CoreData::sceneManager->getLastScene());
        });
}

void Game::OptionsMenuScene::update()
{
    auto &render2D = this->_systemManager.getSystem<System::Render2DSystem>();

    render2D.update();
    this->eventDispatcher(this->_systemManager);
}