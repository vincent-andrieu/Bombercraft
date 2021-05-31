/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** AbstractScene
*/

#ifndef ABSTRACTSCENE_HPP_
#define ABSTRACTSCENE_HPP_

#include "IEventManager.hpp"
#include "EntityManager.hpp"
#include "SceneManager.hpp"
#include "SystemManager.hpp"

namespace Engine
{
    class AbstractScene {
      public:
        AbstractScene(
            IEventManager &events, SystemManager &systemManager, EntityManager<MAX_COMPONENT, MAX_SYSTEM> &entityManager);
        ~AbstractScene();

        virtual void update() = 0;

      protected:
      private:
        IEventManager &_events;
        SystemManager &_systemManager;
        EntityManager<MAX_COMPONENT, MAX_SYSTEM> &_entityManager;
    };
}

#endif /* !ABSTRACTSCENE_HPP_ */
