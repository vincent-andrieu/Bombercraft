/*
 * EPITECH PROJECT, 2021
 * PlayerConfig
 * File description:
 * PlayerConfig.hpp - Created: 11/06/2021
 */

#ifndef PLAYER_CONFIG_COMPONENT_HPP
#define PLAYER_CONFIG_COMPONENT_HPP

#include "GameEngine.hpp"
#include "Game/CoreData/CoreData.hpp"

namespace Component
{
    struct PlayerKeyBindings {
        raylib::KeyBoard moveUp;
        raylib::KeyBoard moveDown;
        raylib::KeyBoard moveLeft;
        raylib::KeyBoard moveRight;
        raylib::KeyBoard pause;
        raylib::KeyBoard placeBomb;
    };

    class PlayerConfig : public Engine::Component<PlayerConfig> {
      public:
        PlayerConfig(const uint playerId, PlayerKeyBindings defaultKeyBinding);
        virtual ~PlayerConfig() = default;

        PlayerConfig &operator=(const PlayerConfig &src);

        const uint &getPlayerId() const;
        const PlayerKeyBindings &getPlayerKeyBindings() const;
        const PlayerKeyBindings &getPlayerDefaultKeyBindings() const;
        void resetAllKeyBindings();
        void setKeyMoveUp(const raylib::KeyBoard &key);
        void setKeyMoveDown(const raylib::KeyBoard &key);
        void setKeyMoveLeft(const raylib::KeyBoard &key);
        void setKeyMoveRight(const raylib::KeyBoard &key);
        void setKeyPause(const raylib::KeyBoard &key);
        void setKeyPlaceBomb(const raylib::KeyBoard &key);

      private:
        uint _id;
        PlayerKeyBindings _keyBindings;
        PlayerKeyBindings _defaultKeyBinding;
    };
} // namespace Component

#endif // CHRONO_HPP
