/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** IABomberman
*/

#ifndef IABOMBERMAN_HPP
#define IABOMBERMAN_HPP

#include "IACore.hpp"

using namespace GameModule;

namespace GameModule
{
    enum class BombermanAction
    {
        ACTION_NONE,
        ACTION_TRIGGER_BOMBE,
    };

    class IABomberman : public IA::IACore<TileType, BombermanAction>
    {
        public:
            IABomberman(std::pair<size_t, size_t> pos, std::vector<std::vector<TileType>> env);
            ~IABomberman();
        
        private:
    };
}

#endif