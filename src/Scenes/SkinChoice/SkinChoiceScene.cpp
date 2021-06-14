/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 11/06/2021 SkinChoiceScene.cpp.cc
*/

#include "SkinChoiceScene.hpp"
#include "Game/CoreData/CoreData.hpp"
#include "Systems/Render2D/Render2DSystem.hpp"
#include "Systems/Render3D/Render3DSystem.hpp"
#include "raylib.hpp"
#include "GUI/Factories/Button/ButtonFactory.hpp"
#include "GUI/Factories/Image/ImageFactory.hpp"
#include "Components/Render3D/Render3D.hpp"
#include "Components/StringChoice/StringChoice.hpp"
#include "Utilities/ProportionUtilities.hpp"
#include "Scenes/OptionsMenu/OptionsMenuScene.hpp"

using namespace Game;

const std::vector<string> SKINS{
    "Asset/Skin/Basic_Test.png",
    "Asset/Skin/Bloody_White.png",
    "Asset/Skin/Deep_Blue.png",
    "Asset/Skin/Cyber_White.png",
    "Asset/Skin/Happy_White.png",
    "Asset/Skin/Lava_Orange.png",
    "Asset/Skin/Prince_Gold.png",
    "Asset/Skin/Pure_Green.png",
    "Asset/Skin/Rebel_Black.png",
    "Asset/Skin/Revenge_Red.png",
    "Asset/Skin/Simple_Steve.png",
};

static void previousHandler(Engine::Entity const)
{
    auto scene = CoreData::sceneManager->getCurrentScene();
    Engine::Entity model = scene->localEntities.getEntity("skin");
    Component::StringChoice &choice = CoreData::entityManager->getComponent<Component::StringChoice>(model);
    Component::Render3D &render = CoreData::entityManager->getComponent<Component::Render3D>(model);

    choice.prev();
    static_cast<raylib::Model *>(render.modele.get())->setTexture(choice.get());
}

static void nextHandler(Engine::Entity const)
{
    auto scene = CoreData::sceneManager->getCurrentScene();
    Engine::Entity model = scene->localEntities.getEntity("skin");
    Component::StringChoice &choice = CoreData::entityManager->getComponent<Component::StringChoice>(model);
    Component::Render3D &render = CoreData::entityManager->getComponent<Component::Render3D>(model);

    choice.next();
    static_cast<raylib::Model *>(render.modele.get())->setTexture(choice.get());
}

static void rotateHandler(Engine::EntityManager &em, Engine::SceneManager &, const Engine::Entity entity)
{
    Component::Render3D &render = em.getComponent<Component::Render3D>(entity);
    raylib::Model &model = *static_cast<raylib::Model *>(render.modele.get());

    raylib::MyVector3 rotation = model.getRotation();
    model.setRotation({rotation.a, rotation.b + 1, rotation.c});
}

static void applyHandler(Engine::Entity const)
{
    // TODO : apply change
    CoreData::sceneManager->setScene<OptionsMenuScene>();
}

Game::SkinChoiceScene::SkinChoiceScene()
    : Engine::AbstractScene(*CoreData::systemManager, *CoreData::entityManager), _selectedPlayer(nullptr)
{
}

void Game::SkinChoiceScene::open()
{
    const raylib::MyVector2 window_size(CoreData::settings->getMyVector2("WIN_SIZE"));
    ProportionUtilities my_utility(window_size);
    CoreData::moveCamera(raylib::MyVector3(12, 0, 0), raylib::MyVector3(0, 0, 0));
    string modelPath = CoreData::settings->getString("CHARACTER_MODEL");
    const GUI::ButtonConfig buttonConfig = GUI::ButtonFactory::getSmallButtonConfig();

    this->_selectedPlayer =
        &Game::CoreData::systemManager->getSystem<System::PlayerConfigSystem>().getPlayerFromID(Component::PlayerID::ALPHA);
    GUI::ImageFactory::create(this->localEntities, raylib::MyVector2(0, 0), window_size, "Asset/Background/skinchoice.png", true);
    GUI::ButtonFactory::create(this->localEntities,
        my_utility(44, 10),
        "changePlayer",
        buttonConfig,
        "Player " + toString(this->_selectedPlayer->getPlayerId()),
        [this](const Engine::Entity &entity) {
            // Change selected player
            this->_selectedPlayer =
                &Game::CoreData::systemManager->getSystem<System::PlayerConfigSystem>().getNextPlayer(*this->_selectedPlayer);

            // Change button label
            static_cast<raylib::Text *>(
                Game::CoreData::entityManager->getComponent<Component::Render2D>(entity).get("label").get())
                ->setText("Player " + toString(this->_selectedPlayer->getPlayerId()));

            // Change skin choice
            const Engine::Entity &model = CoreData::sceneManager->getCurrentScene()->localEntities.getEntity("skin");
            Component::StringChoice &choice = CoreData::entityManager->getComponent<Component::StringChoice>(model);
            choice.set(this->_selectedPlayer->getSkinPath());
            Component::Render3D &render = CoreData::entityManager->getComponent<Component::Render3D>(model);
            static_cast<raylib::Model *>(render.modele.get())->setTexture(this->_selectedPlayer->getSkinPath());
        });
    GUI::ButtonFactory::create(this->localEntities, my_utility(14, 84), "leftButton", buttonConfig, "PREV", previousHandler);
    GUI::ButtonFactory::create(this->localEntities, my_utility(74, 84), "rightButton", buttonConfig, "NEXT", nextHandler);
    GUI::ButtonFactory::create(this->localEntities, my_utility(44, 84), "applyButton", buttonConfig, "APPLY", applyHandler);
    Engine::Entity skin = this->localEntities.createEntity("skin");
    CoreData::entityManager->addComponent<Component::Render3D>(
        skin, std::make_shared<raylib::Model>(this->_selectedPlayer->getSkinPath(), modelPath, raylib::MyVector3(0, -4, 0)));
    CoreData::entityManager->addComponent<Component::StringChoice>(skin, std::vector<string>(SKINS));
    CoreData::entityManager->addComponent<Engine::Timer>(
        skin, 0.005f, *CoreData::entityManager, *CoreData::sceneManager, rotateHandler);
}

void Game::SkinChoiceScene::update()
{
    auto &render2D = this->_systemManager.getSystem<System::Render2DSystem>();
    auto &render3D = this->_systemManager.getSystem<System::Render3DSystem>();
    auto &timer = this->_systemManager.getSystem<Engine::TimerSystem>();

    render2D.update();
    render3D.update();
    timer.update();
    this->eventDispatcher(this->_systemManager);
}
