/*
** EPITECH PROJECT, 2021
** Indie Studio
** File description:
** XPBarFactory
*/

#ifndef XP_BAR_FACTORY_HPP
#define XP_BAR_FACTORY_HPP

#include "raylib.hpp"
#include <string>
#include "GameEngine.hpp"
#include "GUI/Factories/Label/LabelFactory.hpp"
#include "Components/PlayerInventory/PlayerInventory.hpp"
#include "Components/PlayerConfig/PlayerConfig.hpp"

namespace GUI
{
    using MyVector2 = raylib::MyVector2;

    class XPBarFactory {
      public:
        virtual ~XPBarFactory() = 0;

        static void create(const raylib::MyVector2 &position,
            const raylib::MyVector2 &size,
            std::vector<std::string> const &texturesPath,
            Component::PlayerID id,
            Engine::EntityPack &pack,
            Component::PlayerConfig &config,
            const std::string &name = "");

        static Component::PlayerInventoryInfo getDefaultPlayerInventory();
    };
} // namespace GUI

#endif // XP_BAR_FACTORY_HPP
