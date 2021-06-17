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
        explicit OptionComponent(float volume, const std::string &ressourcePack, size_t fov);
        virtual ~OptionComponent() = default;

        float volume{50};
        std::string ressourcePack;
        float fov{Game::CoreData::camera->getFovy()};

        size_t nbPlayers{1};
        size_t gameTimerDuration{120}; // 0 for unlimited time
        size_t mapSeed{42};            // Map factory
        size_t IASeed{42};
        size_t IARandomProb{42}; // difficulty / 100 (100 == minimum)
    };
} // namespace Component

#endif // OPTIONCOMPONENT_HPP