/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 08/06/2021 TimerFactory.cpp.cc
*/

#include "TimerFactory.hpp"
#include "TimeText.hpp"
#include "Components/Render2D/Render2D.hpp"

using namespace GUI;
using CoreData = Game::CoreData;

static void timer_handler(
    Engine::EntityManager &entityManager, [[maybe_unused]] Engine::SceneManager &sceneManager, const Engine::Entity entity)
{
    try {
        auto &timerComponent = entityManager.getComponent<Engine::Timer>(entity);
        auto &render2d = entityManager.getComponent<Component::Render2D>(entity);
        std::chrono::milliseconds delta = timerComponent.getDelta();
        std::chrono::milliseconds &max = timerComponent.interval;
        std::chrono::milliseconds time = max - delta;
        auto &timeText = *dynamic_cast<TimeText *>(render2d.get("timeText").get());

        timeText.setTime(time);
    } catch (...) {
        std::cerr << "TimerEntity::Handler, An exception occured" << std::endl;
    }
}

void TimerFactory::create(Engine::EntityPack &entityPack, raylib::MyVector2 position, const TimerConfig &config,
    const std::string &name, std::size_t refreshMsTime)
{
    Engine::Entity entity;

    if (name.empty()) {
        entity = entityPack.createAnonymousEntity();
    } else {
        entity = entityPack.createEntity(name);
    }
    CoreData::entityManager->addComponent<Engine::Timer>(
        entity, refreshMsTime, *CoreData::entityManager, *CoreData::sceneManager, &timer_handler);
    CoreData::entityManager->addComponent<Component::Render2D>(entity,
        Component::render2dMapModels{
            {"texture", std::make_shared<raylib::Texture>(config.pathTexture, position)},
            {"timeText", std::make_shared<GUI::TimeText>(entity, "00:00", position, config.fontSize, config.textColor, config.pathFont)}});
}

void TimerFactory::create(
    Engine::EntityPack &entityPack, raylib::MyVector2 position, std::string const &name, std::size_t refreshMsTime)
{
    const TimerConfig &config = TimerFactory::getStandardConfig();

    TimerFactory::create(entityPack, position, config, name, refreshMsTime);
}

const TimerConfig TimerFactory::getStandardConfig()
{
    const TimerConfig t = {
        Game::CoreData::settings->getString("TIMER_TEXTURE"),
        Game::CoreData::settings->getString("DEF_FONT"),
        static_cast<std::size_t>(Game::CoreData::settings->getInt("DEF_FONT_SIZE")),
        CONF_GET_COLOR("TIMER_COLOR"),
        Game::CoreData::settings->getMyVector2("TIMER_SIZE")
    };
    return t;
}
