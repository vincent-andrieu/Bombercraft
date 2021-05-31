/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 27/05/2021 EntityManager.hpp.h
*/

#ifndef ENTITYMANAGER_HPP
#define ENTITYMANAGER_HPP

#include <memory>
#include "System/System.hpp"
#include "entity.hpp"
#include "IComponentContainer.hpp"
#include "EntityContainer/EntityRegister.hpp"
#include "System/System.hpp"
#include "ComponentContainer/ComponentContainer.hpp"
#include "Component/Component.hpp"

template <std::size_t ComponentCount, std::size_t SystemCount>
class System;

template <std::size_t ComponentCount, std::size_t SystemCount>
class EntityManager {
  public:
    EntityManager() = default;
    ~EntityManager() = default;

    template <typename T>
    void registerComponent()
    {
        this->template checkComponentType<T>();
        _componentContainers[T::type] = std::make_shared<ComponentContainer<T, ComponentCount, SystemCount>>(
            _entities.getEntityToBitset()
            );
    }

    template <typename T, typename ...Args>
    T *createSystem(Args&& ...args)
    {
        Index type = _systems.size();
        auto &system = _systems.emplace_back(std::make_shared<T>(std::forward<Args>(args)...));
        system->setUp(type);
        return static_cast<T*>(system.get());
    }

    void reserve(std::size_t size)
    {
        for (std::size_t i = 0; i < ComponentCount; i++) {
            if (_componentContainers[i]) {
                _componentContainers[i]->allocate(size);
            }
        }
        _entities.allocate(size);
    }

    Entity createEntity()
    {
        return _entities.create();
    }

    void removeEntity(Entity entity)
    {
        return _entities.remove(entity);
    }

    template <typename T>
    bool hasComponent(Entity entity)
    {
        this->checkComponentType<T>();
        return _entities.getBitset(entity)[T::type];
    }

    template <typename ...Ts>
    bool hasComponents(Entity entity)
    {
        (this->checkComponentTypes<Ts>(), ...);
        auto requirements = std::bitset<ComponentCount>();
        (requirements.set(Ts::type), ...);
        return (requirements & _entities.getBitset(entity)) == requirements;
    }

    template <typename T>
    T& getComponent(Entity entity)
    {
        this->checkComponentType<T>();
        return this->getComponentContainer<T>()->get(entity);
    }

    template <typename T>
    const T& getComponent(Entity entity)
    {
        this->checkComponentType<T>();
        return this->getComponentContainer<T>()->get(entity);
    }

    template <typename ...Ts>
    std::tuple<Ts&...> getComponents(Entity entity)
    {
        this->checkComponentTypes<Ts...>();
        return std::tie(this->getComponentContainer<Ts>()->get(entity)...);
    }

    template <typename T, typename ...Args>
    void addComponent(Entity entity, Args&&... args)
    {
        this->checkComponentType<T>();
        this->getComponentContainer<T>()->add(entity, std::forward<Args>(args)...);
        // Send message to system
        const auto &bitset = _entities.getBitset(entity);
        for (auto &system : _systems) {
            system->onEntityUpdated(entity, bitset);
        }
    }

    template <typename T>
    void removeComponent(Entity entity)
    {
        this->checkComponentType<T>();
        this->getComponentContainer<T>()->remove(entity);
        // Send message to systems
        const auto &bitset = _entities.getBitset(entity);
        for (auto &system : _systems) {
            system->onEntityUpdated(entity, bitset);
        }
    }

    template <typename T>
    Entity getOwner(const T& component) const
    {
        this->checkComponentType<T>();
        return this->getComponentContainer<T>()->getOwner(component);
    }

  private:
    std::array<std::shared_ptr<IComponentContainer>, ComponentCount> _componentContainers;
    EntityRegister _entities;
    std::vector<std::shared_ptr<System<ComponentCount, SystemCount>>> _systems;

    template <typename T>
    void checkComponentType() const
    {
        static_assert(std::is_base_of<Component<T>, T>::value, "Invalid component type");
    }

    template <typename ...Ts>
    void checkComponentTypes() const
    {
        (this->template checkComponentType<Ts>(), ...);
    }

    template <typename T>
    ComponentContainer<T, ComponentCount, SystemCount> * getComponentContainer()
    {
        return static_cast<ComponentContainer<T, ComponentCount, SystemCount> *>(_componentContainers[T::type].get());
    }

    template <typename T>
    ComponentContainer<T, ComponentCount, SystemCount> * getComponentContainer() const
    {
        return static_cast<ComponentContainer<T, ComponentCount, SystemCount> *>(_componentContainers[T::type].get());
    }
};

#endif // ENTITYMANAGER_HPP
