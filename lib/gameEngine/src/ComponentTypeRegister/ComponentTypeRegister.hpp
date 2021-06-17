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
#include <mutex>

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
        Entity getOwner(const T &component) const;

        // void save(Engine::SaveManager &saver) const override;
        // void load(Engine::SaveManager &saver) override;

        std::vector<T> &getComponents();

      private:
        std::vector<T> _components;
        std::vector<Entity> _componentOwners;
        std::unordered_map<Entity, Index> _ownersIndex;
        std::vector<Signature> &_entitySignatures;
        std::mutex _mutex;

        // void saveEntities(Engine::SaveManager &saver) const;
        // void saveEntity(Engine::SaveManager &saver, Entity owner) const;
        // void saveEntitySignature(Engine::SaveManager &saver, Entity owner) const;
        //        void saveEntityComponentIndex(Engine::SaveManager &saver, Entity owner) const;
        // void saveEntityComponents(Engine::SaveManager &saver, Entity owner) const;

        // void loadEntities(Engine::SaveManager &saver);
        // void loadEntity(Engine::SaveManager &saver, Entity owner);
        // void loadEntitySignature(Engine::SaveManager &saver, Entity owner);
        //        void loadEntityComponentIndex(Engine::SaveManager &saver, Entity owner) ;
        // void loadEntityComponents(Engine::SaveManager &saver, Entity owner);
    };

    template <typename T>
    ComponentTypeRegister<T>::ComponentTypeRegister(std::vector<Signature> &entityToBitset) : _entitySignatures(entityToBitset)
    {
    }

    template <typename T> void ComponentTypeRegister<T>::allocate(std::size_t size)
    {
        std::lock_guard<std::mutex> lock_guard(this->_mutex);

        //        _components.reserve(size);
        _componentOwners.reserve(size);
        _ownersIndex.reserve(size);
    }

    template <typename T> T &ComponentTypeRegister<T>::get(Entity entity)
    {
        std::lock_guard<std::mutex> lock_guard(this->_mutex);

        return _components[_ownersIndex[entity]];
    }

    template <typename T> template <typename... Args> void ComponentTypeRegister<T>::add(Entity entity, Args &&...args)
    {
        std::lock_guard<std::mutex> lock_guard(this->_mutex);
        auto index = static_cast<Index>(_components.size());

        _components.emplace_back(std::forward<Args>(args)...);
        _componentOwners.emplace_back(entity);
        _ownersIndex[entity] = index;
        _entitySignatures[entity][T::type] = true;
    }

    template <typename T> void ComponentTypeRegister<T>::remove(Entity entity)
    {
        std::lock_guard<std::mutex> lock_guard(this->_mutex);

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

    template <typename T> Entity ComponentTypeRegister<T>::getOwner(const T &component) const
    {
        auto begin = _components.data();
        auto index = static_cast<std::size_t>(&component - begin);
        return _componentOwners[index];
    }

    // template <typename T> void ComponentTypeRegister<T>::save(Engine::SaveManager &saver) const
    // {
    //     //        saver.createDirectory("game_" + saver.getGameNb()); // TODO put this elsewhere
    //     //        saver.setWorkingDirectory("game_" + saver.getGameNb()); // TODO put this elsewhere
    //     saveEntities(saver);
    // }

    // template <typename T> void ComponentTypeRegister<T>::saveEntities(Engine::SaveManager &saver) const
    // {
    //     for (const auto &owner : _componentOwners) {
    //         saveEntity(saver, owner);
    //     }
    // }

    // template <typename T> void ComponentTypeRegister<T>::saveEntity(Engine::SaveManager &saver, Entity owner) const
    // {
    //     const std::string dirPrefix("Entity_");
    //     const std::string dirname(dirPrefix + std::to_string(owner));

    //     try {
    //         if (!Engine::SaveManager::directoryExists(dirname))
    //             saver.createDirectory(dirname);
    //         saver.setWorkingDirectory(dirname);
    //     } catch (const std::filesystem::filesystem_error &my_e) {
    //         SaveManager::printException(my_e);
    //     }
    //     saveEntitySignature(saver, owner);
    //     saveEntityComponents(saver, owner);
    //     try {
    //         saver.unsetWorkingDirectory();
    //     } catch (const std::filesystem::filesystem_error &my_e) {
    //         SaveManager::printException(my_e);
    //     }
    // }

    // template <typename T> void ComponentTypeRegister<T>::saveEntitySignature(Engine::SaveManager &saver, Entity owner) const
    // {
    //     const std::string filename("EntitySignature");

    //     try {
    //         saver.createFile(filename);
    //         saver.setWritingFile(filename);
    //         saver.writeActFile(_entitySignatures[owner]);
    //         saver.closeWritingFile();
    //     } catch (const std::filesystem::filesystem_error &my_e) {
    //         SaveManager::printException(my_e);
    //     }
    // }

    //    template <typename T> void ComponentTypeRegister<T>::saveEntityComponentIndex(Engine::SaveManager &saver, Entity
    //    owner) const
    //    {
    //        const std::string filename("EntityComponentIndex");
    //
    //        saver.createFile(filename);
    //        saver.setWritingFile(filename);
    //        saver.writeActFile(_ownersIndex.at(owner));
    //        saver.closeFile(filename);
    //}

    // template <typename T> void ComponentTypeRegister<T>::saveEntityComponents(Engine::SaveManager &saver, Entity owner) const
    // {
    //     _components.at(_ownersIndex.at(owner)).save(saver);
    // }

    // template <typename T> void ComponentTypeRegister<T>::load(Engine::SaveManager &saver)
    // {
    //     //        saver.createDirectory("game_" + saver.getGameNb()); // TODO put this elsewhere
    //     //        saver.setWorkingDirectory("game_" + saver.getGameNb()); // TODO put this elsewhere
    //     loadEntities(saver);
    // }

    // template <typename T> void ComponentTypeRegister<T>::loadEntities(Engine::SaveManager &saver)
    // {
    //     for (const auto &owner : _componentOwners) {
    //         loadEntity(saver, owner);
    //     }
    // }

    // template <typename T> void ComponentTypeRegister<T>::loadEntity(Engine::SaveManager &saver, Entity owner)
    // {
    //     const std::string dirPrefix("Entity_");
    //     const std::string dirname(dirPrefix + std::to_string(owner));

    //     try {
    //         saver.setWorkingDirectory(dirname);
    //     } catch (const std::filesystem::filesystem_error &my_e) {
    //         SaveManager::printException(my_e);
    //     }
    //     loadEntitySignature(saver, owner);
    //     loadEntityComponents(saver, owner);
    //     try {
    //         saver.unsetWorkingDirectory();
    //     } catch (const std::filesystem::filesystem_error &my_e) {
    //         SaveManager::printException(my_e);
    //     }
    // }

    // template <typename T> void ComponentTypeRegister<T>::loadEntitySignature(Engine::SaveManager &saver, Entity owner)
    // {
    //     const std::string filename("EntitySignature");

    //     try {
    //         saver.setWritingFile(filename);
    //         saver.writeActFile(_entitySignatures[owner]);
    //         saver.closeWritingFile();
    //     } catch (const std::filesystem::filesystem_error &my_e) {
    //         SaveManager::printException(my_e);
    //     }
    // }

    //    template <typename T> void ComponentTypeRegister<T>::loadEntityComponentIndex(Engine::SaveManager &saver, Entity
    //    owner)
    //    {
    //        const std::string filename("EntityComponentIndex");
    //
    //        saver.setWritingFile(filename);
    //        saver.writeActFile(_ownersIndex.at(owner));
    //        saver.closeFile(filename);
    //}

    // template <typename T> void ComponentTypeRegister<T>::loadEntityComponents(Engine::SaveManager &saver, Entity owner)
    // {
    //     _components.at(_ownersIndex.at(owner)).load(saver);
    // }

    template <typename T> std::vector<T> &ComponentTypeRegister<T>::getComponents()
    {
        std::lock_guard<std::mutex> lock_guard(this->_mutex);

        return _components;
    }

} // namespace Engine

#endif // COMPONENTTYPEREGISTER_HPP