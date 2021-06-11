/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** utilities
*/

#include "utilities.hpp"

using namespace GUI;

std::string getPromptContent(Engine::EntityPack &pack, std::string inputName)
{
    auto textInput = pack.getEntity(inputName);
    raylib::Text *textContent = static_cast<raylib::Text *>(Game::CoreData::entityManager->getComponent<Component::Render2D>(textInput).get("text").get());

    return textContent->getText();
}

raylib::KeyBoard getKeyInputContent(Engine::EntityPack &pack, std::string keyInputName)
{
    auto keyInput = pack.getEntity(keyInputName);

    Component::KeyBox &keyBox = Game::CoreData::entityManager->getComponent<Component::KeyBox>(keyInput);
    return keyBox.key;
}