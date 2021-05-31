/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 27/05/2021 EntityManager.hpp.h
*/

#ifndef ENTITYMANAGER_HPP
#define ENTITYMANAGER_HPP

#include <memory>
#include "SystemManager/SystemManager.hpp"
#include "entity.hpp"
#include "IComponentTypeRegister.hpp"
#include "EntityContainer/EntityRegister.hpp"
#include "ComponentTypeRegister/ComponentTypeRegister.hpp"
#include "Component/Component.hpp"

template <std::size_t ComponentCount>
class EntityManager {
  public:
    EntityManager(SystemManager &sysManager) : _systemManager(sysManager) {}
    ~EntityManager() = default;

    template <typename T>
    void registerComponent()
    {
        this->template checkComponentType<T>();
        _componentRegisters[T::type] = std::make_shared<ComponentTypeRegister<T>>(_entities.getEntitySignatures());
    }

    void allocate(std::size_t size)
    {
        for (std::size_t i = 0; i < ComponentCount; i++) {
            if (_componentRegisters[i]) {
                _componentRegisters[i]->allocate(size);
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
        return _entities.getSignature(entity)[T::type];
    }

    template <typename ...Ts>
    bool hasComponents(Entity entity)
    {
        (this->checkComponentTypes<Ts>(), ...);
        auto requirements = std::bitset<ComponentCount>();
        (requirements.set(Ts::type), ...);
        return (requirements & _entities.getSignature(entity)) == requirements;
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
        const Signature &signature = _entities.getSignature(entity);
        this->_systemManager.onEntityUpdated(entity, signature);
    }

    template <typename T>
    void removeComponent(Entity entity)
    {
        this->checkComponentType<T>();
        this->getComponentContainer<T>()->remove(entity);
        // Send message to systems
        const auto &signature = _entities.getSignature(entity);
        this->_systemManager.onEntityUpdated(entity, signature);
    }

    template <typename T>
    Entity getOwner(const T& component) const
    {
        this->checkComponentType<T>();
        return this->getComponentContainer<T>()->getOwner(component);
    }

  private:
    std::array<std::shared_ptr<IComponentTypeRegister>, ComponentCount> _componentRegisters;
    EntityRegister _entities;
    SystemManager &_systemManager;

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
    ComponentTypeRegister<T> * getComponentContainer()
    {
        return static_cast<ComponentTypeRegister<T> *>(_componentRegisters[T::type].get());
    }

    template <typename T>
    ComponentTypeRegister<T> * getComponentContainer() const
    {
        return static_cast<ComponentTypeRegister<T> *>(_componentRegisters[T::type].get());
    }
};

#endif // ENTITYMANAGER_HPP
