/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 03/06/2021 EventSystem.hpp.h
*/

#ifndef EVENTSYSTEM_HPP
#define EVENTSYSTEM_HPP

#include "GameEngine.hpp"
#include "Components/ClickEvent.hpp"
#include "Components/KeyEvent.hpp"
#include "Components/MouseMoveEvent.hpp"

namespace System
{
    template <typename T>
    class EventSystem : public Engine::AbstractSystem {
      public:
        EventSystem(Engine::EntityManager &entityManager) : AbstractSystem(entityManager)
        {
            this->setRequirements<T>();
        }
        ~EventSystem() = default;

        void update(raylib::Input &eventManager)
        {
            for (const Engine::Entity &entity : this->getManagedEntities()) {
                auto [event] = _entityManager.getComponents<T>(entity);

                event.trigger(_entityManager, eventManager, entity);
            }
        }
    };

    using ClickEventSystem = EventSystem<Component::ClickEvent>;
    using KeyEventSystem = EventSystem<Component::KeyEvent>;
    using MouseEventSystem = EventSystem<Component::MouseMoveEvent>;
}

#endif // EVENTSYSTEM_HPP
