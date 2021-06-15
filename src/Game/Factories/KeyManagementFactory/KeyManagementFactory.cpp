/*
** EPITECH PROJECT, 2021
** KeyManagementFactory.cpp
** File description:
** Implementation of KeyManagementFactory that allows to easily create keyManager, in order to handle key events as an entity
*/

#include "KeyManagementFactory.hpp"
#include "Components/KeyEvent.hpp"

template <typename K, typename E> std::vector<K> unordered_mapToVector(const std::unordered_map<K, E> map)
{
    std::vector<K> my_vector;

    my_vector.reserve(map.size());
    for (const auto &key_element : map) {
        my_vector.emplace_back(key_element.first);
    }
    return my_vector;
}

void Game::keyManagementFactory::create(
    Engine::EntityPack &pack, const std::unordered_map<raylib::KeyBoard, Component::eventScript> keyTriggers)
{
    const auto my_entity(pack.createAnonymousEntity());
    std::vector<raylib::KeyBoard> my_keys(unordered_mapToVector(keyTriggers));
    Game::EventRequirement my_eventRequirements(my_keys, std::vector<raylib::KeyBoard>());

    auto my_eventHandler([keyTriggers](Engine::Entity entity) {
        Component::KeyEvent my_keyEvent(Game::CoreData::entityManager->getComponent<Component::KeyEvent>(entity));

        for (const auto &keyTrigger : keyTriggers) {
            if (keyTrigger.first != raylib::KeyBoard::IKEY_NULL && Game::CoreData::eventManager->isKeyPressed(keyTrigger.first))
                keyTrigger.second(entity);
        }
    });

    Game::CoreData::entityManager->addComponent<Component::KeyEvent>(my_entity, my_eventHandler, my_eventRequirements);
}