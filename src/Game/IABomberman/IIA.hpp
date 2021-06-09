/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** IIA
*/

#ifndef IIA_HPP
#define IIA_HPP

#include <vector>
#include <functional>

namespace IA
{
    enum class Movement
    {
        IA_MOVE_UP,
        IA_MOVE_DOWN,
        IA_MOVE_LEFT,
        IA_MOVE_NONE,
        IA_MOVE_RIGHT,
    };

    template <typename TileType, typename Action>
    class IIA {
        public:
            virtual ~IIA() {};
            virtual void setIAEnv(std::vector<std::vector<TileType>> env) = 0;
            virtual std::vector<std::vector<TileType>> getIAEnv() const = 0;
            virtual void setIAPos(std::pair<size_t, size_t> pos) = 0;
            virtual std::pair<size_t, size_t> getIAPos() const = 0;
            virtual void setRunnableTile(TileType tile) = 0;
            virtual void unsetRunnableTile(TileType tile) = 0;
            virtual Movement getIAMovement() = 0;
            virtual Action getIAAction() const = 0;
            virtual void setIAAction(Action act, std::function<bool(std::vector<std::vector<TileType>> env, std::pair<size_t, size_t> pos)> func) = 0;
            virtual void setIAMovement(std::function<void(std::vector<std::vector<TileType>> env, std::pair<size_t, size_t> pos, std::queue<IA::Movement> &list)> func) = 0;
            virtual unsigned int getSeed() const = 0;
            virtual void setSeed(unsigned int seed) = 0;
            virtual void setEnemyPos(std::vector<std::pair<size_t, size_t>> enemy) = 0;
    };
}

#endif