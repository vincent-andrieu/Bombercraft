/*
 * EPITECH PROJECT, 2021
 * Hitbox
 * File description:
 * Hitbox.hpp - Created: 03/06/2021
 */

#ifndef HITBOX_COMPONENT_HPP
#define HITBOX_COMPONENT_HPP

#include "GameEngine.hpp"
#include "raylib.hpp"

namespace Component
{
    using hitboxHandler =
        std::function<void(Engine::EntityManager &, Engine::SceneManager &, const Engine::Entity &, const Engine::Entity &)>;

    class Hitbox : public Engine::Component<Hitbox> {
      public:
        Hitbox(const MyVector3 origin, const MyVector3 size, hitboxHandler &handler, Engine::SceneManager &sceneManager);
        ~Hitbox() = default;

        void trigger(Engine::EntityManager &entityManager, const Engine::Entity &fromEntity, const Engine::Entity &toEntity);

        ObjectBox objectBox;

      private:
        hitboxHandler &_handler;
        Engine::SceneManager &_sceneManager;
    };
} // namespace Component

#endif