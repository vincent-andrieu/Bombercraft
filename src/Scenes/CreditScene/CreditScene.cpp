/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** CreditScene
*/

#include "CreditScene.hpp"
#include "Utilities/ProportionUtilities.hpp"

using namespace Game;

CreditScene::CreditScene(Engine::SystemManager &systemManager) : Engine::AbstractScene(systemManager, *CoreData::entityManager)
{
}

void CreditScene::CreditScene::open()
{
    const auto &windowSize(Game::CoreData::settings->getMyVector2("WIN_SIZE"));
    ProportionUtilities my_utility(windowSize);
    const size_t fontSize = (size_t) CoreData::settings->getInt("STANDARD_FONT_SIZE");
    raylib::MyVector2 logoSize(my_utility.getProportion({70, 25}));
    raylib::MyVector2 textPosition = my_utility.getProportion({50, 95});
    raylib::MyVector2 logoPosition = my_utility.getProportion({50, 75}, logoSize, {50, 50});
    float height = 0;
    const std::vector<std::string> creditText = CoreData::settings->getTabString("CREDIT_SCENE");
    GUI::LabelConfig conf = GUI::LabelFactory::getStandardLabelConfig(fontSize);

    GUI::ImageFactory::create(
        this->localEntities, raylib::MyVector2(0, 0), windowSize, CoreData::settings->getString("STANDARD_BACKGROUND"), false);
    const Engine::Entity &logo = GUI::ImageFactory::create(
        this->localEntities, logoPosition, logoSize, Game::CoreData::settings->getString("BOMBERCRAFT_LOGO"), true, "logo");
    // MOVING LOGO
    CoreData::entityManager->addComponent<Engine::Timer>(logo,
        0.01,
        *CoreData::entityManager,
        *CoreData::sceneManager,
        [](Engine::EntityManager &, Engine::SceneManager &, const Engine::Entity entity) {
            raylib::Texture *pictureBg = static_cast<raylib::Texture *>(
                Game::CoreData::entityManager->getComponent<Component::Render2D>(entity).get("image").get());
            raylib::MyVector2 bgPos = pictureBg->getPosition() + raylib::MyVector2(0, -1);

            const float mouseWheel = CoreData::eventManager->getMouseWheel();
            if (mouseWheel == 1)
                bgPos = bgPos + raylib::MyVector2(0, -20);
            else if (mouseWheel == -1)
                bgPos = bgPos + raylib::MyVector2(0, 10);
            pictureBg->setPosition(bgPos);
        });
    const raylib::MyVector2 textShift = ProportionUtilities::getProportionWin(windowSize, raylib::MyVector2(7, 7));
    // CREDITS TEXT CONTENT
    for (const auto &line : creditText) {
        const Engine::Entity &txt = GUI::LabelFactory::createCentered(
            this->localEntities, raylib::MyVector2(textPosition.a, textPosition.b + height), my_utility(60, 5), line, conf);
        CoreData::entityManager->addComponent<Engine::Timer>(txt,
            0.01,
            *CoreData::entityManager,
            *CoreData::sceneManager,
            [creditText, line](Engine::EntityManager &, Engine::SceneManager &, const Engine::Entity entity) {
                raylib::Text *text = static_cast<raylib::Text *>(
                    Game::CoreData::entityManager->getComponent<Component::Render2D>(entity).get("text").get());
                raylib::MyVector2 textPos = text->getPosition() + raylib::MyVector2(0, -1);

                const float mouseWheel = CoreData::eventManager->getMouseWheel();
                if (mouseWheel == 1)
                    textPos = textPos + raylib::MyVector2(0, -20);
                else if (mouseWheel == -1)
                    textPos = textPos + raylib::MyVector2(0, 10);
                text->setPosition(textPos);
                if (line == creditText.back() && textPos.b + text->getSize().b < 0)
                    CoreData::sceneManager->setScene<MainMenuScene>();
            });
        height += textShift.b;
    }
    //    KEYS
    std::unordered_map<raylib::KeyBoard, Component::eventScript> my_keyTriggers;
    my_keyTriggers.emplace(std::make_pair(raylib::KeyBoard::IKEY_ESCAPE, [](Engine::Entity) {
        CoreData::sceneManager->setScene<MainMenuScene>();
    }));
    Game::KeyManagementFactory::create(this->localEntities, my_keyTriggers);
}

void Game::CreditScene::update()
{
    auto &render2D = this->_systemManager.getSystem<System::Render2DSystem>();
    auto &timer = this->_systemManager.getSystem<Engine::TimerSystem>();

    render2D.update();
    timer.update();
    this->eventDispatcher(this->_systemManager);
}