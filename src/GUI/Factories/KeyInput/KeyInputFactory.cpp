/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** KeyInputFactory
*/

#include "KeyInputFactory.hpp"

using namespace GUI;

static const Game::EventRequirement clickFocusRequirement(Game::CLK_RIGHT | Game::CLK_LEFT);

static const Game::EventRequirement inputHandlerRequireement(
    {
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
        raylib::KeyBoard::IKEY_ZERO,
        raylib::KeyBoard::IKEY_ONE,
        raylib::KeyBoard::IKEY_TWO,
        raylib::KeyBoard::IKEY_THREE,
        raylib::KeyBoard::IKEY_FOUR,
        raylib::KeyBoard::IKEY_FIVE,
        raylib::KeyBoard::IKEY_SIX,
        raylib::KeyBoard::IKEY_SEVEN,
        raylib::KeyBoard::IKEY_EIGHT,
        raylib::KeyBoard::IKEY_NINE,
        raylib::KeyBoard::IKEY_BACKSPACE,
        raylib::KeyBoard::IKEY_SPACE,
        raylib::KeyBoard::IKEY_UP,
        raylib::KeyBoard::IKEY_DOWN,
        raylib::KeyBoard::IKEY_RIGHT,
        raylib::KeyBoard::IKEY_LEFT,
        raylib::KeyBoard::IKEY_BACKSPACE,
        raylib::KeyBoard::IKEY_SPACE,
        raylib::KeyBoard::IKEY_ESCAPE,
        raylib::KeyBoard::IKEY_ENTER,
        raylib::KeyBoard::IKEY_TAB,
        raylib::KeyBoard::IKEY_INSERT,
        raylib::KeyBoard::IKEY_DELETE,
        raylib::KeyBoard::IKEY_PAGE_UP,
        raylib::KeyBoard::IKEY_PAGE_DOWN,
        raylib::KeyBoard::IKEY_HOME,
        raylib::KeyBoard::IKEY_END,
        raylib::KeyBoard::IKEY_CAPS_LOCK,
        raylib::KeyBoard::IKEY_SCROLL_LOCK,
        raylib::KeyBoard::IKEY_NUM_LOCK,
        raylib::KeyBoard::IKEY_PRINT_SCREEN,
        raylib::KeyBoard::IKEY_PAUSE,
        raylib::KeyBoard::IKEY_F1,
        raylib::KeyBoard::IKEY_F2,
        raylib::KeyBoard::IKEY_F3,
        raylib::KeyBoard::IKEY_F4,
        raylib::KeyBoard::IKEY_F5,
        raylib::KeyBoard::IKEY_F6,
        raylib::KeyBoard::IKEY_F7,
        raylib::KeyBoard::IKEY_F8,
        raylib::KeyBoard::IKEY_F9,
        raylib::KeyBoard::IKEY_F10,
        raylib::KeyBoard::IKEY_F11,
        raylib::KeyBoard::IKEY_F12,
        raylib::KeyBoard::IKEY_L_SHIFT,
        raylib::KeyBoard::IKEY_L_CTRL,
        raylib::KeyBoard::IKEY_L_ALT,
        raylib::KeyBoard::IKEY_L_SUPER,
        raylib::KeyBoard::IKEY_R_SHIFT,
        raylib::KeyBoard::IKEY_R_CTRL,
        raylib::KeyBoard::IKEY_R_ALT,
        raylib::KeyBoard::IKEY_R_SUPER,
        raylib::KeyBoard::IKEY_KP_0,
        raylib::KeyBoard::IKEY_KP_1,
        raylib::KeyBoard::IKEY_KP_2,
        raylib::KeyBoard::IKEY_KP_3,
        raylib::KeyBoard::IKEY_KP_4,
        raylib::KeyBoard::IKEY_KP_5,
        raylib::KeyBoard::IKEY_KP_6,
        raylib::KeyBoard::IKEY_KP_7,
        raylib::KeyBoard::IKEY_KP_8,
        raylib::KeyBoard::IKEY_KP_9,
        raylib::KeyBoard::IKEY_KP_DECIMAL,
        raylib::KeyBoard::IKEY_KP_DIVIDE,
        raylib::KeyBoard::IKEY_KP_MULTIPLY,
        raylib::KeyBoard::IKEY_KP_SUBTRACT,
        raylib::KeyBoard::IKEY_KP_ADD,
        raylib::KeyBoard::IKEY_KP_ENTER,
        raylib::KeyBoard::IKEY_KP_EQUAL,
    },
    {});

const std::map<raylib::KeyBoard, string> KeyInputFactory::keyToStr = {
    {raylib::KeyBoard::IKEY_NULL, ""},
    {raylib::KeyBoard::IKEY_A, "A"},
    {raylib::KeyBoard::IKEY_B, "B"},
    {raylib::KeyBoard::IKEY_C, "C"},
    {raylib::KeyBoard::IKEY_D, "D"},
    {raylib::KeyBoard::IKEY_E, "E"},
    {raylib::KeyBoard::IKEY_F, "F"},
    {raylib::KeyBoard::IKEY_G, "G"},
    {raylib::KeyBoard::IKEY_H, "H"},
    {raylib::KeyBoard::IKEY_I, "I"},
    {raylib::KeyBoard::IKEY_J, "J"},
    {raylib::KeyBoard::IKEY_K, "K"},
    {raylib::KeyBoard::IKEY_L, "L"},
    {raylib::KeyBoard::IKEY_M, "M"},
    {raylib::KeyBoard::IKEY_N, "N"},
    {raylib::KeyBoard::IKEY_O, "O"},
    {raylib::KeyBoard::IKEY_P, "P"},
    {raylib::KeyBoard::IKEY_Q, "Q"},
    {raylib::KeyBoard::IKEY_R, "R"},
    {raylib::KeyBoard::IKEY_S, "S"},
    {raylib::KeyBoard::IKEY_T, "T"},
    {raylib::KeyBoard::IKEY_U, "U"},
    {raylib::KeyBoard::IKEY_V, "V"},
    {raylib::KeyBoard::IKEY_W, "W"},
    {raylib::KeyBoard::IKEY_X, "X"},
    {raylib::KeyBoard::IKEY_Y, "Y"},
    {raylib::KeyBoard::IKEY_Z, "Z"},
    {raylib::KeyBoard::IKEY_ZERO, "0"},
    {raylib::KeyBoard::IKEY_ONE, "1"},
    {raylib::KeyBoard::IKEY_TWO, "2"},
    {raylib::KeyBoard::IKEY_THREE, "3"},
    {raylib::KeyBoard::IKEY_FOUR, "4"},
    {raylib::KeyBoard::IKEY_FIVE, "5"},
    {raylib::KeyBoard::IKEY_SIX, "6"},
    {raylib::KeyBoard::IKEY_SEVEN, "7"},
    {raylib::KeyBoard::IKEY_EIGHT, "8"},
    {raylib::KeyBoard::IKEY_NINE, "9"},
    {raylib::KeyBoard::IKEY_SPACE, "SPACE"},
    {raylib::KeyBoard::IKEY_UP, "KEY UP"},
    {raylib::KeyBoard::IKEY_DOWN, "KEY DOWN"},
    {raylib::KeyBoard::IKEY_RIGHT, "KEY RIGHT"},
    {raylib::KeyBoard::IKEY_LEFT, "KEY LEFT"},
    {raylib::KeyBoard::IKEY_BACKSPACE, "BACKSPACE"},
    {raylib::KeyBoard::IKEY_SPACE, "SPACE"},
    {raylib::KeyBoard::IKEY_ESCAPE, "ESCAPE"},
    {raylib::KeyBoard::IKEY_ENTER, "ENTER"},
    {raylib::KeyBoard::IKEY_TAB, "TAB"},
    {raylib::KeyBoard::IKEY_INSERT, "INSERT"},
    {raylib::KeyBoard::IKEY_DELETE, "DELETE"},
    {raylib::KeyBoard::IKEY_PAGE_UP, "PAGE UP"},
    {raylib::KeyBoard::IKEY_PAGE_DOWN, "PAGE DOWN"},
    {raylib::KeyBoard::IKEY_HOME, "HOME"},
    {raylib::KeyBoard::IKEY_END, "END"},
    {raylib::KeyBoard::IKEY_CAPS_LOCK, "CAPS LOCK"},
    {raylib::KeyBoard::IKEY_SCROLL_LOCK, "SCROLL LOCK"},
    {raylib::KeyBoard::IKEY_NUM_LOCK, "NUM LOCK"},
    {raylib::KeyBoard::IKEY_PRINT_SCREEN, "PRINT SCREEN"},
    {raylib::KeyBoard::IKEY_PAUSE, "PAUSE"},
    {raylib::KeyBoard::IKEY_F1, "F1"},
    {raylib::KeyBoard::IKEY_F2, "F2"},
    {raylib::KeyBoard::IKEY_F3, "F3"},
    {raylib::KeyBoard::IKEY_F4, "F4"},
    {raylib::KeyBoard::IKEY_F5, "F5"},
    {raylib::KeyBoard::IKEY_F6, "F6"},
    {raylib::KeyBoard::IKEY_F7, "F7"},
    {raylib::KeyBoard::IKEY_F8, "F8"},
    {raylib::KeyBoard::IKEY_F9, "F9"},
    {raylib::KeyBoard::IKEY_F10, "F10"},
    {raylib::KeyBoard::IKEY_F11, "F11"},
    {raylib::KeyBoard::IKEY_F12, "F12"},
    {raylib::KeyBoard::IKEY_L_SHIFT, "LEFT SHIFT"},
    {raylib::KeyBoard::IKEY_L_CTRL, "LEFT CTRL"},
    {raylib::KeyBoard::IKEY_L_ALT, "LEFT ALT"},
    {raylib::KeyBoard::IKEY_L_SUPER, "LEFT_SUPER"},
    {raylib::KeyBoard::IKEY_R_SHIFT, "RIGHT SHIFT"},
    {raylib::KeyBoard::IKEY_R_CTRL, "RIGHT CTRL"},
    {raylib::KeyBoard::IKEY_R_ALT, "RIGHT ALT"},
    {raylib::KeyBoard::IKEY_R_SUPER, "RIGHT SUPER"},
    {raylib::KeyBoard::IKEY_KP_0, "KP 0"},
    {raylib::KeyBoard::IKEY_KP_1, "KP 1"},
    {raylib::KeyBoard::IKEY_KP_2, "KP 2"},
    {raylib::KeyBoard::IKEY_KP_3, "KP 3"},
    {raylib::KeyBoard::IKEY_KP_4, "KP 4"},
    {raylib::KeyBoard::IKEY_KP_5, "KP 5"},
    {raylib::KeyBoard::IKEY_KP_6, "KP 6"},
    {raylib::KeyBoard::IKEY_KP_7, "KP 7"},
    {raylib::KeyBoard::IKEY_KP_8, "KP 8"},
    {raylib::KeyBoard::IKEY_KP_9, "KP 9"},
    {raylib::KeyBoard::IKEY_KP_DECIMAL, "KP DECIMAL"},
    {raylib::KeyBoard::IKEY_KP_DIVIDE, "KP DIVIDE"},
    {raylib::KeyBoard::IKEY_KP_MULTIPLY, "KP MULTIPLY"},
    {raylib::KeyBoard::IKEY_KP_SUBTRACT, "KP SUBTRACT"},
    {raylib::KeyBoard::IKEY_KP_ADD, "KP ADD"},
    {raylib::KeyBoard::IKEY_KP_ENTER, "KP ENTER"},
    {raylib::KeyBoard::IKEY_KP_EQUAL, "KP EQUAL"},
};

static Component::eventScript focusHandler = [](const Engine::Entity entityChild) {
    raylib::Rectangle *rectActual = dynamic_cast<raylib::Rectangle *>(
        Game::CoreData::entityManager->getComponent<Component::Render2D>(entityChild).get("rectangle").get());

    if (Game::CoreData::eventManager->MouseIsOverClicked(rectActual->getPosition(), rectActual->getSize())) {
        Game::CoreData::entityManager->foreachComponent<Component::ClickFocusEvent>([](Component::ClickFocusEvent &focusEvent) {
            focusEvent.changeFocus(false);
        });
        Game::CoreData::entityManager->getComponent<Component::ClickFocusEvent>(entityChild).changeFocus(true);
    }
};

void KeyInputFactory::create(Engine::EntityPack &pack,
    KeyInputDynConf const &dynConf,
    LabelConfig const &label,
    KeyInputConfig const &keyInput,
    const KeyInputEventScript keyInputHandler)
{
    Engine::Entity entity = pack.createEntity(dynConf.name);
    raylib::MyVector2 textPos = dynConf.position + keyInput.textPositionOffset;
    raylib::MyVector2 inputPosition(dynConf.position.a + keyInput.borderSize, dynConf.position.b + keyInput.borderSize);
    raylib::MyVector2 inputSize(keyInput.size.a - keyInput.borderSize * 2, keyInput.size.b - keyInput.borderSize * 2);

    Game::CoreData::entityManager->addComponent<Component::Render2D>(entity,
        Component::render2dMapModels({
            {"text",
                std::make_shared<raylib::Text>(
                    keyToStr.at(dynConf.key), label.fontPath, textPos, label.fontSize, label.fontColor)},
            {"rectangle", std::make_shared<raylib::Rectangle>(inputPosition, inputSize, keyInput.color)},
            {"border", std::make_shared<raylib::Rectangle>(dynConf.position, keyInput.size, keyInput.borderColor)},
        }));

    const Component::eventScript inputHandler = [keyInputHandler](const Engine::Entity &childEntity) {
        const bool focusState = Game::CoreData::entityManager->getComponent<Component::ClickFocusEvent>(childEntity).getFocus();
        Component::KeyBox &keyBox = Game::CoreData::entityManager->getComponent<Component::KeyBox>(childEntity);

        raylib::Text *textActual = dynamic_cast<raylib::Text *>(
            Game::CoreData::entityManager->getComponent<Component::Render2D>(childEntity).get("text").get());

        for (auto const &x : keyToStr) {
            if (focusState && x.first != raylib::KeyBoard::IKEY_NULL && Game::CoreData::eventManager->isKeyPressed(x.first)) {
                keyInputHandler(childEntity, x);
                textActual->setText(x.second);
                keyBox.key = x.first;
            }
        }
    };
    Game::CoreData::entityManager->addComponent<Component::KeyEvent>(entity, inputHandler, inputHandlerRequireement);
    Game::CoreData::entityManager->addComponent<Component::ClickFocusEvent>(entity, focusHandler, clickFocusRequirement);
    Game::CoreData::entityManager->addComponent<Component::KeyBox>(entity);
}

KeyInputConfig KeyInputFactory::getStandardConfig()
{
    const KeyInputConfig t = {
        raylib::MyVector2(152, 27), raylib::RColor::RBLACK, 2, raylib::RColor::RGRAY, raylib::MyVector2(5, 5)};
    return t;
}