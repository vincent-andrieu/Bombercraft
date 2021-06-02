/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 31/05/2021 SystemManager.hpp.h
*/

#ifndef SYSTEMMANAGER_HPP
#define SYSTEMMANAGER_HPP

#include "entity.hpp"
#include <vector>
#include <memory>
#include <typeinfo>
#include <algorithm>
#include <exception>
#include <iostream>
#include <iterator>

namespace Engine
{
    class AbstractSystem;

    class SystemManager {
      public:
        SystemManager() = default;
        ~SystemManager() = default;

        template <typename T, typename... Args> T *createSystem(Args &&...args);

        void onEntityUpdated(Entity entity, const Signature &signature);

        template <typename T> T &getSystem();

      private:
        std::vector<std::unique_ptr<AbstractSystem>> _systems;
        std::vector<std::reference_wrapper<const std::type_info>> _types;
    };
}

#include "AbstractSystem/AbstractSystem.hpp"

namespace Engine {
    template <typename T, typename... Args>
    T *SystemManager::createSystem(Args &&...args)
    {
        const std::type_info &type = typeid(T);

        if (std::find_if(_types.begin(), _types.end(),
                [&type](auto &sysType) {
                    return sysType.get() == type;
                })
            != _types.end()) {
            throw std::exception();
        }
        auto &system = _systems.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));
        _types.emplace_back(typeid(T));
        return static_cast<T *>(system.get());
    }

    template <typename T>
    T &SystemManager::getSystem()
    {
        std::size_t index = 0;
        const std::type_info &type = typeid(T);
        auto type_it = std::find_if(_types.begin(), _types.end(), [&type](auto &sysType) {
            return sysType.get() == type;
        });

        if (type_it == _types.end()) {
            throw std::exception();
        }
        index = std::distance(_types.begin(), type_it);
        return *(static_cast<T *>(_systems[index].get()));
    }
} // namespace Engine

#endif // SYSTEMMANAGER_HPP