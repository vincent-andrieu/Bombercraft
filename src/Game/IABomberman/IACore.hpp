/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** IA
*/

#ifndef IA_HPP
#define IA_HPP

#include <ctime>
#include <queue>
#include "IIA.hpp"
#include "../../Exceptions/Exceptions.hpp"
#include "../ProceduralMap/IProceduralMap.hpp"

namespace GameModule
{
    enum class BombermanAction;
}

namespace IA
{
    template <typename TileType, typename Action>
    class IACore : public IIA<TileType, Action>
    {
        public:
            IACore(std::pair<size_t, size_t> _pos, std::vector<std::vector<TileType>> _env, unsigned int seed = std::time(nullptr));
            ~IACore();
            void setIAEnv(std::vector<std::vector<TileType>> env);
            std::vector<std::vector<TileType>> getIAEnv() const;
            void setIAPos(std::pair<size_t, size_t> pos);
            std::pair<size_t, size_t> getIAPos() const;
            void setRunnableTile(TileType tile);
            void unsetRunnableTile(TileType tile);
            Movement getIAMovement();
            Action getIAAction() const;
            void setIAAction(Action act, std::function<bool(std::vector<std::vector<TileType>> env, std::pair<size_t, size_t> pos)> func);
            void setIAMovement(std::function<void(std::vector<std::vector<TileType>> env, std::pair<size_t, size_t> pos, std::queue<IA::Movement> &list)> func);
            unsigned int getSeed() const;
            void setSeed(unsigned int seed);
            void setEnemyPos(std::vector<std::pair<size_t, size_t>> enemy);
        
        private:
            void applyIAMovement(Movement move);

        protected:
            std::pair<size_t, size_t> _pos;
            std::pair<size_t, size_t> _prevPos;
            std::vector<std::vector<TileType>> _env;
            std::vector<TileType> _isRunnable;
            std::queue<Movement> _MovementQueue;
            unsigned int _seed;
            std::vector<std::pair<size_t, size_t>> _enemyPos;

        private:
            std::unordered_map<Action, std::function<bool(std::vector<std::vector<TileType>>, std::pair<size_t, size_t>)>> _actLink;
            std::function<void(std::vector<std::vector<TileType>> env, std::pair<size_t, size_t> pos, std::queue<IA::Movement> &list)> _MovementFunc;
    };
}

#endif