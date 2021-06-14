/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** AbstractScene
*/

#ifndef ABSTRACTSCENE_HPP_
#define ABSTRACTSCENE_HPP_

#include "EntityManager/EntityManager.hpp"
#include "SystemManager/SystemManager.hpp"
#include "EntityPack/EntityPack.hpp"

namespace Engine
{
    class AbstractScene {
      public:
        AbstractScene(SystemManager &systemManager, EntityManager &entityManager);
        ~AbstractScene() = default;

        virtual void update() = 0;

        virtual void close();
        virtual void open() = 0;

      public:
        EntityPack localEntities;

      protected:
        SystemManager &_systemManager;
        EntityManager &_entityManager;
    };
}

#endif /* !ABSTRACTSCENE_HPP_ */