/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** TextInputFactory
*/

#include "TextInputFactory.hpp"

using namespace GUI;
/*
const Game::EventRequirement inputHandlerRequireement(0, false, {
 raylib::KeyBoard::IKEY_A,
 raylib::KeyBoard::IKEY_B,
 raylib::KeyBoard::IKEY_C,
 raylib::KeyBoard::IKEY_D,
 raylib::KeyBoard::IKEY_E,
 raylib::KeyBoard::IKEY_F,
 raylib::KeyBoard::IKEY_G,
 raylib::KeyBoard::IKEY_H,
 raylib::KeyBoard::IKEY_I,
 raylib::KeyBoard::IKEY_J,
 raylib::KeyBoard::IKEY_K,
 raylib::KeyBoard::IKEY_L,
 raylib::KeyBoard::IKEY_M,
 raylib::KeyBoard::IKEY_N,
 raylib::KeyBoard::IKEY_O,
 raylib::KeyBoard::IKEY_P,
 raylib::KeyBoard::IKEY_Q,
 raylib::KeyBoard::IKEY_R,
 raylib::KeyBoard::IKEY_S,
 raylib::KeyBoard::IKEY_T,
 raylib::KeyBoard::IKEY_U,
 raylib::KeyBoard::IKEY_V,
 raylib::KeyBoard::IKEY_W,
 raylib::KeyBoard::IKEY_X,
 raylib::KeyBoard::IKEY_Y,
 raylib::KeyBoard::IKEY_Z,
 raylib::KeyBoard::IKEY_BACKSPACE,
 raylib::KeyBoard::IKEY_SPACE
 }
 );

static const Component::eventScript inputHandler = [](const Engine::Entity) {
    auto scene = Game::CoreData::sceneManager->getCurrentScene();
    auto text = scene->localEntities.getEntity("foo");

    static_cast<raylib::Text *>(CoreData::)
}
*/
void TextInputFactory::create(Engine::EntityPack &pack, TextInputConfig const &config)
{
    Engine::Entity entity = pack.createEntity("foo");

    Game::CoreData::entityManager->addComponent<Component::Render2D>(entity,
        Component::render2dMapModels({
            {"text", std::make_shared<raylib::Text>("placeholder", raylib::MyVector2(400, 10), 24, raylib::RColor::RGREEN, "")},
            {"rectTest", std::make_shared<raylib::Rectangle>(raylib::MyVector2(400, 10), raylib::MyVector2(150, 25), raylib::RColor::RBROWN)}
    }));
}

