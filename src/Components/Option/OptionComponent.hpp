/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 14/06/2021 OptionComponent.hpp
*/

#ifndef OPTIONCOMPONENT_HPP
#define OPTIONCOMPONENT_HPP

#include "GameEngine.hpp"
#include "Game/CoreData/CoreData.hpp"

namespace Component
{
    class OptionComponent : public Engine::Component<OptionComponent> {
      public:
        explicit OptionComponent(float volume, const string &ressourcePack, float fov);
        virtual ~OptionComponent() = default;

        float volume{50};
        string ressourcePack;
        float fov{Game::CoreData::camera->getFovy()};

        size_t nbPlayers{1};
        size_t gameTimerDuration{120}; // 0 for unlimited time
        size_t seed{42};               // Map factory
        size_t IARandomProb{42};       // difficulty / 100 (100 == minimum)
    };
} // namespace Component

#endif // OPTIONCOMPONENT_HPP