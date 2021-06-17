/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** AIComponent.hpp
*/

#include "Game/IABomberman/IABomberman.hpp"
#include "Components/Matrix2D/DataMatrix/DataMatrix.hpp"

#ifndef AICOMPONENT_HPP
#define AICOMPONENT_HPP

namespace Component
{
    class AIComponent : public Engine::Component<AIComponent>
    {
        public:
            AIComponent();
            virtual ~AIComponent() = default;

            std::pair<double, double> getVelocity();
            bool putBomb();
            void setEnv(const std::shared_ptr<DataMatrix> &map, std::pair<size_t, size_t> pos, std::vector<std::pair<size_t, size_t>> &enemy);
            raylib::MyVector3 getOrientation() const;

        private:
            static GameModule::MapType translateMatrix(const std::shared_ptr<DataMatrix> &map);

        private:
            std::shared_ptr<GameModule::IABomberman> _AI;
    };
}

#endif