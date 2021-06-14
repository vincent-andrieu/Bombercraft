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
#include <memory>
#include "EntityType.hpp"
#include "../../../lib/raylibCpp/src/Data/MyVector/MyVector3.hpp"
#include "../../../include/EntityType.hpp"

using ObjectBox = raylib::ObjectBox;

namespace Component
{
    using hitboxHandler = std::function<void(const Engine::Entity &, const Engine::Entity &)>;

    class Hitbox : public Engine::Component<Hitbox> {
      public:
        Hitbox(const raylib::MyVector3 &origin, const raylib::MyVector3 &size, hitboxHandler handler, Game::EntityType type);
        virtual ~Hitbox() = default;

        void trigger(const Engine::Entity &fromEntity, const Engine::Entity &toEntity);

        // bool save(Engine::SaveManager &saver) const override;
        // bool load(Engine::SaveManager &saver) override;

        std::shared_ptr<ObjectBox> objectBox;
        Game::EntityType entityType;
        raylib::MyVector3 prevMovement;

      private:
        hitboxHandler _handler;
    };
} // namespace Component

#endif