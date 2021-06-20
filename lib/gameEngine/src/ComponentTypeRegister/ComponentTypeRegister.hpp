/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 27/05/2021 ComponentTypeRegister.hpp.h
*/

#ifndef COMPONENTTYPEREGISTER_HPP
#define COMPONENTTYPEREGISTER_HPP

#include "IComponentTypeRegister.hpp"
#include "entity.hpp"
#include "SaveManager/SaveManager.hpp"

#include <vector>
#include <unordered_map>
#include <bitset>
#include <iostream>

namespace Engine
{
#ifndef DEBUG
    #define DEBUG 0
#endif

    const std::vector<std::string> COMPONENTS = {"MATRIX2D",
        "RENDER 2D",
        "RENDER 3D",
        "CLICK EVENT",
        "CLICK FOCUS EVENT",
        "KEY EVENT",
        "MOUSE MOVE EVENT",
        "HITBOX",
        "POSITION",
        "ENTITY BOX",
        "KEY BOX",
        "STRING CHOICE",
        "PLAYER CONFIG",
        "VELOCITY",
        "TIMER",
        "SCRIPT",
        "CHRONO",
        "TEXT INPUT CONFIG",
        "SOUND",
        "OPTION COMPONENT",
        "PLAYER INVENTORY",
        "MODEL LIST",
        "AI COMPONENT"};

    template <typename T> class ComponentTypeRegister : public IComponentTypeRegister {
      public:
        ComponentTypeRegister(std::vector<Signature> &entityToBitset);

        void allocate(std::size_t size) override;

        T &get(Entity entity);

        template <typename... Args> void add(Entity entity, Args &&...args);

        void remove(Entity entity);
        virtual bool tryRemove(Entity entity) override;
        Entity getOwner(const T &component);

        std::vector<T> &getComponents();

      private:
        std::vector<T> _components;
        std::vector<Entity> _componentOwners;
        std::unordered_map<Entity, Index> _ownersIndex;
        std::vector<Signature> &_entitySignatures;
    };

    template <typename T>
    ComponentTypeRegister<T>::ComponentTypeRegister(std::vector<Signature> &entityToBitset) : _entitySignatures(entityToBitset)
    {
    }

    template <typename T> void ComponentTypeRegister<T>::allocate(std::size_t size)
    {
        _components.reserve(size);
        _componentOwners.reserve(size);
        _ownersIndex.reserve(size);
    }

    template <typename T> T &ComponentTypeRegister<T>::get(Entity entity)
    {
        return _components[_ownersIndex[entity]];
    }

    template <typename T> template <typename... Args> void ComponentTypeRegister<T>::add(Entity entity, Args &&...args)
    {
        if (DEBUG) {
            std::cerr << "ADD COMPONENT " << COMPONENTS[T::type] << " -> " << entity << "\n";
        }
        auto index = static_cast<Index>(_components.size());

        _components.emplace_back(std::forward<Args>(args)...);
        _componentOwners.emplace_back(entity);
        _ownersIndex[entity] = index;
        _entitySignatures[entity][T::type] = true;
    }

    template <typename T> void ComponentTypeRegister<T>::remove(Entity entity)
    {
        if (DEBUG) {
            std::cerr << "REMOVE COMPONENT " << COMPONENTS[T::type] << " -> " << entity << "\n";
        }
        _entitySignatures[entity][T::type] = false;
        auto index = _ownersIndex[entity];
        // update _components
        _components[index] = std::move(_components.back());
        _components.pop_back();
        // update _ownersIndex
        _ownersIndex[_componentOwners.back()] = index;
        _ownersIndex.erase(entity);
        // update _componentOwners
        _componentOwners[index] = _componentOwners.back();
        _componentOwners.pop_back();
    }

    template <typename T> bool ComponentTypeRegister<T>::tryRemove(Entity entity)
    {
        if (_entitySignatures[entity][T::type]) {
            this->remove(entity);
            return true;
        }
        return false;
    }

    template <typename T> Entity ComponentTypeRegister<T>::getOwner(const T &component)
    {
        auto begin = _components.data();
        auto index = static_cast<std::size_t>(&component - begin);
        return _componentOwners[index];
    }

    template <typename T> std::vector<T> &ComponentTypeRegister<T>::getComponents()
    {
        return _components;
    }

} // namespace Engine

#endif // COMPONENTTYPEREGISTER_HPP