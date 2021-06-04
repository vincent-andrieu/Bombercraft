/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 02/06/2021 Script.hpp.h
*/

#ifndef SCRIPT_HPP
#define SCRIPT_HPP

#include "Component/Component.hpp"
#include "EntityManager/EntityManager.hpp"
#include "SceneManager/SceneManager.hpp"
#include "entity.hpp"
#include <functional>

namespace Engine
{
#define SCRIPT_HANDLER std::function<void(Engine::EntityManager, Engine::SceneManager, const Engine::Entity)>

    class Script : public Component<Script> {
      public:
        Script(EntityManager &entityManager, SceneManager &sceneManager, SCRIPT_HANDLER &handler)
            : handler(handler), _entityManager(entityManager), _sceneManager(sceneManager)
        {
        }

        ~Script() = default;

        void trigger(const Entity entity)
        {
            handler(_entityManager, _sceneManager, entity);
        }

        void save(SaveManager &saver) const override
        {
            try {
                saver.closeWritingFile();
            } catch (const std::filesystem::filesystem_error &my_e) {
                SaveManager::printException(my_e);
            }
        }
        void load(SaveManager &saver) override
        {
            try {
                saver.closeReadingFile();
            } catch (const std::filesystem::filesystem_error &my_e) {
                SaveManager::printException(my_e);
            }
        }

      private:
        SCRIPT_HANDLER &handler;
        EntityManager &_entityManager;
        SceneManager &_sceneManager;
    };
} // namespace Engine

#endif // EVENT_HPP