/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 14/06/2021 CharacterFactory.cpp.cc
*/

#include "CharacterFactory.hpp"
#include "Game/CoreData/CoreData.hpp"
#include "EntityType.hpp"
#include "Components/Hitbox/Hitbox.hpp"
#include "Systems/Audio/AudioSystem.hpp"
#include "Components/ModelList/ModelList.hpp"
#include "GUI/Factories/Inventory/InventoryFactory.hpp"

using namespace Game;

extern std::unique_ptr<Core> core;

static const std::unordered_map<Component::PlayerID, std::string> PLAYER_ID_TO_NAME({{Component::ALPHA, "TL_ALPHA"},
    {Component::BRAVO, "TR_BRAVO"},
    {Component::DELTA, "BL_DELTA"},
    {Component::CHARLIE, "BR_CHARLIE"}});

static void handlerHitbox(const Engine::Entity &character, const Engine::Entity &other)
{
    Component::Hitbox &hitbox = CoreData::entityManager->getComponent<Component::Hitbox>(other);
    Component::ModelList &render = CoreData::entityManager->getComponent<Component::ModelList>(character);
    Engine::Velocity &velocity = CoreData::entityManager->getComponent<Engine::Velocity>(character);
    const Component::PlayerInventory &inventory = CoreData::entityManager->getComponent<Component::PlayerInventory>(character);
    const Component::PlayerInventoryInfo &info = inventory.getPlayerInventoryInfo();
    const Component::PlayerID &id = inventory.getPlayerId();

    Game::EntityType type = hitbox.entityType;

    if (type == EntityType::BLAST) {
        if (CoreData::entityManager->hasComponent<Component::KeyEvent>(character)) {
            CoreData::entityManager->removeComponent<Component::KeyEvent>(character);
        } /* else if (CoreData::entityManager->hasComponent< AI Component >(character)) { // TODO
             CoreData::entityManager->removeComponent< AI Component >(character);
         }*/
        auto &audioSys = CoreData::systemManager->getSystem<System::AudioSystem>();
        audioSys.play("Death", core->globalEntities);
        /// Set Timer => remove entity
        CoreData::entityManager->addComponent<Engine::Timer>(character,
            CoreData::settings->getFloat("CHARACTER_DEATH_DURATION"),
            *CoreData::entityManager,
            *CoreData::sceneManager,
            [id](Engine::EntityManager &, Engine::SceneManager &sm, const Engine::Entity) {
                auto scene = sm.getCurrentScene();
                auto it_name = std::find_if(PLAYER_ID_TO_NAME.begin(), PLAYER_ID_TO_NAME.end(), [id](auto &pair) {
                    return pair.first == id;
                });
                if (it_name != PLAYER_ID_TO_NAME.end()) {
                    scene->localEntities.removeEntity(it_name->second);
                }
            });
        render.select("death"); /// Play animation => Death
    } else if (type == EntityType::POWERUP) {
        /// Note : bonus are given by the power-up collision handlers
    } else if (!(type == EntityType::SOFTBLOCK && info.wallPass == true)) {
        Component::Render3D &otherRender = CoreData::entityManager->getComponent<Component::Render3D>(other);
        raylib::MyVector3 otherPosition = otherRender.modele->getPosition();
        raylib::MyVector3 playerPosition = render.getPosition();
        raylib::MyVector3 delta = playerPosition - otherPosition;
        if ((delta.a > 0 && velocity.x < 0) || (delta.a < 0 && velocity.x > 0)) {
            velocity.x = 0;
            render.resetPosition(true, false);
        }
        if ((delta.c > 0 && velocity.y < 0) || (delta.c < 0 && velocity.y > 0)) {
            velocity.y = 0;
            render.resetPosition(false, true);
        }
    }
}

static void handlerKeyEvent(const Engine::Entity character)
{
    Component::ModelList &render = CoreData::entityManager->getComponent<Component::ModelList>(character);
    const Component::PlayerInventory &inventory = CoreData::entityManager->getComponent<Component::PlayerInventory>(character);
    Engine::Velocity &velocity = CoreData::entityManager->getComponent<Engine::Velocity>(character);
    const Component::PlayerInventoryInfo &info = inventory.getPlayerInventoryInfo();

    if (info.config != nullptr) {
        const Component::PlayerKeyBindings &keys = info.config->getPlayerKeyBindings();
        if (CoreData::eventManager->isKeyPressed(keys.moveUp)) {
            velocity.y = -info.speed;
        } else if (CoreData::eventManager->isKeyPressed(keys.moveDown)) {
            velocity.y = info.speed;
        } else if (CoreData::eventManager->isKeyReleased(keys.moveUp) || CoreData::eventManager->isKeyReleased(keys.moveDown)) {
            velocity.y = 0;
        }
        if (CoreData::eventManager->isKeyPressed(keys.moveLeft)) {
            velocity.x = -info.speed;
        } else if (CoreData::eventManager->isKeyPressed(keys.moveRight)) {
            velocity.x = info.speed;
        } else if (CoreData::eventManager->isKeyReleased(keys.moveLeft)
            || CoreData::eventManager->isKeyReleased(keys.moveRight)) {
            velocity.x = 0;
        }
        if (velocity.x || velocity.y) {
            render.select("walk");
        } else {
            render.select("idle");
        }
        // TODO : Drop bomb
        // render.select("setBomb");
    }
}

Engine::Entity Game::CharacterFactory::create(
    Engine::EntityPack &pack, Component::PlayerConfig &config, Component::Matrix2D &map, bool isAI)
{
    Engine::Entity entity;
    raylib::MyVector3 characterPos;
    Component::PlayerID id = config.getPlayerId();
    Component::PlayerInventoryInfo info = {(std::size_t) CoreData::settings->getInt("CHARACTER_INIT_BOMB"),
        (double) CoreData::settings->getFloat("CHARACTER_INIT_SPEED"),
        (bool) CoreData::settings->getInt("CHARACTER_INIT_WALLPASS"),
        (std::size_t) CoreData::settings->getInt("CHARACTER_INIT_BLAST_RAD")};
    auto it_name = std::find_if(PLAYER_ID_TO_NAME.begin(), PLAYER_ID_TO_NAME.end(), [id](auto &pair) {
        return pair.first == id;
    });

    if (it_name == PLAYER_ID_TO_NAME.end()) {
        throw std::invalid_argument("CharacterFactory::create Invalid player id.");
    }
    entity = pack.createEntity(it_name->second);
    characterPos = CharacterFactory::getPlayerPosition(id, map);
    /// Inventory
    const std::vector<std::string> texturesPath = CoreData::settings->getTabString("INVENTORY_TEXTURE");
    const raylib::MyVector2 windowSize(CoreData::settings->getMyVector2("WIN_SIZE"));
    raylib::MyVector2 inventoryPosition = CharacterFactory::getInventoryPosition(id);
    GUI::InventoryFactory::create(entity,
        inventoryPosition,
        {windowSize.a / 15, windowSize.a / 15},
        texturesPath,
        GUI::LabelFactory::getStandardLabelConfig(20),
        id,
        pack,
        config);
    /// Render3D
    const std::string &texturePath = config.getSkinPath();
    const std::string &modelPath = CoreData::settings->getString("CHARACTER_MODEL");
    std::cerr << "TEXTURE: " << texturePath << " Model: " << modelPath << std::endl;
    CoreData::entityManager->addComponent<Component::ModelList>(entity,
        Component::ModelListMap({{"idle", std::make_shared<raylib::Model>(texturePath, modelPath, characterPos)},
            {"death",
                std::make_shared<raylib::Animation>(
                    texturePath, CoreData::settings->getString("CHARA_ANIM_DEATH"), characterPos, raylib::RColor::RWHITE)},
            {"walk",
                std::make_shared<raylib::Animation>(
                    texturePath, CoreData::settings->getString("CHARA_ANIM_WALK"), characterPos, raylib::RColor::RWHITE, true)},
            {"setBomb",
                std::make_shared<raylib::Animation>(
                    texturePath, CoreData::settings->getString("CHARA_ANIM_SET_BOMB"), characterPos, raylib::RColor::RWHITE)}}),
        "idle");
    auto &modelList = CoreData::entityManager->getComponent<Component::ModelList>(entity);
    modelList.setScale(CoreData::settings->getFloat("CHARACTER_SCALE"));
    /// Inventory
    CoreData::entityManager->addComponent<Component::PlayerInventory>(entity, id, info, config);
    /// Hitbox
    const raylib::MyVector3 &hitboxSize = CoreData::settings->getMyVector3("HITBOX_SIZE");
    CoreData::entityManager->addComponent<Component::Hitbox>(
        entity, characterPos, hitboxSize, handlerHitbox, EntityType::CHARACTER);
    /// Velocity
    CoreData::entityManager->addComponent<Engine::Velocity>(entity, 0, 0);
    /// Specific
    if (isAI) {
        // TODO
    } else {
        return CharacterFactory::createPlayer(entity, config);
    }
    return entity;
}

/**
 * ALPHA    : TOP LEFT
 * BRAVO    : TOP RIGHT
 * CHARLIE  : BOTTOM LEFT
 * DELTA    : BOTTOM RIGHT
 */
raylib::MyVector3 Game::CharacterFactory::getPlayerPosition(Component::PlayerID id, Component::Matrix2D &map)
{
    raylib::MyVector2 mapSize = map.getMapSize();

    switch (id) {
        case Component::PlayerID::ALPHA: return Component::Matrix2D::getPositionAbs(1, 1);
        case Component::PlayerID::BRAVO: return Component::Matrix2D::getPositionAbs((size_t) (mapSize.a - 2), 1);
        case Component::PlayerID::DELTA: return Component::Matrix2D::getPositionAbs(1, (size_t) (mapSize.b - 2));
        case Component::PlayerID::CHARLIE:
            return Component::Matrix2D::getPositionAbs((size_t) (mapSize.a - 2), (size_t) (mapSize.b - 2));
        default: throw std::invalid_argument("CharacterFactory::getPlayerPosition Unknown PlayerID.");
    }
}

Engine::Entity CharacterFactory::createPlayer(Engine::Entity entity, Component::PlayerConfig &config)
{
    const Component::PlayerKeyBindings &keys = config.getPlayerKeyBindings();
    EventRequirement requirements(config.getPlayerKeyList(), {keys.moveRight, keys.moveLeft, keys.moveDown, keys.moveUp});

    CoreData::entityManager->addComponent<Component::KeyEvent>(entity, handlerKeyEvent, requirements);
    return entity;
}

raylib::MyVector2 CharacterFactory::getInventoryPosition(Component::PlayerID id)
{
    const raylib::MyVector2 windowSize(CoreData::settings->getMyVector2("WIN_SIZE"));
    switch (id) {
        case Component::PlayerID::ALPHA: return raylib::MyVector2(0, 0);
        case Component::PlayerID::BRAVO: return raylib::MyVector2(windowSize.a - (windowSize.a / 15) * 4, 0);
        case Component::PlayerID::DELTA: return raylib::MyVector2(0, windowSize.b - (windowSize.a / 15));
        case Component::PlayerID::CHARLIE:
            return raylib::MyVector2(windowSize.a - (windowSize.a / 15) * 4, windowSize.b - (windowSize.a / 15));
        default: throw std::invalid_argument("CharacterFactory::getPlayerPosition Unknown PlayerID.");
    }
}
