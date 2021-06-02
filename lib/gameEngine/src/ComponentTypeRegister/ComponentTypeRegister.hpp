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

        void saveEntities(Engine::SaveManager &saver) const;
        void saveEntity(Engine::SaveManager &saver, Entity owner) const;
        void saveEntitySignature(Engine::SaveManager &saver, Entity owner) const;
        void saveEntityComponents(Engine::SaveManager &saver, Entity owner) const;
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
        //        saver.createDirectory("game_" + saver.getGameNb()); // TODO put this elsewhere
        //        saver.setWorkingDirectory("game_" + saver.getGameNb()); // TODO put this elsewhere
        saveEntities(saver);
    }

    template <typename T> void ComponentTypeRegister<T>::saveEntities(Engine::SaveManager &saver) const
    {
        for (const auto &owner : _componentOwners) {
            saveEntity(saver, owner);
        }
    }

    template <typename T> void ComponentTypeRegister<T>::saveEntity(Engine::SaveManager &saver, Entity owner) const
    {
        const std::string dirPrefix("Entity_");
        const std::string dirname(dirPrefix + std::to_string(owner));

        if (!Engine::SaveManager::directoryExists(dirname))
            saver.createDirectory(dirname);
        saver.setWorkingDirectory(dirname);
        saveEntitySignature(saver, owner);
        saveEntityComponents(saver, owner);
        saver.unsetWorkingDirectory();
    }

    template <typename T> void ComponentTypeRegister<T>::saveEntitySignature(Engine::SaveManager &saver, Entity owner) const
    {
        const std::string filename("EntitySignature");

        saver.createFile(filename);
        saver.setWritingFile(filename);
        saver.writeActFile(_entitySignatures[owner]);
        saver.closeFile(filename);
    }

    template <typename T> void ComponentTypeRegister<T>::saveEntityComponents(Engine::SaveManager &saver, Entity owner) const
    {
        //        _components.at(_ownersIndex.at(owner)).save(saver);
    }

} // namespace Engine

#endif // COMPONENTTYPEREGISTER_HPP