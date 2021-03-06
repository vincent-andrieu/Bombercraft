/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** TextInputFactory
*/

#include "TextInputFactory.hpp"

using namespace GUI;

static const Game::EventRequirement clickFocusRequirement(Game::CLK_RIGHT | Game::CLK_LEFT);

static const Game::EventRequirement inputHandlerRequirement(
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
        raylib::KeyBoard::IKEY_BACKSPACE,
        raylib::KeyBoard::IKEY_SPACE,
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
    },
    {});

static const std::map<raylib::KeyBoard, std::string> _letterMap = {
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
    {raylib::KeyBoard::IKEY_ZERO, std::string("0")},
    {raylib::KeyBoard::IKEY_ONE, std::string("1")},
    {raylib::KeyBoard::IKEY_TWO, std::string("2")},
    {raylib::KeyBoard::IKEY_THREE, std::string("3")},
    {raylib::KeyBoard::IKEY_FOUR, std::string("4")},
    {raylib::KeyBoard::IKEY_FIVE, std::string("5")},
    {raylib::KeyBoard::IKEY_SIX, std::string("6")},
    {raylib::KeyBoard::IKEY_SEVEN, std::string("7")},
    {raylib::KeyBoard::IKEY_EIGHT, std::string("8")},
    {raylib::KeyBoard::IKEY_NINE, std::string("9")},
    {raylib::KeyBoard::IKEY_SPACE, std::string(" ")},
};

TextInputConfig TextInputFactory::getStandardConfig()
{
    const TextInputConfig t = {raylib::RColor::RBLACK, 2, raylib::RColor::RGRAY, 12, raylib::MyVector2(5, 5)};
    return t;
}

static Component::eventScript inputHandler = [](const Engine::Entity &childEntity) {
    const bool focusState = Game::CoreData::entityManager->getComponent<Component::ClickFocusEvent>(childEntity).getFocus();
    const size_t maxChar = Game::CoreData::entityManager->getComponent<Component::TextInputConfig>(childEntity).getMaxChar();
    std::string stringActual;
    raylib::Text *textActual =
        dynamic_cast<raylib::Text *>(Game::CoreData::entityManager->getComponent<Component::Render2D>(childEntity).get("text").get());

    if (!focusState)
        return;
    for (auto const &x : _letterMap) {
        if (Game::CoreData::eventManager->isKeyPressed(x.first)) {
            stringActual = textActual->getText();
            if (stringActual.length() < maxChar) {
                textActual->setText(stringActual + x.second);
            }
        }
    }
    if (Game::CoreData::eventManager->isKeyPressed(raylib::KeyBoard::IKEY_BACKSPACE)) {
        if (!textActual->getText().empty()) {
            std::string newText = textActual->getText();

            newText.pop_back();
            textActual->setText(newText);
        }
    }
};

static Component::eventScript focusHandler = [](const Engine::Entity &childEntity) {
    raylib::Texture *rectActual = static_cast<raylib::Texture *>(
        Game::CoreData::entityManager->getComponent<Component::Render2D>(childEntity).get("rectangle").get());

    if (Game::CoreData::eventManager->MouseIsOverClicked(rectActual->getPosition(), rectActual->getSize())) {
        Game::CoreData::entityManager->foreachComponent<Component::ClickFocusEvent>([](Component::ClickFocusEvent &focusEvent) {
            static_cast<raylib::Texture *>(
                Game::CoreData::entityManager->getComponent<Component::Render2D>(Game::CoreData::entityManager->getOwner(focusEvent))
                    .get("rectangle")
                    .get())
                ->setPath(Game::CoreData::settings->getString("STANDARD_UNAVAILABLE_BUTTON_TEXTURE"));
            focusEvent.changeFocus(false);
        });
        Game::CoreData::entityManager->getComponent<Component::ClickFocusEvent>(childEntity).changeFocus(true);
        rectActual->setPath(Game::CoreData::settings->getString("STANDARD_HOVER_BUTTON_TEXTURE"));
    } else {
        Game::CoreData::entityManager->getComponent<Component::ClickFocusEvent>(childEntity).changeFocus(false);
        rectActual->setPath(Game::CoreData::settings->getString("STANDARD_UNAVAILABLE_BUTTON_TEXTURE"));
    }
};

void TextInputFactory::create(Engine::EntityPack &pack,
    TextInputDynConf const &dynConf,
    TextInputConfig const &textInput,
    LabelConfig const &label,
    const bool centered)
{
    if (dynConf.name.empty()) {
        throw std::invalid_argument("TextInputFactory::create empty entity name");
    }
    Engine::Entity entity = pack.createEntity(dynConf.name);
    raylib::MyVector2 position(dynConf.position);
    if (centered) {
        position = position - ProportionUtilities::getProportionWin(dynConf.size, raylib::MyVector2(50, 50));
    }
    raylib::MyVector2 textPos = position + textInput.textPositionOffset;
    raylib::MyVector2 inputPosition(position.a + textInput.borderSize, position.b + textInput.borderSize);
    raylib::MyVector2 inputSize(dynConf.size.a - textInput.borderSize * 2, dynConf.size.b - textInput.borderSize * 2);
    auto textModel = std::make_shared<raylib::Text>(dynConf.placeholder, label.fontPath, textPos + 5, label.fontSize, label.fontColor);

    Game::CoreData::entityManager->addComponent<Component::Render2D>(entity,
        Component::render2dMapModels({
            {"border",
                std::make_shared<raylib::Texture>(Game::CoreData::settings->getString("STANDARD_HOVER_BUTTON_TEXTURE"),
                    dynConf.size,
                    position,
                    textInput.borderColor)},
            {"rectangle",
                std::make_shared<raylib::Texture>(
                    Game::CoreData::settings->getString("STANDARD_UNAVAILABLE_BUTTON_TEXTURE"), inputSize, inputPosition)},
            {"text", textModel},
        }));
    raylib::Text::setFontSize(*textModel, (dynConf.size.a < 20 && dynConf.size.b < 20) ? dynConf.size : dynConf.size - 20);
    Game::CoreData::entityManager->addComponent<Component::TextInputConfig>(entity, textInput.maxChar);
    Game::CoreData::entityManager->addComponent<Component::KeyEvent>(entity, inputHandler, inputHandlerRequirement);
    Game::CoreData::entityManager->addComponent<Component::ClickFocusEvent>(entity, focusHandler, clickFocusRequirement);
}

void TextInputFactory::create(Engine::EntityPack &pack, TextInputDynConf const &dynConf, LabelConfig const &label, const bool centered)
{
    TextInputConfig const &textInput = TextInputFactory::getStandardConfig();

    TextInputFactory::create(pack, dynConf, textInput, label, centered);
}