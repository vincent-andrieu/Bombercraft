/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** TextInputFactory
*/

#include "TextInputFactory.hpp"

using namespace GUI;

const Game::EventRequirement clickFocusRequirement(Game::evtMouse::RIGHT | Game::evtMouse::LEFT);

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

const std::map<raylib::KeyBoard, std::string> _letterMap = {
    {raylib::KeyBoard::IKEY_A, std::string("a")},
    {raylib::KeyBoard::IKEY_B, std::string("b")},
    {raylib::KeyBoard::IKEY_C, std::string("c")},
    {raylib::KeyBoard::IKEY_D, std::string("d")},
    {raylib::KeyBoard::IKEY_E, std::string("e")},
    {raylib::KeyBoard::IKEY_F, std::string("f")},
    {raylib::KeyBoard::IKEY_G, std::string("g")},
    {raylib::KeyBoard::IKEY_H, std::string("h")},
    {raylib::KeyBoard::IKEY_I, std::string("i")},
    {raylib::KeyBoard::IKEY_J, std::string("j")},
    {raylib::KeyBoard::IKEY_K, std::string("k")},
    {raylib::KeyBoard::IKEY_L, std::string("l")},
    {raylib::KeyBoard::IKEY_M, std::string("m")},
    {raylib::KeyBoard::IKEY_N, std::string("n")},
    {raylib::KeyBoard::IKEY_O, std::string("o")},
    {raylib::KeyBoard::IKEY_P, std::string("p")},
    {raylib::KeyBoard::IKEY_Q, std::string("q")},
    {raylib::KeyBoard::IKEY_R, std::string("r")},
    {raylib::KeyBoard::IKEY_S, std::string("s")},
    {raylib::KeyBoard::IKEY_T, std::string("t")},
    {raylib::KeyBoard::IKEY_U, std::string("u")},
    {raylib::KeyBoard::IKEY_V, std::string("v")},
    {raylib::KeyBoard::IKEY_W, std::string("w")},
    {raylib::KeyBoard::IKEY_X, std::string("x")},
    {raylib::KeyBoard::IKEY_Y, std::string("y")},
    {raylib::KeyBoard::IKEY_Z, std::string("z")},
    {raylib::KeyBoard::IKEY_SPACE, std::string(" ")},
};

static Component::eventScript inputHandler = [](const Engine::Entity &childEntity) {
    const bool focusState = Game::CoreData::entityManager->getComponent<Component::ClickFocusEvent>(childEntity).getFocus();
    const size_t maxChar = Game::CoreData::entityManager->getComponent<Component::TextInputConfig>(childEntity).getMaxChar();
    std::string stringActual;
    raylib::Text *textActual = dynamic_cast<raylib::Text *>(
        Game::CoreData::entityManager->getComponent<Component::Render2D>(childEntity).get("text").get());

    for (auto const& x : _letterMap) {
        if (focusState && Game::CoreData::eventManager->isKeyPressed(x.first)) {
            stringActual = textActual->getText();
            if (stringActual.length() < maxChar) {
                textActual->setText(stringActual + x.second);
            }
        }
    }
    if (focusState && Game::CoreData::eventManager->isKeyPressed(raylib::KeyBoard::IKEY_BACKSPACE)) {
        if (!textActual->getText().empty()) {
            std::string newText = textActual->getText();

            newText.pop_back();
            textActual->setText(newText);
        }
    }
};

static Component::eventScript focusHandler = [](const Engine::Entity entityChild) {

    raylib::Rectangle *rectActual = dynamic_cast<raylib::Rectangle *>(
        Game::CoreData::entityManager->getComponent<Component::Render2D>(entityChild).get("rectangle").get());

    if (Game::CoreData::eventManager->MouseIsOverClicked(rectActual->getPosition(), rectActual->getSize())) {
        Game::CoreData::entityManager->foreachComponent<Component::ClickFocusEvent>([](Component::ClickFocusEvent &focusEvent){
            focusEvent.changeFocus(false);
        });
        Game::CoreData::entityManager->getComponent<Component::ClickFocusEvent>(entityChild).changeFocus(true);
    }
};

void TextInputFactory::create(Engine::EntityPack &pack, TextInputDynConf const &dynConf, TextInputConfig const &textInput, LabelConfig const &label)
{
    Engine::Entity entity = pack.createEntity(dynConf.name);
    raylib::MyVector2 textPos = dynConf.position + textInput.textPositionOffset;
    raylib::MyVector2 inputPosition(dynConf.position.a + textInput.borderSize, dynConf.position.b + textInput.borderSize);
    raylib::MyVector2 inputSize(textInput.size.a - textInput.borderSize * 2, textInput.size.b - textInput.borderSize * 2);

    Game::CoreData::entityManager->addComponent<Component::Render2D>(entity,
        Component::render2dMapModels({
            {"text", std::make_shared<raylib::Text>(dynConf.placeholder, textPos, label.fontSize, label.fontColor, label.fontPath)},
            {"rectangle", std::make_shared<raylib::Rectangle>(inputPosition, inputSize, textInput.color)},
            {"border", std::make_shared<raylib::Rectangle>(dynConf.position, textInput.size, textInput.borderColor)},
    }));
    Game::CoreData::entityManager->addComponent<Component::TextInputConfig>(entity, textInput.maxChar);
    Game::CoreData::entityManager->addComponent<Component::KeyEvent>(entity, inputHandler, inputHandlerRequireement);
    Game::CoreData::entityManager->addComponent<Component::ClickFocusEvent>(entity, focusHandler, clickFocusRequirement);
}

void TextInputFactory::create(Engine::EntityPack &pack, TextInputDynConf const &dynConf, LabelConfig const &label)
{
    TextInputConfig const &textInput = TextInputFactory::getStandardConfig();

    TextInputFactory::create(pack, dynConf, textInput, label);
}

TextInputConfig TextInputFactory::getStandardConfig()
{
    const TextInputConfig t = { .size = raylib::MyVector2(152, 27), .color = raylib::RColor::RBLACK,
                                .borderSize = 2, .borderColor = raylib::RColor::RGRAY, .maxChar = 16,
                                .textPositionOffset = raylib::MyVector2(5, 5)};
    return t;
}