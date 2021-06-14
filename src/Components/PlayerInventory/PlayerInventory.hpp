/*
 * EPITECH PROJECT, 2021
 * PlayerInventory
 * File description:
 * PlayerInventory.hpp - Created: 11/06/2021
 */

#ifndef PLAYER_INVENTORY_HPP
#define PLAYER_INVENTORY_HPP

#include "GameEngine.hpp"
#include "Game/CoreData/CoreData.hpp"
#include "Components/PlayerConfig/PlayerConfig.hpp"

namespace Component
{
    struct PlayerInventoryInfo {
        size_t bomb;
        size_t speed;
        bool wallPass;
        size_t blastRadius;
    };

    class PlayerInventory : public Engine::Component<PlayerInventory> {
      public:
        PlayerInventory(const PlayerID playerId, PlayerInventoryInfo defaultInfo);
        virtual ~PlayerInventory() = default;

        PlayerInventory &operator=(const PlayerInventory &src);

        const PlayerID &getPlayerId() const;
        const PlayerInventoryInfo &getPlayerInventoryInfo() const;
        const PlayerInventoryInfo &getDefaultPlayerInventoryInfo() const;
        void resetAllInfo();
        void setBomb(const size_t &bomb);
        void setSpeed(const size_t &speed);
        void setWallPass(const bool &wallPass);
        void setBlastRadius(const size_t &blastRadius);

      private:
        PlayerID _id;
        PlayerInventoryInfo _info;
        PlayerInventoryInfo _defaultInfo;
    };
} // namespace Component

#endif // PLAYER_INVENTORY_HPP
