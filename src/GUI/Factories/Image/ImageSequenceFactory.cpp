/*
** EPITECH PROJECT, 2021
** Indie Studio
** File description:
** Image Sequence Factory
*/

#include "ImageSequenceFactory.hpp"
#include "Game/CoreData/CoreData.hpp"
#include "Components/Render2D/Render2D.hpp"

static void timer_handler(
    Engine::EntityManager &entityManager, [[maybe_unused]] Engine::SceneManager &sceneManager, const Engine::Entity entity)
{
    try {
        auto &render2d = entityManager.getComponent<Component::Render2D>(entity);
        auto &imageSequence = *dynamic_cast<raylib::ITexture *>(render2d.get("imageSequence").get());

        imageSequence.update();
    } catch (...) {
        std::cerr << "TimerEntity::Handler, An exception occurred" << std::endl;
    }
}

void GUI::ImageSequenceFactory::create(Engine::EntityPack &entityPack, const raylib::MyVector2 &position,
    const raylib::MyVector2 &size, const std::string &directoryPath, const std::string &name, const double frameRate)
{
    Engine::Entity entity;

    if (name.empty()) {
        entity = entityPack.createAnonymousEntity();
    } else {
        entity = entityPack.createEntity(name);
    }
    Game::CoreData::entityManager->addComponent<Component::Render2D>(entity,
        Component::render2dMapModels{
            {"imageSequence", std::make_shared<raylib::TextureSequence>(directoryPath, size, position)}});
    Game::CoreData::entityManager->addComponent<Engine::Timer>(
        entity, frameRate, *Game::CoreData::entityManager, *Game::CoreData::sceneManager, &timer_handler);
}
