/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** IABomberman
*/

#ifndef IABOMBERMAN_HPP
#define IABOMBERMAN_HPP

#include <iostream>
#include "IACore.hpp"
#include "../../ConfigFile/IConfigFile.hpp"

namespace GameModule
{
    enum class BombermanAction
    {
        ACTION_NONE = 0,
        ACTION_TRIGGER_BOMBE,
    };

    class IABomberman : public IA::IACore<TileType, BombermanAction>
    {
        public:
            IABomberman(std::pair<size_t, size_t> pos, std::vector<std::vector<TileType>> env, std::unique_ptr<IConfigFile> &configFile);
            IABomberman(std::pair<size_t, size_t> pos, std::vector<std::vector<TileType>> env, size_t range = 6, int defaultValue = -1);
            ~IABomberman();
            void setRange(size_t range);
            IA::Movement getIAMovement();
            void setEnemyPos(std::vector<std::pair<size_t, size_t>> enemy);
        
        private:
            // SETTINGS
                void IASettings();

            // To set in IACore
            bool actionPutBomber(std::pair<size_t, size_t> pos, std::vector<std::vector<TileType>> env);
            void movementPrediction(std::pair<size_t, size_t> pos, std::vector<std::vector<TileType>> env, std::queue<IA::Movement> &list);

            // Internal function
            bool findSecurePlace(std::pair<size_t, size_t> pos, std::vector<std::vector<TileType>> env, std::queue<IA::Movement> &list);
            std::vector<std::vector<TileType>> getMapWithExposionEffect(std::vector<std::vector<TileType>> env, const std::pair<size_t, size_t> &pos, size_t range) const;
            void randomMove(const std::pair<size_t, size_t> &pos, const std::vector<std::vector<TileType>> &env, std::queue<IA::Movement> &list);
            void offensiveMove(const std::pair<size_t, size_t> &pos, const std::vector<std::vector<TileType>> &env, std::queue<IA::Movement> &list);
            bool isRandomMove() const;

            // TOOLS
            bool isRunnable(TileType type) const;
            bool isSecurePlace(TileType type) const;
            void clearQueue(std::queue<IA::Movement> &list);
            void loadPath(const std::vector<std::vector<int>> &tab, std::pair<size_t, size_t> end, std::queue<IA::Movement> &list) const;
            std::vector<std::vector<int>> getCostArray(const std::pair<size_t, size_t> &pos, const std::vector<std::vector<TileType>> &env) const;
            std::pair<size_t, size_t> getCostLessSafeMove(const std::vector<std::vector<int>> &tab, const std::vector<std::vector<TileType>> &env, bool &stat) const;
        
        private:
            size_t _range;
            int _defaultValue;
            size_t _randomMove;
            size_t _randomBombe;
    };
}

#endif