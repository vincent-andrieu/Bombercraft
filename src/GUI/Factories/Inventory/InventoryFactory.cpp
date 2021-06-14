/*
** EPITECH PROJECT, 2021
** Indie Studio
** File description:
** InventoryFactory
*/

#include "InventoryFactory.hpp"
#include "Game/CoreData/CoreData.hpp"
#include "Components/Render2D/Render2D.hpp"

static const std::vector<std::string> valueNames = {
    "InventoryValueBomb",
    "InventoryValueSpeed",
    "InventoryValueWallPass",
    "InventoryValueBlastRadius",
};

static void timer_handler([[maybe_unused]] Engine::EntityManager &entityManager,
    [[maybe_unused]] Engine::SceneManager &sceneManager,
    [[maybe_unused]] const Engine::Entity entity)
{
    try {
        Component::PlayerInventoryInfo playerInventoryInfo;
        std::shared_ptr<Engine::AbstractScene> scene = sceneManager.getCurrentScene();
        auto &playerInventory = entityManager.getComponent<Component::PlayerInventory>(entity);
        auto &bombValueRender2d = entityManager.getComponent<Component::Render2D>(
            scene->localEntities.getEntity(valueNames[0] + toString(playerInventory.getPlayerId())));
        auto &speedValueRender2d = entityManager.getComponent<Component::Render2D>(
            scene->localEntities.getEntity(valueNames[1] + toString(playerInventory.getPlayerId())));
        auto &wallPassValueRender2d = entityManager.getComponent<Component::Render2D>(
            scene->localEntities.getEntity(valueNames[2] + toString(playerInventory.getPlayerId())));
        auto &blastRadiusValueRender2d = entityManager.getComponent<Component::Render2D>(
            scene->localEntities.getEntity(valueNames[3] + toString(playerInventory.getPlayerId())));

        playerInventoryInfo = playerInventory.getPlayerInventoryInfo();
        (*dynamic_cast<raylib::IText *>(bombValueRender2d.get("text").get())).setText(toString(playerInventoryInfo.bomb));
        (*dynamic_cast<raylib::IText *>(speedValueRender2d.get("text").get())).setText(toString(playerInventoryInfo.speed));
        (*dynamic_cast<raylib::IText *>(wallPassValueRender2d.get("text").get())).setText(toString(playerInventoryInfo.wallPass));
        (*dynamic_cast<raylib::IText *>(blastRadiusValueRender2d.get("text").get()))
            .setText(toString(playerInventoryInfo.blastRadius));
    } catch (...) {
        std::cerr << "TimerEntity::Handler, An exception occurred" << std::endl;
    }
}

GUI::LabelConfig GUI::InventoryFactory::getStandardLabelConfig(const int fontSize)
{
    size_t finalFontSize = 0;

    if (fontSize == -1) {
        finalFontSize = Game::CoreData::settings->getInt("STANDARD_FONT_SIZE");
    } else {
        finalFontSize = fontSize;
    }
    GUI::LabelConfig myStandard{finalFontSize, raylib::RColor::RWHITE, Game::CoreData::settings->getString("STANDARD_FONT")};
    return myStandard;
}

Component::PlayerInventoryInfo GUI::InventoryFactory::getDefaultPlayerInventory()
{
    Component::PlayerInventoryInfo myDefault{1, 1, false, 1};
    return myDefault;
}

void GUI::InventoryFactory::create(Engine::EntityPack &entityPack,
    const raylib::MyVector2 &position,
    const raylib::MyVector2 &boxSize,
    std::vector<std::string> const &texturesPath,
    GUI::LabelConfig const &labelconfig,
    Component::PlayerID id,
    const std::string &name)
{
    Engine::Entity entity;
    raylib::MyVector2 boxPosition = position;
    raylib::MyVector2 itemPosition = {position.a + (boxSize.a / 10.0f), position.b + (boxSize.a / 10.0f)};
    raylib::MyVector2 itemSize = {boxSize.a * (4.0f / 5.0f), boxSize.b * (4.0f / 5.0f)};
    raylib::MyVector2 valuePosition = {position.a + boxSize.a * (75.0f / 100.0f), position.b + boxSize.a * (65.0f / 100.0f)};
    std::vector<std::shared_ptr<raylib::Texture>> cases = {};
    std::vector<std::shared_ptr<raylib::Texture>> powerUp = {};
    std::vector<size_t> defaultLabelValue = {1, 1, 0, 1};

    if (name.empty()) {
        entity = entityPack.createAnonymousEntity();
    } else {
        entity = entityPack.createEntity(name);
    }
    if (texturesPath.size() != 5)
        return;
    for (size_t i = 0; i < 4; i++) {
        cases.push_back(std::make_shared<raylib::Texture>(texturesPath[0], boxSize, boxPosition, raylib::RColor::RWHITE));
        powerUp.push_back(std::make_shared<raylib::Texture>(texturesPath[i + 1], itemSize, itemPosition, raylib::RColor::RWHITE));
        boxPosition.a += boxSize.a;
        itemPosition.a += boxSize.a;
    }
    Game::CoreData::entityManager->addComponent<Component::Render2D>(entity,
        Component::render2dMapModels{{"inventoryBlastRadius", powerUp[3]},
            {"inventoryBomb", powerUp[0]},
            {"inventorySpeed", powerUp[1]},
            {"inventoryWallPass", powerUp[2]},
            {"inventoryCase1", cases[0]},
            {"inventoryCase2", cases[1]},
            {"inventoryCase3", cases[2]},
            {"inventoryCase4", cases[3]}});
    for (size_t i = 0; i < 4; i++) {
        GUI::LabelFactory::create(entityPack, valuePosition, defaultLabelValue[i], labelconfig, valueNames[i] + toString(id));
        valuePosition.a += boxSize.a;
    }
    Game::CoreData::entityManager->addComponent<Component::PlayerInventory>(entity, id, getDefaultPlayerInventory());
    Game::CoreData::entityManager->addComponent<Engine::Timer>(
        entity, 1.0f, *Game::CoreData::entityManager, *Game::CoreData::sceneManager, &timer_handler);
}
