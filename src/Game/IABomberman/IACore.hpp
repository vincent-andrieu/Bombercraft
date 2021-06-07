/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** IA
*/

#ifndef IA_HPP
#define IA_HPP

#include "IIA.hpp"
//#include "IABomberman.hpp"
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
            IACore(std::pair<size_t, size_t> _pos, std::vector<std::vector<TileType>> _env);
            ~IACore();
            void setIAEnv(std::vector<std::vector<TileType>> env);
            std::vector<std::vector<TileType>> getIAEnv() const;
            void setIAPos(std::pair<size_t, size_t> pos);
            std::pair<size_t, size_t> getIAPos() const;
            void setRunnableTile(TileType tile);
            void unsetRunnableTile(TileType tile);
            Movement getIAMovement() const;
            Action getIAAction() const;
            void setIAAction(Action act, std::function<bool(std::vector<std::vector<TileType>> env, std::pair<size_t, size_t> pos)> func);
            void setIAMovement(std::function<Movement(std::vector<std::vector<TileType>> env, std::pair<size_t, size_t> pos)> func);

        private:
            std::pair<size_t, size_t> _pos;
            std::vector<std::vector<TileType>> _env;
            std::unordered_map<Action, std::function<bool(std::vector<std::vector<TileType>>, std::pair<size_t, size_t>)>> _actLink;
            std::vector<TileType> _isRunnable;
            std::function<Movement(std::vector<std::vector<TileType>> env, std::pair<size_t, size_t> pos)> _MovementFunc;
    };
}

#endif