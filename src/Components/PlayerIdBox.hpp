/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 19/06/2021 PlayerIdbox.hpp.h
*/

#ifndef PLAYERIDBOX_HPP
#define PLAYERIDBOX_HPP

#include "GameEngine.hpp"
#include "Components/PlayerConfig/PlayerConfig.hpp"

namespace Component
{
    class PlayerIdBox : public Engine::Component<PlayerIdBox> {
      public:
        PlayerIdBox(PlayerID id) : id(id) {}
        virtual ~PlayerIdBox() = default;

        PlayerID id;
    };
}

#endif // PLAYERIDBOX_HPP
