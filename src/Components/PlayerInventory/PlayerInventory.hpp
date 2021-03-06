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
        double speed;
        bool wallPass;
        size_t blastRadius;
        PlayerConfig *config;
    };

    class PlayerInventory : public Engine::Component<PlayerInventory> {
      public:
        PlayerInventory(const PlayerID playerId, PlayerInventoryInfo defaultInfo, PlayerConfig &config);
        virtual ~PlayerInventory() = default;

        PlayerInventory &operator=(const PlayerInventory &src);

        const PlayerID &getPlayerId() const;
        const PlayerInventoryInfo &getPlayerInventoryInfo() const;
        const PlayerInventoryInfo &getDefaultPlayerInventoryInfo() const;
        void resetAllInfo();
        void setBomb(const size_t &bomb);
        void setSpeed(double speed);
        void setWallPass(const bool &wallPass);
        void setBlastRadius(const size_t &blastRadius);

      private:
        PlayerID _id;
        PlayerInventoryInfo _info;
        PlayerInventoryInfo _defaultInfo;
    };
} // namespace Component

#endif // PLAYER_INVENTORY_HPP
