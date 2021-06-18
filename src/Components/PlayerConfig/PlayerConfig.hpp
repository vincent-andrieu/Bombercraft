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
    enum PlayerID
    {
        ALPHA = 0,
        BRAVO = 1,
        CHARLIE = 2,
        DELTA = 3
    };

    enum PlayerStatus
    {
        DEAD = 0,
        ALIVE = 1
    };

    struct PlayerKeyBindings {
        raylib::KeyBoard moveUp;
        raylib::KeyBoard moveDown;
        raylib::KeyBoard moveLeft;
        raylib::KeyBoard moveRight;
        raylib::KeyBoard placeBomb;
    };

    class PlayerConfig : public Engine::Component<PlayerConfig> {
      public:
        PlayerConfig(const PlayerID playerId,
            PlayerKeyBindings defaultKeyBinding,
            const string &defaultSkinPath = Game::CoreData::settings->getString("STANDARD_SKIN_PATH"),
            const size_t &xp = 0);
        virtual ~PlayerConfig() = default;

        PlayerConfig &operator=(const PlayerConfig &src);

        const PlayerID &getPlayerId() const;
        const PlayerKeyBindings &getPlayerKeyBindings() const;
        [[nodiscard]] std::vector<raylib::KeyBoard> getPlayerKeyList() const;
        const PlayerKeyBindings &getPlayerDefaultKeyBindings() const;
        const string &getSkinPath() const;
        const size_t &getXP() const;
        const PlayerStatus &getStatus() const;

        void resetAllKeyBindings();
        void setKeyMoveUp(const raylib::KeyBoard &key);
        void setKeyMoveDown(const raylib::KeyBoard &key);
        void setKeyMoveLeft(const raylib::KeyBoard &key);
        void setKeyMoveRight(const raylib::KeyBoard &key);
        void setKeyPlaceBomb(const raylib::KeyBoard &key);
        void setSkinPath(const string &skinpath);
        void setXP(const size_t &xp);
        void setStatus(const PlayerStatus &status);

      private:
        PlayerID _id;
        PlayerKeyBindings _keyBindings;
        PlayerKeyBindings _defaultKeyBinding;
        string _skinPath;
        size_t _xp;
        PlayerStatus _status;
    };
} // namespace Component

#endif // CHRONO_HPP