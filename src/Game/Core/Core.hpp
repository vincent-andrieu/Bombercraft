/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 02/06/2021 Core.hpp.h
*/

#ifndef CORE_HPP
#define CORE_HPP

#include "Game/CoreData/CoreData.hpp"

#include "raylib.hpp"
#include "GameEngine.hpp"

#include "Components/Hitbox/Hitbox.hpp"
#include "Systems/Render2D/Render2DSystem.hpp"
#include "Systems/Render3D/Render3DSystem.hpp"
#include "Systems/Hitbox/HitboxSystem.hpp"
#include "Systems/Event/EventSystem.hpp"
#include "Systems/Physics/PhysicsSystem.hpp"

#include "Scenes/DebugScene/DebugScene.hpp"

#include "Components/KeyBox.hpp"
#include "Components/ClickEvent.hpp"
#include "Components/KeyEvent.hpp"
#include "Components/FocusEvent/ClickFocusEvent.hpp"
#include "Components/TextInputConfig/TextInputConfig.hpp"
#include "Components/MouseMoveEvent.hpp"
#include "Components/Hitbox/Hitbox.hpp"

namespace Game
{
    class Core : public CoreData {
      public:
        Core();
        ~Core() = default;

        void loop();

      public:
        Engine::EntityPack globalEntities;
    };
} // namespace Game

#endif // CORE_HPP
