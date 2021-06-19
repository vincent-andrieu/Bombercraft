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
#include "Components/PlayerIdBox.hpp"

extern std::unique_ptr<Game::Core> core;

static void timer_handler([[maybe_unused]] Engine::EntityManager &entityManager,
    [[maybe_unused]] Engine::SceneManager &sceneManager,
    [[maybe_unused]] const Engine::Entity entity)
{
    try {
        std::shared_ptr<Engine::AbstractScene> scene = sceneManager.getCurrentScene();
        Component::PlayerID playerID = entityManager.getComponent<Component::PlayerIdBox>(entity).id;
        auto &playerConfig = entityManager.getComponent<Component::PlayerConfig>(
            core->globalEntities.getEntity("config" + toString(playerID + 1)));
        const size_t playerXp = playerConfig.getXP();
        auto &XPBarRender2d = entityManager.getComponent<Component::Render2D>(entity);

        raylib::Texture &emptyXPBar = (*dynamic_cast<raylib::Texture *>(XPBarRender2d.get("EmptyXPBar").get()));
        raylib::Texture &fullXPBar = (*dynamic_cast<raylib::Texture *>(XPBarRender2d.get("FullXPBar").get()));
        float xpPercentage = (float) (playerXp % 101) / 100;

        raylib::MyVector2 const &emptyBarSize = emptyXPBar.getSize();
        fullXPBar.setTruncateSize({(emptyBarSize.a - (xpPercentage * emptyBarSize.a)), 0});
    } catch (std::exception const &e) {
        std::cerr << "XPBar Timer Handler, An exception occurred : " << e.what() << std::endl;
    }
}

void GUI::XPBarFactory::create(const raylib::MyVector2 &position,
    const raylib::MyVector2 &size,
    std::vector<std::string> const &texturesPath,
    Component::PlayerID id,
    Engine::EntityPack &pack,
    const std::string &name)
{
    Engine::Entity entity;

    if (texturesPath.size() != 2)
        return;
    if (name.empty())
        entity = pack.createAnonymousEntity();
    else
        entity = pack.createEntity(name);
    Game::CoreData::entityManager->addComponent<Component::Render2D>(entity,
        Component::render2dMapModels({
            {"EmptyXPBar",
              std::make_shared<raylib::Texture>(texturesPath[0],
                  size,
                  position,
                  raylib::RColor::RWHITE,
                true,
                raylib::MyVector2(0, 0)) },
            {"FullXPBar",
                std::make_shared<raylib::Texture>(texturesPath[1],
                    size,
                    position,
                    raylib::RColor::RWHITE,
                    true,
                    raylib::MyVector2(size.a, 0)
                    )
            }
            })
        );
    timer_handler(*Game::CoreData::entityManager, *Game::CoreData::sceneManager, entity); // first update
    Game::CoreData::entityManager->addComponent<Engine::Timer>(
        entity, 1.0f, *Game::CoreData::entityManager, *Game::CoreData::sceneManager, &timer_handler);
    Game::CoreData::entityManager->addComponent<Component::PlayerIdBox>(entity, id);
}