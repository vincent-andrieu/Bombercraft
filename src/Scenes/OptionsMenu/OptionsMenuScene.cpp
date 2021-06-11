/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** OptionsMenuScene
*/

#include "OptionsMenuScene.hpp"

using namespace Game;

OptionsMenuScene::OptionsMenuScene(Engine::SystemManager &systemManager)
    : Engine::AbstractScene(systemManager, *CoreData::entityManager)
{
}

static const raylib::MyVector2 buttonSize = {
    raylib::MyVector2(570, 55)
};

void OptionsMenuScene::open()
{
    auto scene = CoreData::sceneManager->getCurrentScene();

    auto background = scene->localEntities.createEntity("backgroud");

    /*
        const string &path, const MyVector2 size = {-1, -1}, const MyVector2 position = {0, 0},
            const RColor color = RColor::RWHITE
    */
    GUI::ImageFactory::create(scene->localEntities, raylib::MyVector2(0, 0), raylib::MyVector2(1280, 720), "./Asset/Texture/dirt_32_32.png", false);

    // CoreData::entityManager->addComponent<Component::Render2D>(background,
    //     Component::render2dMapModels(
    //         {
    //             {"texture1", std::make_shared<raylib::Texture>("./Asset/Texture/dirt_32_32.png", raylib::MyVector2(1280, 720))}
    //         }
    //     )
    // );

    auto b1 = scene->localEntities.createEntity("b1");
    CoreData::entityManager->addComponent<Component::Render2D>(b1,
        Component::render2dMapModels(
            {{"texture1", std::make_shared<raylib::Texture>("Asset/Interface/Button.png", buttonSize, raylib::MyVector2(50, 150), raylib::RColor::RGRAY)}
    }));

    auto b2 = scene->localEntities.createEntity("b2");
    CoreData::entityManager->addComponent<Component::Render2D>(b2,
        Component::render2dMapModels(
            {
                {"rectangle", std::make_shared<raylib::Rectangle>(raylib::MyVector2(650, 150), buttonSize, raylib::RColor::RGRAY)}
            }
        )
    );

    auto b3 = scene->localEntities.createEntity("b3");
    CoreData::entityManager->addComponent<Component::Render2D>(b3,
        Component::render2dMapModels(
            {{"rectangle", std::make_shared<raylib::Rectangle>(raylib::MyVector2(50, 210), buttonSize, raylib::RColor::RGRAY)}
    }));


    auto done = scene->localEntities.createEntity("done");
    CoreData::entityManager->addComponent<Component::Render2D>(done,
        Component::render2dMapModels(
            {
                {"rectangle", std::make_shared<raylib::Rectangle>(raylib::MyVector2(310, 660), raylib::MyVector2(600, 55), raylib::RColor::RGRAY)}
            }
        )
    );

}

void Game::OptionsMenuScene::update()
{
    auto &render2D = this->_systemManager.getSystem<System::Render2DSystem>();

    render2D.update();
    this->eventDispatcher(this->_systemManager);
}