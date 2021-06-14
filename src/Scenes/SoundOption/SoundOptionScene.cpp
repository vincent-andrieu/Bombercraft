/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 14/06/2021 SoundOptionScene.cpp.cc
*/

#include "SoundOptionScene.hpp"
#include "GUI/Factories/Slider/SliderFactory.hpp"
#include "GUI/Factories/Button/ButtonFactory.hpp"
#include "Scenes/OptionsMenu/OptionsMenuScene.hpp"
#include "Systems/Render2D/Render2DSystem.hpp"
#include "Systems/Audio/AudioSystem.hpp"
#include "Utilities/ProportionUtilities.hpp"
#include "Game/Core/Core.hpp"
#include "Components/Option/OptionComponent.hpp"

using namespace Game;

extern std::unique_ptr<Game::Core> core;

static void handler_slider(Engine::Entity, GUI::sliderValue &value)
{
    float volume = ((float) value / 100);
    Engine::Entity optionEntity = core->globalEntities.getEntity("options");
    auto &options = CoreData::entityManager->getComponent<Component::OptionComponent>(optionEntity);
    auto &audioSystem = CoreData::systemManager->getSystem<System::AudioSystem>();

    options.volume = volume;
    audioSystem.setVolume(volume);
}

Game::SoundOptionScene::SoundOptionScene() : Engine::AbstractScene(*CoreData::systemManager, *CoreData::entityManager)
{
}

void Game::SoundOptionScene::open()
{
    const raylib::MyVector2 window_size(CoreData::settings->getMyVector2("WIN_SIZE"));
    const GUI::ButtonConfig doneButton = GUI::ButtonFactory::getStandardButtonConfig(raylib::MyVector2(600, 55));
    ProportionUtilities pos(window_size);
    Engine::Entity optionEntity = core->globalEntities.getEntity("options");
    auto &options = CoreData::entityManager->getComponent<Component::OptionComponent>(optionEntity);

    /// Background
    GUI::ImageFactory::create(
        this->localEntities, raylib::MyVector2(0, 0), window_size, CoreData::settings->getString("STANDARD_BACKGROUND"), false);
    /// Quit button
    GUI::ButtonFactory::create(
        this->localEntities, raylib::MyVector2(310, 660), "done", doneButton, "Done", [](const Engine::Entity) {
            CoreData::sceneManager->setScene(CoreData::sceneManager->peekLastScene());
        });
    /// Slider
    GUI::SliderFactory::create(this->localEntities,
        raylib::MyVector2(100, 50),
        handler_slider,
        "Master Volume: ",
        GUI::ButtonFactory::getMediumButtonConfig().size,
        0,
        100,
        static_cast<GUI::sliderValue>(options.volume * 100));
}

void Game::SoundOptionScene::update()
{
    auto &render2D = this->_systemManager.getSystem<System::Render2DSystem>();

    render2D.update();
    this->eventDispatcher(this->_systemManager);
}