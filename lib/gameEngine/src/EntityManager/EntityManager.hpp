/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 27/05/2021 EntityManager.hpp.h
*/

#ifndef ENTITYMANAGER_HPP
#define ENTITYMANAGER_HPP

#include <array>
#include <algorithm>
#include <memory>
#include <mutex>
#include "entity.hpp"
#include "IComponentTypeRegister.hpp"
#include "EntityContainer/EntityRegister.hpp"
#include "ComponentTypeRegister/ComponentTypeRegister.hpp"
#include "Component/Component.hpp"
#include "SaveManager/SaveManager.hpp"

namespace Engine
{
    class SystemManager;

    class EntityManager {
      public:
        explicit EntityManager(SystemManager &sysManager);
        ~EntityManager();

        template <typename T> void registerComponent();

        void allocate(std::size_t size);

        Entity createEntity();
        void removeEntity(Entity entity);

        SystemManager &getSystemManager() const;

        template <typename T> bool hasComponent(Entity entity) const;
        template <typename... Ts> bool hasComponents(Entity entity) const;

        template <typename T> T &getComponent(Entity entity) const;
        template <typename... Ts> std::tuple<Ts &...> getComponents(Entity entity) const;

        template <typename T, typename... Args> void addComponent(Entity entity, Args &&...args);

        template <typename T> void removeComponent(Entity entity);

        template <typename T> Entity getOwner(const T &component) const;

        void save(const std::string &saveName);
        void load(const std::string &saveName);

        template <typename T, class Function> void foreachComponent(Function fn) const;

      private:
        std::array<std::shared_ptr<IComponentTypeRegister>, MAX_COMPONENT> _componentRegisters;
        EntityRegister _entities;
        SystemManager &_systemManager;
        std::mutex _mutex;
        // SaveManager _saver{"Engine_Save"};

        template <typename T> void checkComponentType() const;
        template <typename... Ts> void checkComponentTypes() const;

        template <typename T> ComponentTypeRegister<T> *getComponentContainer() const;
    };
} // namespace Engine

#include "SystemManager/SystemManager.hpp"

namespace Engine
{
    template <typename T> void EntityManager::registerComponent()
    {
        std::lock_guard<std::mutex> lock_guard(this->_mutex);

        this->template checkComponentType<T>();
        _componentRegisters[T::type] = std::make_shared<ComponentTypeRegister<T>>(_entities.getEntitySignatures());
    }

    template <typename T> bool EntityManager::hasComponent(Entity entity) const
    {
        this->checkComponentType<T>();
        return _entities.getSignature(entity)[T::type];
    }

    template <typename... Ts> bool EntityManager::hasComponents(Entity entity) const
    {
        (this->checkComponentTypes<Ts>(), ...);
        auto requirements = Signature();
        (requirements.set(Ts::type), ...);
        return (requirements & _entities.getSignature(entity)) == requirements;
    }

    template <typename T> T &EntityManager::getComponent(Entity entity) const
    {
        this->checkComponentType<T>();
        return this->getComponentContainer<T>()->get(entity);
    }

    template <typename... Ts> std::tuple<Ts &...> EntityManager::getComponents(Entity entity) const
    {
        this->checkComponentTypes<Ts...>();
        return std::tie(this->getComponentContainer<Ts>()->get(entity)...);
    }

    template <typename T, typename... Args> void EntityManager::addComponent(Entity entity, Args &&...args)
    {
        std::lock_guard<std::mutex> lock_guard(this->_mutex);

        this->checkComponentType<T>();
        if (_componentRegisters[T::type] == nullptr) {
            throw std::invalid_argument("Invalid component type (not registered?)");
        }
        this->getComponentContainer<T>()->add(entity, std::forward<Args>(args)...);
        // Send message to system
        const Signature &signature = _entities.getSignature(entity);
        this->_systemManager.onEntityUpdated(entity, signature);
    }

    template <typename T> void EntityManager::removeComponent(Entity entity)
    {
        std::lock_guard<std::mutex> lock_guard(this->_mutex);

        this->checkComponentType<T>();
        this->getComponentContainer<T>()->remove(entity);
        // Send message to systems
        const auto &signature = _entities.getSignature(entity);
        this->_systemManager.onEntityUpdated(entity, signature);
    }

    template <typename T> Entity EntityManager::getOwner(const T &component) const
    {
        this->checkComponentType<T>();
        return this->getComponentContainer<T>()->getOwner(component);
    }

    template <typename T> void EntityManager::checkComponentType() const
    {
        static_assert(std::is_base_of<Component<T>, T>::value, "Invalid component type");
    }

    template <typename... Ts> void EntityManager::checkComponentTypes() const
    {
        (this->template checkComponentType<Ts>(), ...);
    }

    template <typename T> ComponentTypeRegister<T> *EntityManager::getComponentContainer() const
    {
        return static_cast<ComponentTypeRegister<T> *>(_componentRegisters[T::type].get());
    }

    template <typename T, class Function> void EntityManager::foreachComponent(Function fn) const
    {
        this->checkComponentType<T>();
        std::vector<T> &components = this->getComponentContainer<T>()->getComponents();

        std::for_each(components.begin(), components.end(), fn);
    }
} // namespace Engine

#endif // ENTITYMANAGER_HPP