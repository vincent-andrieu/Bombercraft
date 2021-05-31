/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 31/05/2021 SystemManager.hpp.h
*/

#ifndef SYSTEMMANAGER_HPP
#define SYSTEMMANAGER_HPP

#include "AbstractSystem/AbstractSystem.hpp"
#include "entity.hpp"
#include <vector>
#include <memory>

class SystemManager {
  public:
    SystemManager() = default;
    ~SystemManager() = default;

    template <typename T, typename ...Args>
    T *createSystem(Args&& ...args);

    void onEntityUpdated(Entity entity, const Signature &signature);

    template <typename T>
    T &getSystem();

  private:
    std::vector<std::shared_ptr<AbstractSystem>> _systems;
};

template <typename T, typename... Args>
T *SystemManager::createSystem(Args &&...args)
{
    auto &system = _systems.emplace_back(std::make_shared<T>(std::forward<Args>(args)...));
    return static_cast<T*>(system.get());
}

template <typename T>
T &SystemManager::getSystem()
{
    return _systems[T::type];
}

#endif // SYSTEMMANAGER_HPP
