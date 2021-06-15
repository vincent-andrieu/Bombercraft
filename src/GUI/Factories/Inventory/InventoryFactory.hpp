/*
** EPITECH PROJECT, 2021
** Indie Studio
** File description:
** InventoryFactory
*/

#ifndef INVENTORY_FACTORY_HPP
#define INVENTORY_FACTORY_HPP

#include "raylib.hpp"
#include <string>
#include "GameEngine.hpp"
#include "GUI/Factories/Label/LabelFactory.hpp"
#include "Components/PlayerInventory/PlayerInventory.hpp"
#include "Components/PlayerConfig/PlayerConfig.hpp"

namespace GUI
{
    using MyVector2 = raylib::MyVector2;

    class InventoryFactory {
      public:
        virtual ~InventoryFactory() = 0;

        static void create(Engine::Entity entity,
            const raylib::MyVector2 &position,
            const raylib::MyVector2 &boxSize,
            std::vector<std::string> const &texturesPath,
            const GUI::LabelConfig &labelconfig,
            Component::PlayerID id,
            Engine::EntityPack &pack,
            Component::PlayerConfig &config);

        static Component::PlayerInventoryInfo getDefaultPlayerInventory();
    };
} // namespace GUI

#endif // INVENTORY_FACTORY_HPP
