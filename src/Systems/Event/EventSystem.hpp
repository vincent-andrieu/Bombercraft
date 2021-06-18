/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 03/06/2021 EventSystem.hpp.h
*/

#ifndef EVENTSYSTEM_HPP
#define EVENTSYSTEM_HPP

#include "GameEngine.hpp"
#include "Components/ClickEvent/ClickEvent.hpp"
#include "Components/FocusEvent/ClickFocusEvent.hpp"
#include "Components/KeyEvent.hpp"
#include "Components/MouseMoveEvent/MouseMoveEvent.hpp"
#include "Game/CoreData/CoreData.hpp"

namespace System
{
    template <typename T> class EventSystem : public Engine::AbstractSystem {
      public:
        EventSystem() : AbstractSystem(*Game::CoreData::entityManager)
        {
            this->setRequirements<T>();
        }
        ~EventSystem() = default;

        void update()
        {
            for (const Engine::Entity &entity : this->getManagedEntities()) {
                try {
                    auto [event] = Game::CoreData::entityManager->getComponents<T>(entity);

                    event.trigger(entity);
                } catch (std::invalid_argument const &) {
                    this->onEntityRemoved(entity);
                    std::cerr << "Warning: EventSystem::update invalid entity components. Unregister entity." << std::endl;
                }
            }
        }
    };

    using ClickEventSystem = EventSystem<Component::ClickEvent>;
    using ClickFocusSystem = EventSystem<Component::ClickFocusEvent>;
    using KeyEventSystem = EventSystem<Component::KeyEvent>;
    using MouseEventSystem = EventSystem<Component::MouseMoveEvent>;
} // namespace System

#endif // EVENTSYSTEM_HPP