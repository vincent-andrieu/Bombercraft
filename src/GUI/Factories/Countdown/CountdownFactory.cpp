/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 08/06/2021 CountdownFactory.cpp.cc
*/

#include "CountdownFactory.hpp"
#include "TimeText.hpp"
#include "Components/Render2D/Render2D.hpp"
#include "Components/Chrono/Chrono.hpp"

using namespace GUI;
using CoreData = Game::CoreData;

static void timer_handler(
    Engine::EntityManager &entityManager, [[maybe_unused]] Engine::SceneManager &sceneManager, const Engine::Entity entity)
{
    try {
        auto &chronoComponent = entityManager.getComponent<Component::Chrono>(entity);

        if (chronoComponent.seconds > 0) {
            chronoComponent.seconds -= 1;
            if (chronoComponent.seconds == 0) {
                chronoComponent.trigger(entity);
            }
            auto &render2d = entityManager.getComponent<Component::Render2D>(entity);
            auto &timeText = *dynamic_cast<TimeText *>(render2d.get("timeText").get());
            timeText.setTime(chronoComponent.seconds);
        }
    } catch (...) {
        std::cerr << "TimerEntity::Handler, An exception occurred" << std::endl;
    }
}

Engine::Entity CountdownFactory::create(Engine::EntityPack &entityPack,
    raylib::MyVector2 position,
    const TimerConfig &config,
    std::size_t countdown,
    CountDownTimeout handler,
    const std::string &name,
    std::size_t refreshMsTime)
{
    Engine::Entity entity;

    if (name.empty()) {
        entity = entityPack.createAnonymousEntity();
    } else {
        entity = entityPack.createEntity(name);
    }
    CoreData::entityManager->addComponent<Engine::Timer>(
        entity, (double) refreshMsTime, *CoreData::entityManager, *CoreData::sceneManager, &timer_handler);
    raylib::MyVector2 textPos(position.a + 5, position.b + 5);
    CoreData::entityManager->addComponent<Component::Render2D>(entity,
        Component::render2dMapModels{
            {"texture", std::make_shared<raylib::Texture>(config.pathTexture, config.size, position)},
            {"timeText",
                std::make_shared<GUI::TimeText>(entity,
                    "00:00",
                    textPos + Game::CoreData::settings->getMyVector2("TIMER_TEXT_SHIFT"),
                    config.fontSize,
                    config.textColor,
                    config.pathFont)},
        });
    CoreData::entityManager->addComponent<Component::Chrono>(
        entity, (double) countdown, [handler](Engine::EntityManager &em, Engine::SceneManager &, const Engine::Entity entity) {
            handler();
            em.removeComponent<Engine::Timer>(entity);
        });
    return entity;
}

Engine::Entity CountdownFactory::create(Engine::EntityPack &entityPack,
    raylib::MyVector2 position,
    std::size_t countdown,
    CountDownTimeout handler,
    std::string const &name,
    std::size_t refreshMsTime)
{
    const TimerConfig &config = CountdownFactory::getStandardConfig();

    return CountdownFactory::create(entityPack, position, config, countdown, handler, name, refreshMsTime);
}

const TimerConfig CountdownFactory::getStandardConfig()
{
    const TimerConfig t = {Game::CoreData::settings->getString("TIMER_TEXTURE"),
        Game::CoreData::settings->getString("STANDARD_FONT"),
        static_cast<std::size_t>(Game::CoreData::settings->getInt("TIMER_FONT_SIZE")),
        CONF_GET_COLOR("TIMER_COLOR"),
        Game::CoreData::settings->getMyVector2("TIMER_SIZE")};
    return t;
}