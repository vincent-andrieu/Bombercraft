/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** Bomb
*/

#include "Game/Factories/Block/BlockFactory.hpp"
#include "BombFactory.hpp"
#include "Components/Matrix2D/Matrix2D.hpp"

using namespace GUI;

Engine::Entity BombFactory::create(Engine::EntityPack &entityPack, const raylib::MyVector3 position, Engine::Entity entityParent, const std::string &name)
{
    const raylib::MyVector3 &size = Game::CoreData::settings->getMyVector3("STANDARD_BLOCK_SIZE");
    std::shared_ptr<raylib::Animation> animation = BombFactory::getModel(position);

    Engine::Entity entity = (name.size()) ? entityPack.createEntity(name) : entityPack.createAnonymousEntity();
    int bombCountdown = Game::CoreData::settings->getInt("BOMB_COUNTDOWN");

    Game::CoreData::entityManager->addComponent<Engine::Position>(entity, position.a, position.b, position.c);
    Game::CoreData::entityManager->addComponent<Component::Render3D>(entity, animation);
    if (bombCountdown < 0)
        bombCountdown = 0;
    Game::CoreData::entityManager->addComponent<Component::Hitbox>(entity, position, size, BombFactory::handlerBombCollision, Game::EntityType::BOMB);
    Game::CoreData::entityManager->addComponent<Engine::Timer>(
        entity, bombCountdown, *Game::CoreData::entityManager, *Game::CoreData::sceneManager, BombFactory::handlerBombTimer);
    Game::CoreData::entityManager->addComponent<Engine::EntityBox>(entity, entityParent);
    return entity;
}

std::shared_ptr<raylib::Animation> BombFactory::getModel(const raylib::MyVector3 &pos)
{
    std::string animationPath = Game::CoreData::settings->getString("BOMB_ANIM");
    std::string typeInStr = "BOMB";
    std::string texturePath = Game::CoreData::settings->getString("BOMB_ANIM_TEXTURE");

    return std::make_shared<raylib::Animation>(texturePath, animationPath, pos, raylib::RColor::RWHITE);
}

void BombFactory::handlerBombCollision(const Engine::Entity &fromEntity, const Engine::Entity &toEntity)
{
    // TODO stop moving
    (void) fromEntity;
    (void) toEntity;
}

void BombFactory::handlerBombTimer(
    Engine::EntityManager &entityManager, Engine::SceneManager &sceneManager, const Engine::Entity &entity)
{
    auto scene = Game::Core::sceneManager->getCurrentScene();
    Engine::Position &pos = entityManager.getComponent<Engine::Position>(entity);
    Engine::EntityBox &player = entityManager.getComponent<Engine::EntityBox>(entity);
    Component::PlayerInventory &playerInventory = entityManager.getComponent<Component::PlayerInventory>(player.entity);
    const Component::PlayerInventoryInfo &inventoryInfo = playerInventory.getPlayerInventoryInfo();

    BlockFactory::blastPropagation(pos, sceneManager.getCurrentScene()->localEntities, inventoryInfo.blastRadius);
    scene->localEntities.removeEntity(entity);
}