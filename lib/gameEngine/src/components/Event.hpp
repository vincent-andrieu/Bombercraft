/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 02/06/2021 Event.hpp.h
*/

#ifndef EVENT_HPP
#define EVENT_HPP

#include "Component/Component.hpp"
#include "EntityManager/EntityManager.hpp"
#include "SceneManager/SceneManager.hpp"

namespace Engine
{
    /**
 * EventComponent
 * @tparam T data - Object that describe the current event
     */
    template <typename T> class Event : public Component<Event<T>> {
      public:
        Event(std::function<void(const T &, EntityManager &, SceneManager &)> &handler) : handler(handler)
        {
        }
        ~Event() = default;

        std::function<void(const T &, EntityManager &, SceneManager &)> &handler;
    };
}

#endif // EVENT_HPP
