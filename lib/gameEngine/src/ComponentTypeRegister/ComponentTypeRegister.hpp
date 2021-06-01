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

namespace Engine
{
    template <typename T> class ComponentTypeRegister : public IComponentTypeRegister {
      public:
        ComponentTypeRegister(std::vector<Signature> &entityToBitset);

        virtual void allocate(std::size_t size) override;

        T &get(Entity entity);

        template <typename... Args> void add(Entity entity, Args &&...args);

        void remove(Entity entity);
        virtual bool tryRemove(Entity entity) override;
        Entity getOwner(const T &component);

        void save(Engine::SaveManager &saver) const;

      private:
        std::vector<T> _components;
        std::vector<Entity> _componentOwners;
        std::unordered_map<Entity, Index> _ownersIndex;
        std::vector<Signature> &_entitySignatures;

        void saveOwnersIndex(Engine::SaveManager &saver);
        void saveEntities(Engine::SaveManager &saver);
        void saveEntity(Engine::SaveManager &saver, Entity toSave);
        void saveEntityComponents(Engine::SaveManager &saver, Entity toSave);
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
        auto index = static_cast<Index>(_components.size());

        _components.emplace_back(std::forward<Args>(args)...);
        _componentOwners.emplace_back(entity);
        _ownersIndex[entity] = index;
        _entitySignatures[entity][T::type] = true;
    }

    template <typename T> void ComponentTypeRegister<T>::remove(Entity entity)
    {
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

    template <typename T> void ComponentTypeRegister<T>::save(Engine::SaveManager &saver) const
    {
        //        saver.createFolder("game_" + saver.getGameNb());
        //        saver.createFile("EntityToComponent");
        saveOwnersIndex(saver);
        saveEntities(saver);
    }

    template <typename T> void ComponentTypeRegister<T>::saveOwnersIndex(Engine::SaveManager &saver)
    {
        const std::string filename("EntityToComponent");

        //        saver.createFile(filename);
        //        saver.write(filename, _ownersIndex);
    }

    template <typename T> void ComponentTypeRegister<T>::saveEntities(Engine::SaveManager &saver)
    {
        for (const auto &owner : _componentOwners) {
            //        saver.createFolder("Entity_" + owner);
            saveEntity(saver, owner);
        }
    }

    template <typename T> void ComponentTypeRegister<T>::saveEntity(Engine::SaveManager &saver, Entity owner)
    {
        saveEntityComponents(saver, owner);
    }

    template <typename T> void ComponentTypeRegister<T>::saveEntityComponents(Engine::SaveManager &saver, Entity owner)
    {
        for (const auto &entity_component : _ownersIndex) {
            if (entity_component.first == owner) {
                _components[entity_component].second->save();
            }
        }
    }
} // namespace Engine

#endif // COMPONENTTYPEREGISTER_HPP