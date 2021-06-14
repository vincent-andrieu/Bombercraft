/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** OptionsMenuScene
*/

#include "OptionsMenuScene.hpp"

using namespace Game;

OptionsMenuScene::OptionsMenuScene(Engine::SystemManager &systemManager)
    : Engine::AbstractScene(systemManager, *CoreData::entityManager)
{
}

static const std::vector<raylib::MyVector2> buttonPosition = {
    raylib::MyVector2(50, 150),
    raylib::MyVector2(650, 150),
    raylib::MyVector2(50, 210),
    raylib::MyVector2(650, 210),
    raylib::MyVector2(50, 270),
    raylib::MyVector2(650, 270)
};

void OptionsMenuScene::open()
{
    auto scene = CoreData::sceneManager->getCurrentScene();
    const GUI::ButtonConfig largeButton = GUI::ButtonFactory::getStandardButtonConfig(raylib::MyVector2(570, 55));
    const GUI::ButtonConfig doneButton = GUI::ButtonFactory::getStandardButtonConfig(raylib::MyVector2(600, 55));

    //BACKGROUND
    GUI::ImageFactory::create(scene->localEntities, raylib::MyVector2(0, 0), CoreData::settings->getMyVector2("WIN_SIZE"), CoreData::settings->getString("DEF_BACKGROUND"), false);
    GUI::ButtonFactory::create(scene->localEntities, buttonPosition[0], "skin", largeButton, "Skin Customization", [](const Engine::Entity) {
        std::cout << "Skin Customization" << std::endl;
    });
    GUI::ButtonFactory::create(scene->localEntities, buttonPosition[1], "music", largeButton, "Music & Sounds", [](const Engine::Entity) {
        std::cout << "Music & Sounds" << std::endl;
    });
    GUI::ButtonFactory::create(scene->localEntities, buttonPosition[2], "video settings", largeButton, "Video Settings", [](const Engine::Entity) {
        std::cout << "Video settings" << std::endl;
    });
    GUI::ButtonFactory::create(scene->localEntities, buttonPosition[3], "controls", largeButton, "Controls", [](const Engine::Entity) {
        CoreData::sceneManager->setScene<KeyBindingMenuScene>();
    });
    GUI::ButtonFactory::create(scene->localEntities, buttonPosition[4], "ressourcepack", largeButton, "Ressource Pack", [](const Engine::Entity) {
        std::cout << "Ressource Pack" << std::endl;
    });
    GUI::SliderFactory::create(this->localEntities, buttonPosition[5],
           [](const Engine::Entity entity, GUI::sliderValue &value) {
               std::cout << "Slider: entity=" << entity << ", value=" << value << std::endl;
           }, "FOV: ", raylib::MyVector2(60, 10), 0, 200, 60);
    GUI::ButtonFactory::create(scene->localEntities, raylib::MyVector2(310, 660), "done", doneButton, "Done", [](const Engine::Entity) {
        CoreData::sceneManager->setScene<MainMenuScene>();
    });
}

void Game::OptionsMenuScene::update()
{
    auto &render2D = this->_systemManager.getSystem<System::Render2DSystem>();

    render2D.update();
    this->eventDispatcher(this->_systemManager);
}