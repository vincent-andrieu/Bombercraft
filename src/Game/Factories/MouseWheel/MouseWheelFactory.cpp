/*
 * EPITECH PROJECT, 2021
 * MouseWheelFactory
 * File description:
 * MouseWheelFactory.cpp - Created: 17/06/2021
 */

#include "MouseWheelFactory.hpp"
#include "Components/KeyEvent.hpp"

using namespace Game;

void MouseWheelFactory::create(Engine::EntityPack &pack, MouseEventScript eventHandler)
{
    const Engine::Entity &entity = pack.createAnonymousEntity();

    CoreData::entityManager->addComponent<Component::KeyEvent>(
        entity,
        [eventHandler](const Engine::Entity) {
            const float &value = CoreData::eventManager->getMouseWheel();

            if (value != 0)
                eventHandler(value);
        },
        EventRequirement(true));
}