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
#include "GUI/Factories/Label/LabelFactory.hpp"
#include "Components/PlayerInventory/PlayerInventory.hpp"

namespace GUI
{
    using MyVector2 = raylib::MyVector2;

    class InventoryFactory {
      public:
        virtual ~InventoryFactory() = 0;

        static void create(Engine::EntityPack &entityPack,
            const MyVector2 &position,
            const MyVector2 &boxSze,
            std::vector<std::string> const &texturesPath,
            GUI::LabelConfig const &labelconfig,
            Component::PlayerID id,
            std::string const &name = "");

        static GUI::LabelConfig getStandardLabelConfig(const int fontSize = -1);
        static Component::PlayerInventoryInfo getDefaultPlayerInventory();
    };
} // namespace GUI

#endif // INVENTORY_FACTORY_HPP
