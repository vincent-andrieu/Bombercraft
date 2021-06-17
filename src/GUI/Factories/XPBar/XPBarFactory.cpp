/*
** EPITECH PROJECT, 2021
** Indie Studio
** File description:
** XPBarFactory
*/

#include "XPBarFactory.hpp"
#include "Game/Core/Core.hpp"
#include "Game/CoreData/CoreData.hpp"
#include "Components/Render2D/Render2D.hpp"

extern std::unique_ptr<Game::Core> core;

static void timer_handler([[maybe_unused]] Engine::EntityManager &entityManager,
    [[maybe_unused]] Engine::SceneManager &sceneManager,
    [[maybe_unused]] const Engine::Entity entity)
{
    try {
        std::shared_ptr<Engine::AbstractScene> scene = sceneManager.getCurrentScene();
        auto &playerConfig = entityManager.getComponent<Component::PlayerConfig>(entity);
        auto &realPlayerConfig = entityManager.getComponent<Component::PlayerConfig>(
            core->globalEntities.getEntity("config" + toString(playerConfig.getPlayerId() + 1)));
        auto &XPBarRender2d = entityManager.getComponent<Component::Render2D>(
            scene->localEntities.getEntity("XPBarEndGame" + toString(playerConfig.getPlayerId() + 1)));
        auto &emptyXPBar = (*dynamic_cast<raylib::Texture *>(XPBarRender2d.get("EmptyXPBar").get()));
        auto &fullXPBar = (*dynamic_cast<raylib::Texture *>(XPBarRender2d.get("FullXPBar").get()));
        raylib::MyVector2 ogSize = {emptyXPBar.getSize().b * 36.4f, emptyXPBar.getSize().b};
        raylib::MyVector2 ogPos = {fullXPBar.getPosition().a, fullXPBar.getPosition().b};
        float xpPercentage = (float) (realPlayerConfig.getXP() % 100);
        float currentXpPercentage = (fullXPBar.getSize().a / ogSize.a) * 100.0f;
        raylib::MyVector2 fullXPBarSize = {ogSize.a * (xpPercentage / 100.0f), ogSize.b};
        raylib::MyVector2 emptyXPBarSize = {ogSize.a * ((100.0f - xpPercentage) / 100.0f), ogSize.b};
        raylib::MyVector2 emptyXPBarPosition = {ogPos.a + ogSize.a - ogSize.a * ((100.0f - xpPercentage) / 100.0f), ogPos.b};
        raylib::MyVector4 emptyXPBarOgRectPercentage = {xpPercentage / 100.0f, 1, (100.0f - xpPercentage) / 100.0f, 1.0f};
        raylib::MyVector4 fullXPBarOgRectPercentage = {0.0f, 1.0f, xpPercentage / 100.0f, 1.0f};

        if (currentXpPercentage + 1 < xpPercentage) {
            fullXPBar.setSize({ogSize.a * ((currentXpPercentage + 1.0f) / 100.0f), ogSize.b});
            emptyXPBar.setSize({ogSize.a * ((100.0f - (currentXpPercentage + 1.0f)) / 100.0f), ogSize.b});
            emptyXPBar.setPosition({ogPos.a + ogSize.a - ogSize.a * ((100.0f - (currentXpPercentage + 1.0f)) / 100.0f), ogPos.b});
            emptyXPBar.setOgRect(
                {(currentXpPercentage + 1.0f) / 100.0f, 1.0f, (100.0f - (currentXpPercentage + 1.0f)) / 100.0f, 1.0f});
            fullXPBar.setOgRect({0.0f, 1.0f, (currentXpPercentage + 1.0f) / 100.0f, 1.0f});
        } else {
            fullXPBar.setSize(fullXPBarSize);
            emptyXPBar.setSize(emptyXPBarSize);
            emptyXPBar.setPosition(emptyXPBarPosition);
            emptyXPBar.setOgRect(emptyXPBarOgRectPercentage);
            fullXPBar.setOgRect(fullXPBarOgRectPercentage);
        }
    } catch (...) {
        std::cerr << "TimerEntity::Handler, An exception occurred" << std::endl;
    }
}

void GUI::XPBarFactory::create(const raylib::MyVector2 &position,
    const raylib::MyVector2 &size,
    std::vector<std::string> const &texturesPath,
    Component::PlayerID id,
    Engine::EntityPack &pack,
    Component::PlayerConfig &config,
    const std::string &name)
{
    float xpPercentage = 0.0f;
    raylib::MyVector2 fullXPBarSize = {size.a * (xpPercentage / 100.0f), size.b};
    raylib::MyVector2 emptyXPBarSize = {size.a * ((100.0f - xpPercentage) / 100.0f), size.b};
    raylib::MyVector2 emptyXPBarPosition = {position.a + size.a - size.a * ((100.0f - xpPercentage) / 100.0f), position.b};
    raylib::MyVector4 emptyXPBarOgRectPercentage = {xpPercentage / 100.0f, 1, (100.0f - xpPercentage) / 100.0f, 1};
    raylib::MyVector4 fullXPBarOgRectPercentage = {0, 1, xpPercentage / 100.0f, 1};
    Engine::Entity entity;

    if (texturesPath.size() != 2)
        return;
    if (name.empty())
        entity = pack.createAnonymousEntity();
    else
        entity = pack.createEntity(name);
    Game::CoreData::entityManager->addComponent<Component::Render2D>(entity,
        Component::render2dMapModels({{"EmptyXPBar",
                                          std::make_shared<raylib::Texture>(texturesPath[0],
                                              emptyXPBarSize,
                                              emptyXPBarPosition,
                                              raylib::RColor::RWHITE,
                                              true,
                                              emptyXPBarPosition,
                                              emptyXPBarOgRectPercentage)},
            {"FullXPBar",
                std::make_shared<raylib::Texture>(texturesPath[1],
                    fullXPBarSize,
                    position,
                    raylib::RColor::RWHITE,
                    true,
                    position,
                    fullXPBarOgRectPercentage)}}));
    Game::CoreData::entityManager->addComponent<Engine::Timer>(
        entity, 0.02f, *Game::CoreData::entityManager, *Game::CoreData::sceneManager, &timer_handler);
    Game::CoreData::entityManager->addComponent<Component::PlayerConfig>(entity, id, config.getPlayerKeyBindings());
}