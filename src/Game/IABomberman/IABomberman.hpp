/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** IABomberman
*/

#ifndef IABOMBERMAN_HPP
#define IABOMBERMAN_HPP

#include "IIA.hpp"
#include "../ProceduralMap/IProceduralMap.hpp"

namespace IA
{
    enum class BombermanAction
    {
        ACTION_NONE,
        ACTION_TRIGGER_BOMBE,
    };

    template <typename TileType, typename Action>
    class IABomberman : public IIA<TileType, Action>
    {
        public:
            IABomberman();
            ~IABomberman();
            void setIAEnv(std::vector<std::vector<TileType>> env);
            std::vector<std::vector<TileType>> getIAEnv() const;
            void setIAPos(std::pair<size_t, size_t> pos);
            std::pair<size_t, size_t> getIAPos() const;
            void setRunnableTile(TileType tile);
            void unsetRunnableTile(TileType tile);
            Movement getIAMovement() const;
            Action getIAAction() const;
            void setIAAction(Action act, std::function<bool(std::vector<std::vector<TileType>> env, std::pair<size_t, size_t> pos)> func);
    };
}

#endif